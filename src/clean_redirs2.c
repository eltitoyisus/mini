/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_redirs2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:37:44 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/15 22:47:29 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	add_redir_to_list(t_reds **head, t_reds **current, t_reds *new)
{
	if (!*head)
		*head = new;
	else
		(*current)->next = new;
	*current = new;
}

t_reds	*handle_redirection_op(t_reds *head, t_reds **current, char **cmd_array,
		int *i)
{
	t_reds	*new;

	new = create_redirection_node(cmd_array, *i);
	if (!new)
	{
		free_red(head);
		return (NULL);
	}
	add_redir_to_list(&head, current, new);
	*i += 2;
	return (head);
}

t_reds	*parse_redirection_from_cmd(t_cmd *cmd)
{
	t_reds	*head;
	t_reds	*current;
	int		i;

	if (!cmd || !cmd->split_cmd)
		return (NULL);
	head = NULL;
	current = NULL;
	i = 0;
	while (cmd->split_cmd[i])
	{
		if (is_redirection_op(cmd->split_cmd, i))
		{
			head = handle_redirection_op(head, &current, cmd->split_cmd, &i);
			if (!head)
				return (NULL);
		}
		else
			i++;
	}
	return (head);
}
