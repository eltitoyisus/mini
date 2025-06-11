/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:59:18 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/11 18:59:18 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	handle_built_token(t_sh *sh, t_parse *parse)
{
	if (sh->node->arg)
		free(sh->node->arg);
	sh->node->arg = ft_strdup(parse->line);
	sh->node->line_is->built = true;
}

void	handle_cmd_token(t_sh *sh, t_parse *parse, int i, int *j)
{
	if (*j > 0)
		ft_lstadd_back_cmd(sh->node->cmd);
	sh->node->cmd->cmd = ft_strdup(parse->line);
	sh->node->cmd->path = find_path(sh->env);
	sh->node->line_is->cmd = true;
	sh->node->cmd->split_cmd = ft_split(sh->node->cmd->cmd, ' ');
	free_words(sh->node->cmd->split_cmd);
	sh->node->cmd->split_cmd = NULL;
	sh->node->cmd->index_token = i;
	(*j)++;
}

void	type_cmd_built_2(t_sh *sh, t_parse *parse, int i)
{
	int	j;

	j = 0;
	if (parse->type_token == BUILT)
		handle_built_token(sh, parse);
	else if (parse->type_token == CMD)
		handle_cmd_token(sh, parse, i, &j);
	else if (parse->type_token == FLAG && find_cmd(parse))
	{
		parse->is_flag = true;
		add_flag(sh, parse->line);
	}
}
