/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:11:40 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/15 16:00:59 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	wait_for_children(pid_t *pids, int cmd_count)
{
	int	status;
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &status, 0);
		if (i == cmd_count - 1)
		{
			if (WIFEXITED(status))
				last_signal_code(WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				last_signal_code(128 + WTERMSIG(status));
		}
		i++;
	}
	free(pids);
}

int	process_piped_command(t_sh *sh, char **envp)
{
	t_pipe_vars	vars;
	char		***commands;
	int			cmd_idx;
	int			i;

	i = 0;
	init_pipe_command_vars(sh, &vars);
	commands = allocate_commands_array(vars.pipe_count);
	if (!commands)
		return (1);
	cmd_idx = parse_command_segments(commands, vars.cmd_args, vars.pipe_count);
	if (cmd_idx < 0)
		return (1);
	execute_pipe_chain_new(commands, cmd_idx, envp);
	while (i < cmd_idx)
		free_args(commands[i++]);
	free(commands);
	return (0);
}

void	wait_for_pipe_commands(pid_t *pids, int cmd_count)
{
	int	status;
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &status, 0);
		if (i == cmd_count - 1)
		{
			if (WIFEXITED(status))
				last_signal_code(WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				last_signal_code(128 + WTERMSIG(status));
		}
		i++;
	}
	ft_signals();
	free(pids);
}

void	process_pipe_commands(t_pipe_handle *ph, t_sh *sh, char **envp)
{
	t_pipe_cmd_args	args;

	while (ph->i < sh->node->n_cmd && ph->current_cmd)
	{
		if (create_pipe_for_command(sh, ph->i, ph->fd, ph->pids))
			return ;
		if (fork_pipe_command(ph->pids, ph->i))
			return ;
		if (ph->pids[ph->i] == 0)
		{
			args = init_pipe_cmd_args(ph, sh, envp);
			execute_pipe_command(args);
		}
		handle_pipe_parent_cleanup(&ph->fd_prev, ph->fd, ph->i, sh);
		ph->current_cmd = ph->current_cmd->next;
		ph->i++;
	}
}

int	handle_pipes(t_sh *sh, char **envp)
{
	t_pipe_handle	ph;

	ph.i = 0;
	if (setup_pipe_execution(sh, &ph.pids, &ph.fd_prev, &ph.current_cmd))
		return (1);
	process_pipe_commands(&ph, sh, envp);
	if (!ph.i && !ph.current_cmd)
		free(ph.pids);
	else
		wait_for_pipe_commands(ph.pids, sh->node->n_cmd);
	return (0);
}
