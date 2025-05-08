/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:15:19 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/05/08 15:11:56 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	free_built(t_built *built)
{
	if (built->name)
		free(built->name);
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->path)
		free(cmd->path);
	if (cmd->split_cmd)
		free_words(cmd->split_cmd);
}

void	free_red(t_reds *red)
{
	if (red->fd > 0)
		close(red->fd);
	if (red->file)
		free(red->file);
	if (red->type)
		free(red->type);
}

void	free_pipe(t_pipe *w_pipe)
{
	// w_pipe->pids; NO RECUERDO COMO GESTIONAR ESTO JAJAJA
	w_pipe->pipe_count = 0;
	w_pipe->pipe_in = 0;
	w_pipe->pipe_out = 0;
	w_pipe->pipe_pos = 0;
	if (w_pipe->pipefd[1] > 0)
		close (w_pipe->pipefd[1]);
	if (w_pipe->pipefd[0] > 0)
		close (w_pipe->pipefd[0]);
}

void	destroy_node(t_node *node)
{
	if (node->arg)
		free(node->arg);
	if (node->built)
		free_built(node->built);
	if (node->cmd)
		free_cmd(node->cmd);
	if (node->red)
		free_red(node->red);
	if (node->w_pipe)
		free_pipe(node->w_pipe);
	free(node);
}


