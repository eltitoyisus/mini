/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 20:21:27 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/09 20:21:27 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static int	add_redirection_node(t_reds **head, t_reds **current, char **args,
		int i)
{
	t_reds	*new;

	new = create_redir_node(args, i);
	if (!new)
		return (0);
	if (!(*head))
		*head = new;
	else
		(*current)->next = new;
	*current = new;
	return (1);
}

static t_reds	*init_redirection_list(void)
{
	return (NULL);
}

static t_reds	*process_redirection_args(char **args)
{
	t_reds	*head;
	t_reds	*current;
	int		i;

	head = init_redirection_list();
	current = NULL;
	i = 0;
	while (args[i])
	{
		if (is_redir_with_target(args, i))
		{
			if (!add_redirection_node(&head, &current, args, i))
			{
				free_redirs(head);
				return (NULL);
			}
			i += 2;
		}
		else
			i++;
	}
	return (head);
}

t_reds	*parse_redirection(char **args)
{
	return (process_redirection_args(args));
}
