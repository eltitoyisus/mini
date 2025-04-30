/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:12:50 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/04/30 16:03:24 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

t_sh	*shell_factory(void)
{
	t_sh	*sh;

	sh = malloc(sizeof(t_sh));
	if (!sh)
		return (NULL);
	sh->prompt = ft_prompt();
	sh->input = NULL;
	sh->node = node_factory();
	sh->pwd = NULL;
	return (sh);
}

t_cmd	*cmd_factory(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->split_cmd = NULL;
	cmd->line_cmd = NULL;
	cmd->path = NULL;
	cmd->cmd = NULL;
	cmd->args = NULL;
	return (cmd);
}

t_node	*node_factory(void)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->cmd = cmd_factory();
	node->built = init_built();
	node->red = init_redir();
	node->w_pipe = init_pipe();
	node->arg = NULL;
	node->next = NULL;
	return (node);
}
