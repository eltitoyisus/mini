/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:05:12 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/09 18:05:12 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	setup_pipe_execution(t_sh *sh, pid_t **pids, int *fd_prev,
		t_cmd **current_cmd)
{
	if (!sh || !sh->node || !sh->node->cmd)
		return (1);
	*fd_prev = -1;
	*current_cmd = sh->node->cmd;
	*pids = malloc(sizeof(pid_t) * sh->node->n_cmd);
	if (!*pids)
		return (1);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

int	create_pipe_for_command(t_sh *sh, int i, int fd[2], pid_t *pids)
{
	if (i < sh->node->n_cmd - 1)
	{
		if (pipe(fd) == -1)
		{
			free(pids);
			return (1);
		}
	}
	return (0);
}

t_pipe_cmd_args	init_pipe_cmd_args(t_pipe_handle *ph, t_sh *sh, char **envp)
{
	t_pipe_cmd_args	args;

	args.i = ph->i;
	args.sh = sh;
	args.fd_prev = ph->fd_prev;
	args.fd[0] = ph->fd[0];
	args.fd[1] = ph->fd[1];
	args.current_cmd = ph->current_cmd;
	args.envp = envp;
	return (args);
}

int	fork_pipe_command(pid_t *pids, int i)
{
	pids[i] = fork();
	if (pids[i] == -1)
		return (1);
	return (0);
}

void	handle_pipe_parent_cleanup(int *fd_prev, int fd[2], int i, t_sh *sh)
{
	if (i > 0)
		close(*fd_prev);
	if (i < sh->node->n_cmd - 1)
	{
		*fd_prev = fd[0];
		close(fd[1]);
	}
}
