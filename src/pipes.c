/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:11:40 by jramos-a          #+#    #+#             */
/*   Updated: 2025/05/29 21:11:32 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	is_pipe(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return (0);
	while (args[i])
	{
		if (ft_strncmp(args[i], "|", 2) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	count_pipes(char **args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!args)
		return (0);
	while (args[i])
	{
		if (ft_strncmp(args[i], "|", 2) == 0)
			count++;
		i++;
	}
	return (count);
}

void	free_commands(char ***commands, int k)
{
	int	i;
	int	j;

	i = 0;
	if (!commands)
		return ;
	while (i < k)
	{
		j = 0;
		while (commands[i] && commands[i][j])
		{
			free(commands[i][j]);
			j++;
		}
		free(commands[i]);
		i++;
	}
	free(commands);
}

char	***split_command(char **args, int num_cmds)
{
	char	***commands;
	int		i;
	int		j;
	int		k;
	int		start;
	int		len;

	i = 0;
	j = 0;
	k = 0;
	start = 0;
	commands = malloc(sizeof(char **) * (num_cmds + 1));
	if (!commands)
		return (NULL);
	while (args[j])
	{
		if (ft_strncmp(args[j], "|", 2) == 0 || args[j + 1] == NULL)
		{
			if (args[j + 1] == NULL && ft_strncmp(args[j], "|", 2) != 0)
				len = j - start + 1;
			else
				len = j - start;
			commands[k] = malloc(sizeof(char *) * (len + 1));
			if (!commands[k])
			{
				free_commands(commands, k);
				return (NULL);
			}
			i = 0;
			while (i < len)
			{
				commands[k][i] = ft_strdup(args[start + i]);
				if (!commands[k][i])
				{
					while (--i >= 0)
						free(commands[k][i]);
					free_commands(commands, k + 1);
					return (NULL);
				}
				i++;
			}
			commands[k][i] = NULL;
			k++;
			start = j + 1;
		}
		j++;
	}
	commands[k] = NULL;
	return (commands);
}

void	pipe_command(char **args, char **envp)
{
	char	*path;

	if (!args || !args[0])
	{
		printf("Invalid command\n");
		exit(EXIT_FAILURE);
	}
	if (is_builtin(args[0]))
	{
		if (exec_builtin(args, envp, NULL))
			exit(EXIT_SUCCESS);
		exit(EXIT_FAILURE);
	}
	path = get_path(envp, args[0]);
	if (path)
	{
		execve(path, args, envp);
		free(path);
	}
	printf("Command not found: %s\n", args[0]);
	exit(EXIT_FAILURE);
}

void	close_pipe_fds(int fd_prev, int fd[2], int pipe_stage)
{
	if (fd_prev != -1)
		close(fd_prev);
	if (pipe_stage)
	{
		close(fd[0]);
		close(fd[1]);
	}
}

void	execute_pipe_chain_new(char ***commands, int cmd_count, char **envp)
{
	int		pipefd[2];
	int		prev_pipe;
	pid_t	*pids;
	char	*path;
	int		status;
	t_reds	*redirs;
	char	**clean_args;
		t_cmd temp_cmd;
	t_reds	*current;
	char	**exec_args;

	redirs = NULL;
	clean_args = NULL;
	prev_pipe = -1;
	pids = malloc(sizeof(pid_t) * cmd_count);
	if (!pids)
		return ;
	for (int i = 0; i < cmd_count; i++)
	{
		temp_cmd.split_cmd = commands[i];
		if (has_redirection_in_cmd(&temp_cmd))
		{
			redirs = parse_redirection_from_cmd(&temp_cmd);
			if (redirs)
			{
				if (open_all_redirs(redirs) >= 0)
				{
					clean_args = clean_cmd_args(&temp_cmd);
				}
			}
		}
		if (i < cmd_count - 1)
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe");
				if (redirs)
					free_redirs(redirs);
				if (clean_args)
					free_args(clean_args);
				free(pids);
				return ;
			}
		}
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("fork");
			if (redirs)
				free_redirs(redirs);
			if (clean_args)
				free_args(clean_args);
			free(pids);
			return ;
		}
		if (pids[i] == 0)
		{
			if (prev_pipe != -1)
			{
				dup2(prev_pipe, STDIN_FILENO);
				close(prev_pipe);
			}
			if (i < cmd_count - 1)
			{
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}
			if (redirs)
			{
				current = redirs;
				while (current)
				{
					if (current->type == INRED || current->type == HEREDOC)
						dup2(current->fd, STDIN_FILENO);
					else if (current->type == OURED || current->type == D_OURED)
						dup2(current->fd, STDOUT_FILENO);
					close(current->fd);
					current = current->next;
				}
			}
			exec_args = clean_args ? clean_args : commands[i];
			if (is_builtin(exec_args[0]))
			{
				exec_builtin(exec_args, envp, NULL);
				exit(EXIT_SUCCESS);
			}
			else
			{
				path = get_path(envp, exec_args[0]);
				if (path)
				{
					execve(path, exec_args, envp);
					free(path);
				}
				fprintf(stderr, "Command not found: %s\n", exec_args[0]);
				exit(EXIT_FAILURE);
			}
		}
		if (prev_pipe != -1)
			close(prev_pipe);
		if (i < cmd_count - 1)
		{
			prev_pipe = pipefd[0];
			close(pipefd[1]);
		}
		if (redirs)
		{
			free_redirs(redirs);
			redirs = NULL;
		}
		if (clean_args)
		{
			free_args(clean_args);
			clean_args = NULL;
		}
	}
	for (int i = 0; i < cmd_count; i++)
	{
		waitpid(pids[i], &status, 0);
		if (i == cmd_count - 1)
		{
			if (WIFEXITED(status))
				last_signal_code(WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				last_signal_code(128 + WTERMSIG(status));
		}
	}
	free(pids);
}

int	process_piped_command(t_sh *sh, char **envp)
{
	int		i;
	char	**cmd_args;
	char	***commands;
	int		pipe_count;
	int		cmd_count;
	int		start;
	int		cmd_idx;
	int		cmd_len;

	i = 0;
	cmd_args = sh->node->cmd->split_cmd;
	commands = NULL;
	pipe_count = 0;
	cmd_count = 0;
	(void)cmd_count;
	while (cmd_args[i])
	{
		if (ft_strncmp(cmd_args[i], "|", 2) == 0)
			pipe_count++;
		i++;
	}
	commands = malloc(sizeof(char **) * (pipe_count + 2));
	if (!commands)
		return (1);
	for (i = 0; i <= pipe_count + 1; i++)
		commands[i] = NULL;
	start = 0;
	cmd_idx = 0;
	i = 0;
	while (cmd_args[i])
	{
		if (ft_strncmp(cmd_args[i], "|", 2) == 0 || cmd_args[i + 1] == NULL)
		{
			cmd_len = i - start;
			if (cmd_args[i + 1] == NULL && ft_strncmp(cmd_args[i], "|", 2) != 0)
				cmd_len++;
			commands[cmd_idx] = malloc(sizeof(char *) * (cmd_len + 1));
			if (!commands[cmd_idx])
			{
				for (int j = 0; j < cmd_idx; j++)
					free_args(commands[j]);
				free(commands);
				return (1);
			}
			for (int j = 0; j < cmd_len; j++)
			{
				commands[cmd_idx][j] = ft_strdup(cmd_args[start + j]);
				if (!commands[cmd_idx][j])
				{
					for (int k = 0; k < j; k++)
						free(commands[cmd_idx][k]);
					free(commands[cmd_idx]);
					for (int k = 0; k < cmd_idx; k++)
						free_args(commands[k]);
					free(commands);
					return (1);
				}
			}
			commands[cmd_idx][cmd_len] = NULL;
			cmd_idx++;
			start = i + 1;
		}
		i++;
	}
	execute_pipe_chain_new(commands, cmd_idx, envp);
	for (i = 0; i < cmd_idx; i++)
		free_args(commands[i]);
	free(commands);
	return (0);
}

int	do_pipe(char **argv, char **envp, t_sh *sh)
{
	char	***all_cmds;
	int		i;
	int		saved_pipe_count;
	int		saved_n_cmd;
	int		saved_pipefd[2];

	if (!sh || !sh->node || !sh->node->cmd)
		return (-1);
	saved_pipe_count = sh->pipe_count;
	saved_n_cmd = sh->node->n_cmd;
	saved_pipefd[0] = sh->node->cmd->pipefd[0];
	saved_pipefd[1] = sh->node->cmd->pipefd[1];
	i = 0;
	sh->pipe_count = count_pipes(argv) + 1;
	sh->node->cmd->pipefd[0] = -1;
	sh->node->cmd->pipefd[1] = -1;
	sh->node->cmd->pipe_in = 0;
	sh->node->cmd->pipe_out = 0;
	sh->node->n_cmd = sh->pipe_count;
	all_cmds = split_command(argv, sh->pipe_count);
	if (!all_cmds)
	{
		sh->pipe_count = saved_pipe_count;
		sh->node->n_cmd = saved_n_cmd;
		sh->node->cmd->pipefd[0] = saved_pipefd[0];
		sh->node->cmd->pipefd[1] = saved_pipefd[1];
		return (-1);
	}
	execute_pipe_chain_new(all_cmds, sh->pipe_count, envp);
	if (all_cmds)
	{
		for (i = 0; i < sh->pipe_count && all_cmds[i]; i++)
			free_args(all_cmds[i]);
		free(all_cmds);
	}
	sh->pipe_count = saved_pipe_count;
	sh->node->n_cmd = saved_n_cmd;
	sh->node->cmd->pipefd[0] = saved_pipefd[0];
	sh->node->cmd->pipefd[1] = saved_pipefd[1];
	return (0);
}

int	handle_pipes(t_sh *sh, char **envp)
{
	pid_t	*pids;
	int		fd[2];
	int		fd_prev;
	int		i;
	int		status;
	t_cmd	*current_cmd;
	char	*path;

	if (!sh || !sh->node || !sh->node->cmd)
		return (1);
	fd_prev = -1;
	i = 0;
	current_cmd = sh->node->cmd;
	pids = malloc(sizeof(pid_t) * sh->node->n_cmd);
	if (!pids)
		return (1);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (i < sh->node->n_cmd && current_cmd)
	{
		if (i < sh->node->n_cmd - 1)
			if (pipe(fd) == -1)
			{
				free(pids);
				return (1);
			}
		pids[i] = fork();
		if (pids[i] == -1)
		{
			free(pids);
			return (1);
		}
		if (pids[i] == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (i > 0)
			{
				dup2(fd_prev, STDIN_FILENO);
				close(fd_prev);
			}
			if (i < sh->node->n_cmd - 1)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
			}
			if (current_cmd->split_cmd)
			{
				path = get_path(envp, current_cmd->split_cmd[0]);
				if (path)
				{
					execve(path, current_cmd->split_cmd, envp);
					free(path);
				}
				write(2, "Command not found: ", 19);
				write(2, current_cmd->split_cmd[0],
					ft_strlen(current_cmd->split_cmd[0]));
				write(2, "\n", 1);
			}
			exit(EXIT_FAILURE);
		}
		if (i > 0)
			close(fd_prev);
		if (i < sh->node->n_cmd - 1)
		{
			fd_prev = fd[0];
			close(fd[1]);
		}
		current_cmd = current_cmd->next;
		i++;
	}
	for (i = 0; i < sh->node->n_cmd; i++)
	{
		waitpid(pids[i], &status, 0);
		if (i == sh->node->n_cmd - 1)
		{
			if (WIFEXITED(status))
				last_signal_code(WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				last_signal_code(128 + WTERMSIG(status));
		}
	}
	ft_signals();
	free(pids);
	return (0);
}
