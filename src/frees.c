/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:15:19 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/18 14:39:49 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	free_red(t_reds *head)
{
	t_reds	*current;
	t_reds	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		if (current->file)
			free(current->file);
		if (current->delim)
			free(current->delim);
		if (current->fd >= 0)
		{
			close(current->fd);
			current->fd = -1;
		}
		free(current);
		current = next;
	}
}

void	free_bools(t_type *bools)
{
	if (bools)
		free(bools);
}

void	free_shell(t_sh *sh)
{
	if (!sh)
		return ;
	unlink("heredoc.tmp");
	if (sh->prompt)
		free(sh->prompt);
	if (sh->input)
		free(sh->input);
	if (sh->pwd)
		free(sh->pwd);
	if (sh->env)
		free_env(sh->env);
	if (sh->node)
	{
		if (sh->node->cmd)
			free_cmd(sh->node->cmd);
		if (sh->node->arg)
			free(sh->node->arg);
		if (sh->node->line_is)
			free_bools(sh->node->line_is);
		free(sh->node);
	}
	free(sh);
}
