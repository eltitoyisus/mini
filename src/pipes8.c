/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:25:56 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/11 15:25:56 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	create_pipe_if_needed(int i, int cmd_count, int pipefd[2])
{
	if (i < cmd_count - 1)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			return (-1);
		}
	}
	return (0);
}

void	handle_pipe_setup_error(t_reds *redirs, char **clean_args, pid_t *pids)
{
	if (redirs)
		free_redirs(redirs);
	if (clean_args)
		free_args(clean_args);
	free(pids);
}

void	setup_pipe(int i, int cmd_count, int pipefd[2])
{
	if (i < cmd_count - 1)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
		}
	}
}

void	setup_pipe_io(int prev_pipe, int pipefd[2], int i, int cmd_count)
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
}

void	execute_pipe_child_process(t_pipe_execution *pipe_exec)
{
	char	*path;

	setup_pipe_io(pipe_exec->prev_pipe, pipe_exec->pipefd, pipe_exec->i,
		pipe_exec->cmd_count);
	apply_redirections(pipe_exec->redirs);
	if (is_builtin(pipe_exec->exec_args[0]))
	{
		exec_builtin(pipe_exec->exec_args, pipe_exec->envp, NULL);
		exit(EXIT_SUCCESS);
	}
	path = get_path(pipe_exec->envp, pipe_exec->exec_args[0]);
	if (path)
	{
		execve(path, pipe_exec->exec_args, pipe_exec->envp);
		free(path);
	}
	printf("Command not found: %s\n", pipe_exec->exec_args[0]);
	exit(EXIT_FAILURE);
}
