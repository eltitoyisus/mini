/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:12:50 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/05/08 17:25:12 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

t_cmd	*cmd_factory(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->cmd = NULL;
	cmd->split_cmd = NULL;
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
	node->is_cmd = false;
	node->is_flag = false;
	node->arg = NULL;
	node->head = NULL;
	node->next = NULL;
	return (node);
}

t_sh	*shell_factory(char **envp)
{
	t_sh	*sh;

	sh = malloc(sizeof(t_sh));
	sh->prompt = ft_prompt();
	sh->input = NULL;
	sh->node = node_factory();
	sh->node->head = sh->node;
	sh->env = envp;
	sh->pipe_count = 0;
	return (sh);
}
