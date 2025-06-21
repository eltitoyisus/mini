/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:41:29 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/21 13:30:47 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static void	setup_pipe_redirections(int i, t_sh *sh, int fd_prev, int fd[2])
{
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
}

static void	execute_command(t_cmd *current_cmd, char **envp)
{
	char	*path;

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

void	execute_pipe_command(t_pipe_cmd_args args)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	setup_pipe_redirections(args.i, args.sh, args.fd_prev, args.fd);
	execute_command(args.current_cmd, args.envp);
}
