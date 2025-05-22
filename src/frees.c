/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:15:19 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/05/22 17:32:11 by jramos-a         ###   ########.fr       */
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
	red->type = -1;
}

void	destroy_node(t_node *node)
{
	if (node->arg)
		free(node->arg);
	if (node->cmd)
		free_cmd(node->cmd);
	node->n_cmd = 0;
	free(node);
}

void	free_parse(t_parse *parse)
{
	parse->is_cmd = false;
	parse->is_flag = false;
	parse->type_token = 0;
	free(parse);
}

// void	destroy_sh(t_sh *sh)
// {
// 	free_words(sh->env);
// 	sh->
// }
