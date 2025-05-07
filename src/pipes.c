/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:11:40 by jramos-a          #+#    #+#             */
/*   Updated: 2025/05/07 19:37:51 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	is_pipe(char **args)
{
	int	i = 0;

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
	int	i = 0;
	int	count = 0;

	while (args[i])
	{
		if (ft_strncmp(args[i], "|", 2) == 0)
			count++;
		i++;
	}
	return (count);
}

static void free_commands(char ***commands, int k)
{
	int i = 0;
	int j;

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

char ***split_command(char **args, int num_cmds)
{
	char ***commands;
	int i = 0;
	int j = 0;
	int k = 0;
	int start = 0;
	int len;

	commands = malloc(sizeof(char **) * (num_cmds + 1));
	if (!commands)
		return (NULL);
	while (args[j])
	{
		if (ft_strncmp(args[j], "|", 2) == 0 || args[j + 1] == NULL)
		{
			if (args[j + 1] == NULL)
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

void pipe_command(char **args, char **envp)
{
	char *path;

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

void	execute_pipe_chain(t_pipe *pipe_info, char ***cmds, char **envp)
{
	int	i = 0;
	int	fd_prev = -1;
	int	fd[2];

	while (i < pipe_info->pipe_count)
	{
		if (i < pipe_info->pipe_count - 1)
			if (pipe(fd) == -1)
				exit(EXIT_FAILURE);
		pipe_info->pids[i] = fork();
		if (pipe_info->pids[i] == 0)
		{
			if (i > 0)
			{
				dup2(fd_prev, STDIN_FILENO);
				close(fd_prev);
			}
			if (i < pipe_info->pipe_count - 1)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
			}
			pipe_command(cmds[i], envp);
		}
		if (i > 0)
			close(fd_prev);
		if (i < pipe_info->pipe_count - 1)
		{
			fd_prev = fd[0];
			close(fd[1]);
		}
		i++;
	}
	i = 0;
	int status;
	while (i < pipe_info->pipe_count)
	{
		waitpid(pipe_info->pids[i], &status, 0);
		if (i == pipe_info->pipe_count - 1)
		{
			if (WIFEXITED(status))
				last_signal_code(WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				last_signal_code(128 + WTERMSIG(status));
		}
		i++;
	}
}

int do_pipe(char **argv, char **envp)
{
	t_pipe pipe_info;
	char ***all_cmds;
	int i = 0;

	pipe_info.pipe_count = count_pipes(argv) + 1;
	pipe_info.pids = malloc(sizeof(pid_t) * pipe_info.pipe_count);
	if (!pipe_info.pids)
		return (-1);
	pipe_info.pipefd[0] = -1;
	pipe_info.pipefd[1] = -1;
	pipe_info.pipe_pos = -1;
	pipe_info.pipe_in = -1;
	pipe_info.pipe_out = -1;
	all_cmds = split_command(argv, pipe_info.pipe_count);
	if (!all_cmds)
	{
		free(pipe_info.pids);
		return (-1);
	}
	execute_pipe_chain(&pipe_info, all_cmds, envp);
	while (i < pipe_info.pipe_count)
	{
		free_args(all_cmds[i]);
		i++;
	}
	free(all_cmds);
	free(pipe_info.pids);
	return (0);
}

int	handle_pipes(char *command, char **envp)
{
	char	**args;
	int		result = 0;

	args = ft_split(command, ' ');
	if (!args)
		return (1);
	if (is_pipe(args))
		result = do_pipe(args, envp);
	free_args(args);
	return (result);
}
