/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_chain2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:44:32 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/21 13:57:08 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char	**select_exec_args(char **clean_args, char **commands_i)
{
	if (clean_args)
		return (clean_args);
	return (commands_i);
}

void	initialize_pipe_command(t_pipe_command_args *args, t_cmd *temp_cmd,
		t_reds **redirs, char ***clean_args)
{
	*redirs = NULL;
	*clean_args = NULL;
	prepare_pipe_command(temp_cmd, args->commands[args->i], redirs, clean_args);
}

int	create_pipe_and_fork(t_pipe_command_args *args, int pipefd[2],
		t_reds *redirs, char **clean_args)
{
	setup_pipe(args->i, args->cmd_count, pipefd);
	if (args->i < args->cmd_count - 1 && (pipefd[0] == -1 || pipefd[1] == -1))
	{
		handle_pipe_setup_error(redirs, clean_args, args->pids);
		return (-1);
	}
	args->pids[args->i] = fork();
	if (args->pids[args->i] == -1)
	{
		handle_pipe_fork_error(args->pids, redirs, clean_args);
		return (-1);
	}
	return (args->pids[args->i]);
}

void	handle_child_process(t_pipe_command_args *args, int pipefd[2],
		t_reds *redirs, char **exec_args)
{
	t_pipe_execution	pipe_exec;

	pipe_exec.i = args->i;
	pipe_exec.cmd_count = args->cmd_count;
	pipe_exec.prev_pipe = *(args->prev_pipe);
	pipe_exec.pipefd[0] = pipefd[0];
	pipe_exec.pipefd[1] = pipefd[1];
	pipe_exec.redirs = redirs;
	pipe_exec.exec_args = exec_args;
	pipe_exec.pids = args->pids;
	pipe_exec.envp = args->envp;
	execute_pipe_child_process(&pipe_exec);
}

void	process_pipe_command(t_pipe_command_args *args)
{
	int					pipefd[2];
	t_reds				*redirs;
	char				**clean_args;
	t_cmd				temp_cmd;
	t_parent_cleanup	cleanup;

	initialize_pipe_command(args, &temp_cmd, &redirs, &clean_args);
	if (create_pipe_and_fork(args, pipefd, redirs, clean_args) == 0)
	{
		handle_child_process(args, pipefd, redirs, select_exec_args(clean_args,
				args->commands[args->i]));
	}
	cleanup.redirs = &redirs;
	cleanup.clean_args = &clean_args;
	cleanup.prev_pipe = args->prev_pipe;
	cleanup.pipefd[0] = pipefd[0];
	cleanup.pipefd[1] = pipefd[1];
	cleanup.i = args->i;
	cleanup.cmd_count = args->cmd_count;
	handle_parent_cleanup(&cleanup);
}
