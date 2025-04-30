/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:06:23 by jramos-a          #+#    #+#             */
/*   Updated: 2025/04/30 19:06:23 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void free_shell(t_sh *sh)
{
	if (!sh)
		return;
	if (sh->node)
	{
		if (sh->node->cmd)
		{
			if (sh->node->cmd->cmd)
				free(sh->node->cmd->cmd);
			if (sh->node->cmd->args)
				free(sh->node->cmd->args);
			if (sh->node->cmd->line_cmd)
				free(sh->node->cmd->line_cmd);
			if (sh->node->cmd->split_cmd)
				free_args(sh->node->cmd->split_cmd);
			if (sh->node->cmd->path)
				free(sh->node->cmd->path);
			free(sh->node->cmd);
		}
		if (sh->node->built)
		{
			if (sh->node->built->name)
				free(sh->node->built->name);
			free(sh->node->built);
		}
		if (sh->node->red)
		{
			if (sh->node->red->file)
				free(sh->node->red->file);
			if (sh->node->red->type)
				free(sh->node->red->type);
			free(sh->node->red);
		}
		if (sh->node->w_pipe)
		{
			if (sh->node->w_pipe->pids)
				free(sh->node->w_pipe->pids);
			if (sh->node->w_pipe->red)
				free(sh->node->w_pipe->red);
			free(sh->node->w_pipe);
		}
		if (sh->node->arg)
			free(sh->node->arg);
			
		free(sh->node);
	}
	if (sh->prompt)
		free(sh->prompt);
	if (sh->pwd)
		free(sh->pwd);
	free(sh);
}
