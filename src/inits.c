/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:42:14 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/04/30 11:26:05 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

// inits

t_reds	*init_redir(void)
{
	t_reds	*red;

	red = malloc(sizeof(t_reds));
	red->fd = -1;
	red->file = NULL;
	red->type = NULL;
	return (red);
}

t_pipe	*init_pipe(void)
{
	t_pipe	*pipe_info;

	pipe_info = malloc(sizeof(t_pipe));
	pipe_info->pipefd[0] = -1;
	pipe_info->pipefd[1] = -1;
	pipe_info->pipe_count = 0;
	pipe_info->pipe_pos = -1;
	pipe_info->pipe_in = -1;
	pipe_info->pipe_out = -1;
	pipe_info->red = NULL;
	return (pipe_info);
}

t_built	*init_built(void)
{
	t_built	*built;

	built = malloc(sizeof(t_built));
	built->name = NULL;
	return (built);
}



