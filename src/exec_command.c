/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:07:12 by jramos-a          #+#    #+#             */
/*   Updated: 2025/05/31 08:13:46 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	build_command_args(t_sh *sh, t_parse *parse)
{
	t_parse	*current;
	int		count;
	t_cmd	*cmd_node;
	int		cmd_idx;
	int		cmd_count;

	count = 0;
	cmd_node = sh->node->cmd;
	cmd_count = 1;
	current = parse;
	while (current)
	{
		if (current->type_token == PIPE)
			cmd_count++;
		current = current->next;
	}
	sh->node->n_cmd = cmd_count;
	printf("Found %d commands in pipe chain\n", cmd_count);
	current = parse;
	cmd_node = sh->node->cmd;
	while (current)
	{
		if (current->type_token == PIPE)
		{
			if (count > 0)
			{
				cmd_node->split_cmd = malloc(sizeof(char *) * (count + 1));
				if (!cmd_node->split_cmd)
					return ;
			}
			ft_lstadd_back_cmd(cmd_node);
			cmd_node = cmd_node->next;
			count = 0;
			current = current->next;
			continue ;
		}
		if (current->type_token == CMD || current->type_token == BUILT
			|| current->type_token == FLAG || current->type_token == ARG
			|| current->type_token == INRED || current->type_token == OURED
			|| current->type_token == D_OURED || current->type_token == HEREDOC
			|| current->type_token == DELIM || current->type_token == INFILE
			|| current->type_token == OUTFILE_TR
			|| current->type_token == OUTFILE_APP)
		{
			count++;
		}
		current = current->next;
	}
	if (count > 0)
	{
		cmd_node->split_cmd = malloc(sizeof(char *) * (count + 1));
		if (!cmd_node->split_cmd)
			return ;
	}
	current = parse;
	cmd_node = sh->node->cmd;
	count = 0;
	while (current)
	{
		if (current->type_token == PIPE)
		{
			if (cmd_node && cmd_node->split_cmd)
				cmd_node->split_cmd[count] = NULL;
			cmd_node = cmd_node->next;
			count = 0;
			current = current->next;
			continue ;
		}
		if (current->type_token == CMD || current->type_token == BUILT
			|| current->type_token == FLAG || current->type_token == ARG
			|| current->type_token == INRED || current->type_token == OURED
			|| current->type_token == D_OURED || current->type_token == HEREDOC
			|| current->type_token == DELIM || current->type_token == INFILE
			|| current->type_token == OUTFILE_TR
			|| current->type_token == OUTFILE_APP)
		{
			if (cmd_node && cmd_node->split_cmd)
			{
				cmd_node->split_cmd[count] = ft_strdup(current->line);
				count++;
			}
		}
		current = current->next;
	}
	if (cmd_node && cmd_node->split_cmd)
		cmd_node->split_cmd[count] = NULL;
	cmd_node = sh->node->cmd;
	cmd_idx = 0;
	while (cmd_node)
	{
		printf("Command %d: ", cmd_idx++);
		if (cmd_node->split_cmd)
		{
			for (int i = 0; cmd_node->split_cmd[i]; i++)
				printf("[%s] ", cmd_node->split_cmd[i]);
		}
		printf("\n");
		cmd_node = cmd_node->next;
	}
}

char	*find_path(char **envp)
{
	char	*env_path;
	int		i;

	env_path = NULL;
	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			env_path = envp[i] + 5;
			break ;
		}
		i++;
	}
	return (env_path);
}

char	*try_executable_path(char **paths, char *command)
{
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	if (!paths || !command || !command[0])
		return (NULL);
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		path = ft_strjoin(tmp, command);
		free(tmp);
		if (!path)
			return (NULL);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*get_path(char **envp, char *command)
{
	char	*env_path;
	char	**paths;
	char	*executable_path;

	if (!command || !command[0])
		return (NULL);
	if (command[0] == '/' || command[0] == '.' || ft_strchr(command,
			'/') != NULL)
	{
		if (access(command, F_OK) == 0)
		{
			if (access(command, X_OK) != 0)
			{
				write(2, command, ft_strlen(command));
				write(2, ": Permission denied\n", 20);
				return (NULL);
			}
			return (ft_strdup(command));
		}
		write(2, command, ft_strlen(command));
		write(2, ": No such file or directory\n", 28);
		return (NULL);
	}
	env_path = find_path(envp);
	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ':');
	if (!paths)
		return (NULL);
	executable_path = try_executable_path(paths, command);
	free_args(paths);
	return (executable_path);
}

void	exec_external_command(t_sh *sh, char **envp)
{
	pid_t	pid;
	char	*path;
	int		status;
	int		i;
	t_reds	*redirs;
	char	**clean_args;
	int		stdin_fd;
	int		stdout_fd;
	t_reds	*current;

	stdin_fd = -1;
	stdout_fd = -1;
	printf("Executing command: ");
	if (sh->node->cmd && sh->node->cmd->split_cmd)
	{
		i = 0;
		while (sh->node->cmd->split_cmd[i])
		{
			printf("[%s] ", sh->node->cmd->split_cmd[i]);
			i++;
		}
		printf("\n");
	}
	if (!sh->node->cmd || !sh->node->cmd->split_cmd
		|| !sh->node->cmd->split_cmd[0])
	{
		write(2, "Command not found\n", 18);
		return ;
	}
	if (has_redirection_in_cmd(sh->node->cmd))
	{
		redirs = parse_redirection_from_cmd(sh->node->cmd);
		if (!redirs)
			return ;
		if (open_all_redirs(redirs) < 0)
		{
			free_redirs(redirs);
			return ;
		}
		clean_args = clean_cmd_args(sh->node->cmd);
		if (!clean_args)
		{
			free_redirs(redirs);
			return ;
		}
	}
	else
	{
		redirs = NULL;
		clean_args = sh->node->cmd->split_cmd;
	}
	path = get_path(envp, clean_args[0]);
	if (!path)
	{
		if (ft_strchr(clean_args[0], '/') == NULL)
		{
			write(2, clean_args[0], ft_strlen(clean_args[0]));
			write(2, ": command not found\n", 20);
		}
		if (redirs)
			free_redirs(redirs);
		if (clean_args != sh->node->cmd->split_cmd)
			free_args(clean_args);
		return ;
	}
	if (redirs)
	{
		current = redirs;
		while (current)
		{
			if (current->type == INRED || current->type == HEREDOC)
				stdin_fd = current->fd;
			else if (current->type == OURED || current->type == D_OURED)
				stdout_fd = current->fd;
			current = current->next;
		}
	}
	pid = fork();
	if (pid == -1)
	{
		write(2, "fork: failed to create process\n", 31);
		free(path);
		if (redirs)
			free_redirs(redirs);
		if (clean_args != sh->node->cmd->split_cmd)
			free_args(clean_args);
		return ;
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (stdin_fd != -1)
			dup2(stdin_fd, STDIN_FILENO);
		if (stdout_fd != -1)
			dup2(stdout_fd, STDOUT_FILENO);
		if (redirs)
		{
			current = redirs;
			while (current)
			{
				if (current->fd != -1)
					close(current->fd);
				current = current->next;
			}
		}
		if (execve(path, clean_args, envp) == -1)
		{
			write(2, clean_args[0], ft_strlen(clean_args[0]));
			write(2, ": execution failed\n", 19);
			free(path);
			if (redirs)
				free_redirs(redirs);
			if (clean_args != sh->node->cmd->split_cmd)
				free_args(clean_args);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		if (redirs)
		{
			current = redirs;
			while (current)
			{
				if (current->fd != -1)
					close(current->fd);
				current->fd = -1;
				current = current->next;
			}
			free_redirs(redirs);
		}
		waitpid(pid, &status, 0);
		ft_signals();
		free(path);
		if (clean_args != sh->node->cmd->split_cmd)
			free_args(clean_args);
		if (WIFSIGNALED(status))
			last_signal_code(128 + WTERMSIG(status));
		else if (WIFEXITED(status))
			last_signal_code(WEXITSTATUS(status));
	}
}

void	fork_and_exec(char *command, char **envp)
{
	pid_t	pid;
	int		status;
	char	**args;
	char	*path;

	args = ft_split(command, ' ');
	if (!args)
		return ;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		path = get_path(envp, args[0]);
		if (path)
		{
			execve(path, args, envp);
			free(path);
		}
		else
			write(2, "Command not found\n", 18);
		free_args(args);
		exit(EXIT_FAILURE);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		ft_signals();
		if (WIFSIGNALED(status))
			last_signal_code(128 + WTERMSIG(status));
		else if (WIFEXITED(status))
			last_signal_code(WEXITSTATUS(status));
	}
	free_args(args);
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}

// void	execute_cmd(t_cmd *cmd, char **envp, t_sh *sh)
// {
// 	pid_t	pid;
// 	int		status;
// 	char	*executable_path;

// 	(void)sh;
// 	if (!cmd || !cmd->cmd || !cmd->split_cmd || !cmd->split_cmd[0])
// 	{
// 		write(2, "Command not found or improperly parsed\n", 39);
// 		return ;
// 	}
// 	executable_path = get_path(envp, cmd->split_cmd[0]);
// 	if (!executable_path)
// 	{
// 		write(2, "Command not found: ", 19);
// 		write(2, cmd->split_cmd[0], ft_strlen(cmd->split_cmd[0]));
// 		write(2, "\n", 1);
// 		return ;
// 	}
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		signal(SIGINT, SIG_DFL);
// 		signal(SIGQUIT, SIG_DFL);
// 		execve(executable_path, cmd->split_cmd, envp);
// 		perror("execve");
// 		free(executable_path);
// 		exit(EXIT_FAILURE);
// 	}
// 	else
// 	{
// 		signal(SIGINT, SIG_IGN);
// 		waitpid(pid, &status, 0);
// 		ft_signals();
// 		free(executable_path);
// 		if (WIFSIGNALED(status))
// 			last_signal_code(128 + WTERMSIG(status));
// 		else if (WIFEXITED(status))
// 			last_signal_code(WEXITSTATUS(status));
// 	}
// }

// void exec_command(char *command, char **envp, t_sh *sh)
// {
// 	char **args;

// 	args = ft_split(command, ' ');
// 	if (!command || !*command)
// 	{
// 		free_args(args);
// 		return ;
// 	}
// 	if (!args)
// 	{
// 		perror("ft_split");
// 		return ;
// 	}
// 	if (is_pipe(args))
// 	{
// 		free_args(args);
// 		handle_pipes(command, envp);
// 		return ;
// 	}
// 	if (has_redirection(args))
// 	{
// 		free_args(args);
// 		handle_redirs(command, envp);
// 		return ;
// 	}
// 	if (is_builtin(args[0]))
// 	{
// 		if (exec_builtin(args, envp, sh))
// 		{
// 			free_args(args);
// 			return ;
// 		}
// 	}
// 	else
// 	{
// 		free_args(args);
// 		fork_and_exec(command, envp);
// 		return ;
// 	}
// 	free_args(args);
// }

char	**inc_shlvl(char **envp)
{
	int		i;
	int		shlvl;
	char	*new_value;
	char	*new_var;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
		{
			shlvl = ft_atoi(envp[i] + 6);
			new_value = ft_itoa(shlvl + 1);
			if (new_value)
			{
				new_var = ft_strjoin("SHLVL=", new_value);
				free(new_value);
				if (new_var)
					envp[i] = new_var;
			}
			break ;
		}
		i++;
	}
	return (envp);
}

void	exec_external_command_with_redirs(t_sh *sh, char **envp, t_reds *redirs)
{
	pid_t	pid;
	char	*path;
	int		status;
	int		stdin_fd;
	int		stdout_fd;
	t_reds	*current;

	stdin_fd = -1;
	stdout_fd = -1;
	if (!sh->node->cmd || !sh->node->cmd->split_cmd
		|| !sh->node->cmd->split_cmd[0])
	{
		write(2, "Command not found\n", 18);
		return ;
	}
	path = get_path(envp, sh->node->cmd->split_cmd[0]);
	if (!path)
	{
		if (ft_strchr(sh->node->cmd->split_cmd[0], '/') == NULL)
		{
			write(2, sh->node->cmd->split_cmd[0],
				ft_strlen(sh->node->cmd->split_cmd[0]));
			write(2, ": command not found\n", 20);
		}
		return ;
	}
	if (redirs)
	{
		current = redirs;
		while (current)
		{
			if (current->type == INRED || current->type == HEREDOC)
				stdin_fd = current->fd;
			else if (current->type == OURED || current->type == D_OURED)
				stdout_fd = current->fd;
			current = current->next;
		}
	}
	pid = fork();
	if (pid == -1)
	{
		write(2, "fork: failed to create process\n", 31);
		free(path);
		return ;
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (stdin_fd != -1)
			dup2(stdin_fd, STDIN_FILENO);
		if (stdout_fd != -1)
			dup2(stdout_fd, STDOUT_FILENO);
		if (redirs)
		{
			current = redirs;
			while (current)
			{
				if (current->fd != -1)
					close(current->fd);
				current = current->next;
			}
		}
		if (execve(path, sh->node->cmd->split_cmd, envp) == -1)
		{
			write(2, sh->node->cmd->split_cmd[0],
				ft_strlen(sh->node->cmd->split_cmd[0]));
			write(2, ": execution failed\n", 19);
			free(path);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		if (redirs)
		{
			current = redirs;
			while (current)
			{
				if (current->fd != -1)
					close(current->fd);
				current = current->next;
			}
		}
		waitpid(pid, &status, 0);
		ft_signals();
		free(path);
		if (WIFSIGNALED(status))
			last_signal_code(128 + WTERMSIG(status));
		else if (WIFEXITED(status))
			last_signal_code(WEXITSTATUS(status));
	}
}

int	exec_parsed_command(t_sh *sh, char **envp)
{
	int		has_pipe;
	int		has_redirs;
	int		i;
	t_reds	*redirs;
	char	**clean_args;
	char	**cmd_to_exec;
	int		result;
	char	**temp;
	int		stdin_backup;
	int		has_heredoc;
	int		needs_cleanup;
	char	**cat_args;

	stdin_backup = -1;
	has_heredoc = 0;
	needs_cleanup = 0;
	redirs = NULL;
	clean_args = NULL;
	printf("Executing parsed command\n");
	if (!sh->node || !sh->node->cmd)
	{
		return (1);
	}
	if (isatty(STDIN_FILENO))
	{
		stdin_backup = dup(STDIN_FILENO);
		if (stdin_backup < 0)
		{
			perror("dup");
			return (1);
		}
	}
	has_pipe = 0;
	has_redirs = 0;
	i = 0;
	if (sh->node->cmd->split_cmd)
	{
		while (sh->node->cmd->split_cmd[i])
		{
			if (ft_strncmp(sh->node->cmd->split_cmd[i], "|", 2) == 0)
				has_pipe = 1;
			else if (ft_strncmp(sh->node->cmd->split_cmd[i], ">", 2) == 0
				|| ft_strncmp(sh->node->cmd->split_cmd[i], ">>", 3) == 0
				|| ft_strncmp(sh->node->cmd->split_cmd[i], "<", 2) == 0
				|| ft_strncmp(sh->node->cmd->split_cmd[i], "<<", 3) == 0)
			{
				has_redirs = 1;
				if (ft_strncmp(sh->node->cmd->split_cmd[i], "<<", 3) == 0)
					has_heredoc = 1;
			}
			i++;
		}
	}
	if (has_redirs && (!sh->node->cmd->split_cmd
			|| !sh->node->cmd->split_cmd[0]))
	{
		printf("Creating default cat command for heredoc\n");
		cat_args = malloc(sizeof(char *) * 2);
		if (!cat_args)
		{
			if (stdin_backup != -1)
				close(stdin_backup);
			return (1);
		}
		cat_args[0] = ft_strdup("cat");
		cat_args[1] = NULL;
		sh->node->cmd->split_cmd = cat_args;
		needs_cleanup = 1;
	}
	if (!sh->node->cmd->split_cmd || !sh->node->cmd->split_cmd[0])
	{
		printf("No command to execute\n");
		if (stdin_backup != -1)
			close(stdin_backup);
		return (1);
	}
	printf("Command to execute: [%s]\n", sh->node->cmd->split_cmd[0]);
	if (has_redirs)
	{
		printf("Processing redirections\n");
		redirs = parse_redirection_from_cmd(sh->node->cmd);
		if (!redirs)
		{
			if (stdin_backup != -1)
				close(stdin_backup);
			if (needs_cleanup && sh->node->cmd->split_cmd)
				free_args(sh->node->cmd->split_cmd);
			return (1);
		}
		if (has_heredoc)
			printf("Heredoc detected\n");
		if (open_all_redirs(redirs) < 0)
		{
			printf("Failed to open redirections\n");
			if (stdin_backup != -1)
				close(stdin_backup);
			free_redirs(redirs);
			if (needs_cleanup && sh->node->cmd->split_cmd)
				free_args(sh->node->cmd->split_cmd);
			return (1);
		}
		clean_args = clean_cmd_args(sh->node->cmd);
		if (!clean_args)
		{
			printf("Failed to clean command arguments\n");
			if (stdin_backup != -1)
				close(stdin_backup);
			free_redirs(redirs);
			if (needs_cleanup && sh->node->cmd->split_cmd)
				free_args(sh->node->cmd->split_cmd);
			return (1);
		}
	}
	if (has_pipe)
	{
		if (stdin_backup != -1)
			close(stdin_backup);
		if (redirs)
			free_redirs(redirs);
		if (clean_args)
			free_args(clean_args);
		if (needs_cleanup && sh->node->cmd->split_cmd)
			free_args(sh->node->cmd->split_cmd);
		return (process_piped_command(sh, envp));
	}
	printf("Executing command: ");
	if (clean_args)
	{
		i = 0;
		while (clean_args[i])
		{
			printf("[%s] ", clean_args[i]);
			i++;
		}
		printf("\n");
	}
	else if (sh->node->cmd->split_cmd)
	{
		i = 0;
		while (sh->node->cmd->split_cmd[i])
		{
			printf("[%s] ", sh->node->cmd->split_cmd[i]);
			i++;
		}
		printf("\n");
	}
	cmd_to_exec = clean_args ? clean_args : sh->node->cmd->split_cmd;
	if (cmd_to_exec && is_builtin(cmd_to_exec[0]))
	{
		printf("Executing builtin: %s\n", cmd_to_exec[0]);
		if (redirs)
			result = exec_builtin_with_redirs(cmd_to_exec, envp, sh, redirs);
		else
			result = exec_builtin(cmd_to_exec, envp, sh);
		if (stdin_backup != -1)
		{
			dup2(stdin_backup, STDIN_FILENO);
			close(stdin_backup);
		}
		if (has_heredoc)
			unlink("heredoc.tmp");
		if (redirs)
			free_redirs(redirs);
		if (clean_args && clean_args != sh->node->cmd->split_cmd)
			free_args(clean_args);
		if (needs_cleanup && sh->node->cmd->split_cmd)
			free_args(sh->node->cmd->split_cmd);
		return (result);
	}
	else
	{
		if (has_redirs && clean_args)
		{
			temp = sh->node->cmd->split_cmd;
			sh->node->cmd->split_cmd = clean_args;
			exec_external_command_with_redirs(sh, envp, redirs);
			sh->node->cmd->split_cmd = temp;
			free_args(clean_args);
		}
		else
		{
			exec_external_command(sh, envp);
		}
		if (stdin_backup != -1)
		{
			dup2(stdin_backup, STDIN_FILENO);
			close(stdin_backup);
		}
		if (has_heredoc)
			unlink("heredoc.tmp");
		if (redirs)
			free_redirs(redirs);
		if (needs_cleanup && sh->node->cmd->split_cmd)
			free_args(sh->node->cmd->split_cmd);
	}
	return (0);
}
