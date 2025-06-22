/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:03:31 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/22 12:52:15 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	initialize_pipe_chain(int cmd_count, pid_t **pids, int *prev_pipe)
{
	*pids = malloc(sizeof(pid_t) * cmd_count);
	if (!*pids)
		return ;
	*prev_pipe = -1;
}

void	handle_redirections(t_cmd *temp_cmd, t_reds **redirs,
		char ***clean_args)
{
	if (has_redirection_in_cmd(temp_cmd))
	{
		*redirs = parse_redirection_from_cmd(temp_cmd);
		if (*redirs)
		{
			if (open_all_redirs(*redirs) >= 0)
			{
				*clean_args = clean_cmd_args(temp_cmd);
			}
		}
	}
}

void	apply_redirections(t_reds *redirs)
{
	t_reds	*current;

	if (!redirs)
		return ;
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

void	initialize_cleanup(t_parent_cleanup *cleanup, t_pipe_command_args *args,
		int pipefd[2], t_cleanup_args *output)
{
	cleanup->prev_pipe = args->prev_pipe;
	cleanup->pipefd[0] = pipefd[0];
	cleanup->pipefd[1] = pipefd[1];
	cleanup->i = args->i;
	cleanup->cmd_count = args->cmd_count;
	cleanup->redirs = output->redirs;
	cleanup->clean_args = output->clean_args;
}

void	handle_parent_cleanup(t_parent_cleanup *cleanup)
{
	if (*cleanup->prev_pipe != -1)
		close(*cleanup->prev_pipe);
	if (cleanup->i < cleanup->cmd_count - 1)
	{
		*cleanup->prev_pipe = cleanup->pipefd[0];
		close(cleanup->pipefd[1]);
	}
	if (*cleanup->redirs)
	{
		free_redirs(*cleanup->redirs);
		*cleanup->redirs = NULL;
	}
	if (*cleanup->clean_args)
	{
		free_args(*cleanup->clean_args);
		*cleanup->clean_args = NULL;
	}
}
