/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:00:00 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/22 13:59:42 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

t_heredoc_context	*get_heredoc_context(void)
{
	static t_heredoc_context	ctx;

	return (&ctx);
}

void	heredoc_sigint_handler(int signum)
{
	t_heredoc_context	*ctx;

	(void)signum;
	ctx = get_heredoc_context();
	if (ctx->fd != -1)
		close(ctx->fd);
	_exit(130);
}

void	cleanup_heredoc_tempfiles(void)
{
	int		i;
	char	buffer[32];

	i = 0;
	while (1)
	{
		ft_snprintf(buffer, sizeof(buffer), "heredoc_%d.tmp", i);
		if (unlink(buffer) != 0)
			break ;
		i++;
	}
}

char	*generate_heredoc_filename(int index)
{
	char	buffer[32];

	ft_snprintf(buffer, sizeof(buffer), "heredoc_%d.tmp", index);
	return (ft_strdup(buffer));
}
