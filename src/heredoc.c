/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:39:59 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/09 18:39:59 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	open_redir(t_reds *redir)
{
	int	fd;

	if (!redir || !redir->file)
		return (-1);
	if (redir->type == D_OURED)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->type == OURED)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == INRED)
		fd = open(redir->file, O_RDONLY);
	else if (redir->type == HEREDOC)
		fd = heredoc(redir->file);
	else
		return (-1);
	return (fd);
}

void	process_heredoc_input(int fd, char *delimiter)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("theredoc> ");
		if (!line)
			exit(1);
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			exit(0);
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

int	handle_heredoc_parent(pid_t pid, int fd)
{
	int	status;

	close(fd);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	ft_signals();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		last_signal_code(130);
		unlink("heredoc.tmp");
		return (-1);
	}
	return (open("heredoc.tmp", O_RDONLY));
}

int	heredoc(char *delimiter)
{
	int		fd;
	pid_t	pid;

	fd = open("heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("heredoc: open");
		return (-1);
	}
	pid = fork();
	if (pid == 0)
		process_heredoc_input(fd, delimiter);
	return (handle_heredoc_parent(pid, fd));
}
