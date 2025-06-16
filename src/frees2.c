/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:21:47 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/16 21:21:47 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

t_cmd	*find_list_head(t_cmd *cmd)
{
	t_cmd	*list_head;

	if (cmd->head)
		list_head = cmd->head;
	else
	{
		list_head = cmd;
		while (list_head->prev)
			list_head = list_head->prev;
	}
	return (list_head);
}

void	free_cmd_resources(t_cmd *current)
{
	if (current->cmd)
		free(current->cmd);
	if (current->path)
		free(current->path);
	if (current->split_cmd)
		free_words(current->split_cmd);
	if (current->red)
		free_red(current->red);
	if (current->pids)
		free(current->pids);
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*current;
	t_cmd	*next;
	t_cmd	*list_head;

	if (!cmd)
		return ;
	list_head = find_list_head(cmd);
	current = list_head;
	while (current != NULL)
	{
		next = current->next;
		free_cmd_resources(current);
		free(current);
		current = next;
	}
}

void	destroy_node(t_node *node)
{
	if (node->arg)
		free(node->arg);
	if (node->cmd)
		free_cmd(node->cmd);
	node->n_cmd = 0;
	free(node);
}

void	free_parse(t_parse *parse)
{
	if (parse->line)
		free(parse->line);
	parse->is_cmd = false;
	parse->is_flag = false;
	parse->type_token = 0;
	free(parse);
}
