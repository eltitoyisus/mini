/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:39:59 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/22 14:03:35 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	write_to_heredoc(int fd, char *line)
{
	if (!line || fd < 0)
		return ;
	ft_putstr_fd(line, fd);
	ft_putchar_fd('\n', fd);
}

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
		fd = heredoc(redir->file, get_heredoc_state());
	else
		return (-1);
	return (fd);
}

void	process_heredoc_input(int fd, char *delimiter)
{
	char				*line;
	t_heredoc_context	*ctx;

	ctx = get_heredoc_context();
	ctx->fd = fd;
	signal(SIGINT, heredoc_sigint_handler);
	while (1)
	{
		rl_clear_history();
		line = readline("theredoc> ");
		if (handle_heredoc_line(line, delimiter, fd))
			break ;
	}
	close(fd);
	ctx->fd = -1;
}

int	heredoc(char *delimiter, t_heredoc_state *state)
{
	int		fd;
	int		result;
	char	*filename;

	heredoc_cleanup_state(state);
	while (state->active)
		usleep(1000);
	state->active = 1;
	fd = heredoc_open_file(&filename);
	if (fd < 0)
	{
		state->active = 0;
		return (-1);
	}
	result = heredoc_fork_and_wait(fd, delimiter, filename, state);
	free(filename);
	state->active = 0;
	return (result);
}

int	handle_heredoc_parent(pid_t pid, int fd, char *filename,
		t_heredoc_state *state)
{
	int	status;
	int	heredoc_fd;

	close(fd);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	ft_signals();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		unlink(filename);
		write(1, "\n", 1);
		last_signal_code(130);
		cleanup_heredoc_tempfiles();
		return (-1);
	}
	heredoc_fd = open(filename, O_RDONLY);
	if (heredoc_fd < 0)
		perror("heredoc: reopening for read");
	state->last_fd = heredoc_fd;
	return (heredoc_fd);
}
