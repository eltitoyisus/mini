/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_chain.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 20:46:59 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/21 12:54:27 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	handle_pipe_fork_error(pid_t *pids, t_reds *redirs, char **clean_args)
{
	perror("fork");
	if (redirs)
		free_redirs(redirs);
	if (clean_args)
		free_args(clean_args);
	free(pids);
	unlink("heredoc.tmp");
}

void	prepare_pipe_command(t_cmd *temp_cmd, char **commands_i,
		t_reds **redirs, char ***clean_args)
{
	temp_cmd->split_cmd = commands_i;
	handle_redirections(temp_cmd, redirs, clean_args);
}

void	execute_pipe_chain_new(char ***commands, int cmd_count, char **envp)
{
	int					prev_pipe;
	pid_t				*pids;
	int					i;
	t_pipe_command_args	args;

	initialize_pipe_chain(cmd_count, &pids, &prev_pipe);
	if (!pids)
		return ;
	i = 0;
	while (i < cmd_count)
	{
		args.i = i;
		args.cmd_count = cmd_count;
		args.commands = commands;
		args.envp = envp;
		args.pids = pids;
		args.prev_pipe = &prev_pipe;
		process_pipe_command(&args);
		i++;
	}
	wait_for_children(pids, cmd_count);
}
