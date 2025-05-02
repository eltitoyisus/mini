/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsts_sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:09:21 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/05/01 16:32:59 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

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

void	ft_lstclear_sh(t_sh *sh, t_node *temp)
{
	sh->node = temp;
	if (!temp || !sh->node)
		return ;
	while (sh->node != NULL)
	{
		temp = sh->node->next;
		destroy_node(sh->node);
		sh->node = temp;
	}
}
