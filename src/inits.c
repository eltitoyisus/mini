/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:42:14 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/05/27 19:07:45 by dacastil         ###   ########.fr       */
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
	parse->quote_error = 0;
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

t_type	*init_bools(void)
{
	t_type	*new;

	new = malloc(sizeof(t_type));
	new->built = false;
	new->cmd = false;
	new->with_pipe = false;
	new->with_reds = false;
	return (new);
}
