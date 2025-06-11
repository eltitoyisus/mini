/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsts_sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:09:21 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/11 16:12:46 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	ft_lstadd_back_cmd(t_cmd *cmd)
{
	t_cmd	*new;
	t_cmd	*last;

	new = cmd_factory();
	if (!cmd || !new)
		return ;
	if (cmd->head == NULL)
	{
		cmd->head = new;
		new->prev = NULL;
		new->next = NULL;
		return ;
	}
	last = cmd;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	new->prev = last;
	new->next = NULL;
}

void	ft_lstadd_back_parse(t_parse *parse)
{
	t_parse	*new;
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
	new->prev = last;
}

void	ft_lstclear_parse(t_parse *parse)
{
	t_parse	*temp;

	if (!parse)
		return ;
	while (parse != NULL)
	{
		temp = parse->next;
		free_parse(parse);
		parse = temp;
	}
}
