/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:15:19 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/05/13 15:32:31 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	free_cmd(t_cmd *cmd)
{
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->path)
		free(cmd->path);
	if (cmd->split_cmd)
		free_words(cmd->split_cmd);
	if (cmd->red)
		free_red(cmd->red);
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

void	destroy_node(t_node *node)
{
	if (node->arg)
		free(node->arg);
	if (node->cmd)
		free_cmd(node->cmd);
	free(node);
}


