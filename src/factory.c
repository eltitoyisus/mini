/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:12:50 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/05/27 10:08:11 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

t_cmd	*cmd_factory(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->split_cmd = NULL;
	cmd->path = NULL;
	cmd->cmd = NULL;
	cmd->index_token = 0;
	cmd->red = NULL;
	cmd->pids = NULL;
	cmd->pipefd[0] = 0;
	cmd->pipefd[1] = 0;
	cmd->pipe_in = 0;
	cmd->pipe_out = 1;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->head = NULL;
	return (cmd);
}

t_node	*node_factory(void)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->cmd = cmd_factory();
	node->is_quote = false;
	node->n_cmd = 1;
	node->arg = NULL;
	node->line_is = init_bools();
	return (node);
}

t_sh	*shell_factory(char **envp)
{
	t_sh	*sh;

	sh = malloc(sizeof(t_sh));
	if (!sh)
		return (NULL);
	sh->prompt = ft_prompt();
	sh->input = NULL;
	sh->node = node_factory();
	sh->pwd = NULL;
	sh->env = envp;
	sh->pipe_count = 0;
	return (sh);
}
