/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:51:21 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/05/27 20:08:54 by dacastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	find_cmd(t_parse *parse)
{
	t_parse	*node_count;

	node_count = parse;
	while (node_count != NULL)
	{
		if (node_count->is_cmd == true)
			return (1);
		node_count = node_count->next;
	}
	return (0);
}

void	add_flag(t_sh *sh, char *flag)
{
	int		i;
	char	**new_split;

	i = 1;
	new_split = sh->node->cmd->split_cmd;
	new_split[i] = ft_strdup(flag);
	i += 1;
	new_split[i] = NULL;
	sh->node->cmd->split_cmd = new_split;
	return ;
}

void	type_red_pipe_2(t_sh *sh, t_parse *parse, int i)
{
	if (parse->type_token == RED)
	{
		sh->node->cmd->red->type = id_red(parse);
		sh->node->line_is->with_reds = true;
	}
	else if (parse->type_token == FILES)
	{
		sh->node->line_is->with_reds = true;
		sh->node->cmd->red->type = id_file(parse);
		if (sh->node->cmd->red->type == DELIM)
			sh->node->cmd->red->delim = ft_strdup(parse->line);
		else
			sh->node->cmd->red->file = ft_strdup(parse->line);
	}
	else if (parse->type_token == PIPE)
	{
		sh->node->line_is->with_pipe = true;
		sh->node->n_cmd += 1;
		if (sh->node->n_cmd == 2)
			sh->node->cmd->pipe_in = i;
		else
			sh->node->cmd->pipe_out = i;
		pipe(sh->node->cmd->pipefd);
		ft_lstadd_back_cmd(sh->node->cmd);
	}
}
