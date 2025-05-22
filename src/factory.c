/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:12:50 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/05/21 18:53:01 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

t_cmd	*cmd_factory(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->cmd = NULL;
	cmd->split_cmd = NULL;
	cmd->path = NULL;
	cmd->red = init_redir();
	cmd->pids =	NULL;
	cmd->pipefd[1] = -1;
	cmd->pipefd[0] = -1;
	cmd->pipe_in = 0;
	cmd->pipe_out = 0;
	cmd->index_token = -1;
	cmd->next = NULL;
	cmd->head = NULL;
	return (cmd);
}

t_node	*node_factory(void)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->cmd = cmd_factory();
	node->is_cmd = false;
	node->is_flag = false;
	node->is_quote = false;
	node->is_built = false;
	node->n_cmd = 1;
	node->arg = NULL;
	return (node);
}

t_sh	*shell_factory(char **envp)
{
	t_sh	*sh;

	sh = malloc(sizeof(t_sh));
	sh->prompt = ft_prompt();
	sh->input = NULL;
	sh->node = node_factory();
	sh->env = envp;
	sh->pipe_count = 0;
	return (sh);
}
