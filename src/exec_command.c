/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:07:12 by jramos-a          #+#    #+#             */
/*   Updated: 2025/05/28 17:02:25 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char	*find_path(char **envp)
{
	char	*env_path;
	int		i;

	env_path = NULL;
	i = 0;
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

	if (command[0] == '/' || (command[0] == '.' && command[1] == '/'))
	{
		if (access(command, X_OK) == 0)
			return (ft_strdup(command));
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

void	execute_cmd(t_cmd *cmd, char **envp, t_sh *sh)
{
	pid_t	pid;
	int		status;
	char	*executable_path;

	(void)sh;
	if (!cmd || !cmd->cmd || !cmd->split_cmd || !cmd->split_cmd[0])
	{
		write(2, "Command not found or improperly parsed\n", 39);
		return ;
	}
	executable_path = get_path(envp, cmd->split_cmd[0]);
	if (!executable_path)
	{
		write(2, "Command not found: ", 19);
		write(2, cmd->split_cmd[0], ft_strlen(cmd->split_cmd[0]));
		write(2, "\n", 1);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execve(executable_path, cmd->split_cmd, envp);
		perror("execve");
		free(executable_path);
		exit(EXIT_FAILURE);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		ft_signals();
		free(executable_path);
		if (WIFSIGNALED(status))
			last_signal_code(128 + WTERMSIG(status));
		else if (WIFEXITED(status))
			last_signal_code(WEXITSTATUS(status));
	}
}

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

void	exec_external_command(t_sh *sh, char **envp)
{
	pid_t	pid;
	char	*path;
	int		status;

	if (!sh->node->cmd->split_cmd || !sh->node->cmd->split_cmd[0])
	{
		write(2, "Command not found\n", 18);
		return ;
	}
	path = get_path(envp, sh->node->cmd->split_cmd[0]);
	if (!path)
	{
		write(2, sh->node->cmd->split_cmd[0],
			ft_strlen(sh->node->cmd->split_cmd[0]));
		write(2, ": command not found\n", 20);
		return ;
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
	if (!sh->node || !sh->node->cmd)
		return (0);
	if (sh->node->line_is->with_pipe)
		return (handle_pipes(sh, envp));
	// if (sh->node->line_is->with_reds)
	//     handle_redirections(sh->node->cmd->split_cmd);
	if (sh->node->line_is->built)
		return (exec_builtin(sh->node->cmd->split_cmd, envp, sh));
	if (sh->node->line_is->cmd)
		exec_external_command(sh, envp);
	return (1);
}
