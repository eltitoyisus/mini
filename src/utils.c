/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:24:15 by jramos-a          #+#    #+#             */
/*   Updated: 2025/03/26 11:24:15 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"
#include <readline/readline.h>

void base_error(void);

void do_pipe(int *fd, int *fd2)
{
	if (pipe(fd) == -1)
		base_error();
	if (pipe(fd2) == -1)
		base_error();
}

void do_here_doc(char *str)
{
	int		fd;
	char	*line;

	fd = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		base_error();
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(line, str, ft_strlen(str)))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
}

void do_redir(char *file, int flags)
{
	int	fd;

	fd = open(file, flags, 0644);
	if (fd == -1)
		base_error();
	dup2(fd, 1);
	close(fd);
}


void do_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
}

