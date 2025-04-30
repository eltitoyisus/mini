/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:12:50 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/04/30 11:32:52 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

t_cmd	*cmd_factory(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->args = NULL;
	cmd->cmd = NULL;
	cmd->line_cmd = NULL;
	cmd->split_cmd = NULL;
	cmd->w_pipe = init_pipe();
	return (cmd);
}

t_node	*node_factory(void)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->cmd = cmd_factory();
	node->built = init_built();
	node->red = init_redir();
	node->next = NULL;
	return (node);
}

t_sh	*shell_factory(void)
{
	t_sh	*sh;

	sh = malloc(sizeof(t_sh));
	sh->prompt = ft_prompt();
	sh->input = NULL;
	sh->node = node_factory();
	sh->pwd = getenv("PWD");
	return (sh);
}
