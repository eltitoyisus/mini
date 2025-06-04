/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:42:14 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/04 14:30:21 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

t_parse	*init_parse(void)
{
	t_parse	*parse;

	parse = malloc(sizeof(t_parse));
	parse->is_cmd = false;
	parse->is_flag = false;
	parse->line = NULL;
	parse->next = NULL;
	parse->prev = NULL;
	return (parse);
}

t_reds	*init_redir(void)
{
	t_reds	*red;

	red = malloc(sizeof(t_reds));
	red->fd = -1;
	red->file = NULL;
	red->delim = NULL;
	red->type = -1;
	red->next = NULL;
	red->prev = NULL;
	return (red);
}

t_type	*init_bools(void)
{
	t_type	*new;

	new = malloc(sizeof(t_type));
	new->built = malloc(sizeof(bool));
	new->built = false;
	new->cmd = malloc(sizeof(bool));
	new->cmd = false;
	new->with_pipe = malloc(sizeof(bool));
	new->with_pipe = false;
	new->with_reds = malloc(sizeof(bool));
	new->with_reds = false;
	return (new);
}



