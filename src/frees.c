/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:15:19 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/05 00:02:51 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*temp;

	temp = cmd;
	while (cmd != NULL)
	{
		temp = cmd->next;
		if (cmd->cmd)
			free(cmd->cmd);
		// if (cmd->path)
		// 	free(cmd->path);
		if (cmd->split_cmd)
			free_words(cmd->split_cmd);
		if (cmd->red)
			free_red(cmd->red);
		cmd = temp;
	}

}

void	free_red(t_reds *red)
{
	t_reds	*temp;

	temp = red;
	while (red != NULL)
	{
		temp = red->next;
		if (red->fd > 0)
			close(red->fd);
		if (red->file)
			free(red->file);
		red->type = -1;
		red = temp;
	}

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
	parse->is_built_arg = false;
	parse->is_cmd = false;
	parse->is_flag = false;
	parse->type_token = -1;
	free(parse);
}

// void	destroy_sh(t_sh *sh)
// {
// 	free_words(sh->env);
// 	sh->
// }

