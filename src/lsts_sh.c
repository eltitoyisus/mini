/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsts_sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:09:21 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/05/09 16:54:15 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	ft_lstadd_back_parse(t_node *node)
{
	t_cmd	*new;
	t_node	*last;

	new = cmd_factory();
	if (!node->cmd || !new)
		return ;
	if (node->cmd == NULL)
	{
		node->cmd = new;
		return ;
	}
	last = node->cmd;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}

void	ft_lstadd_back_parse(t_parse *parse)
{
	t_parse *new;
	t_parse	*last;

	new = init_parse();
	if (!parse || !new)
		return ;
	if (parse == NULL)
	{
		parse = new;
		return ;
	}
	last = parse;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}

void	ft_lstadd_back_sh(t_sh *sh)
{
	t_node *new;
	t_node	*last;

	new = node_factory();
	if (!sh->node || !new)
		return ;
	if (sh->node == NULL)
	{
		sh->node = new;
		return ;
	}
	last = sh->node;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}

void	ft_lstclear_sh(t_sh *sh)
{
	sh->node = sh->node->head;
	if (!sh->node->head || !sh->node)
		return ;
	while (sh->node != NULL)
	{
		sh->node->head = sh->node->next;
		destroy_node(sh->node);
		sh->node = sh->node->head;
	}
}
