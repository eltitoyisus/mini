/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:15:19 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/11 18:57:52 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	free_red(t_reds *red)
{
	t_reds	*current;
	t_reds	*next;

	current = red;
	while (current)
	{
		next = current->next;
		if (current->file)
			free(current->file);
		if (current->delim)
			free(current->delim);
		free(current);
		current = next;
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!cmd)
		return ;
	if (cmd->head)
		current = cmd->head;
	else
		current = cmd;
	while (current != NULL)
	{
		next = current->next;
		free(current->cmd);
		free(current->path);
		free_words(current->split_cmd);
		free_red(current->red);
		free(current->pids);
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

void	free_shell(t_sh *sh)
{
	if (!sh)
		return ;
	if (sh->prompt)
		free(sh->prompt);
	if (sh->input)
		free(sh->input);
	if (sh->node)
	{
		if (sh->node->cmd)
			free_cmd(sh->node->cmd);
		if (sh->node->arg)
			free(sh->node->arg);
		if (sh->node->line_is)
			free(sh->node->line_is);
		free(sh->node);
	}
	free(sh);
}
