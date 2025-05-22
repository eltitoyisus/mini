/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:42:14 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/05/15 16:46:44 by daniel-cast      ###   ########.fr       */
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
	parse->head = parse;
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
	return (red);
}


