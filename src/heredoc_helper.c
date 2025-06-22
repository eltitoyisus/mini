/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:35:38 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/22 13:35:38 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

t_heredoc_state	*get_heredoc_state(void)
{
	static t_heredoc_state	state = {0, -1, NULL};

	return (&state);
}

void	heredoc_cleanup_state(t_heredoc_state *state)
{
	if (state->last_fd != -1)
	{
		close(state->last_fd);
		state->last_fd = -1;
	}
	if (state->last_filename)
	{
		unlink(state->last_filename);
		free(state->last_filename);
		state->last_filename = NULL;
	}
}

int	handle_heredoc_line(char *line, char *delimiter, int fd)
{
	if (!line)
	{
		free(delimiter);
		return (1);
	}
	if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
	{
		free(line);
		free(delimiter);
		return (1);
	}
	write_to_heredoc(fd, line);
	free(line);
	return (0);
}

int	heredoc_open_file(char **filename)
{
	int	fd;

	*filename = generate_heredoc_filename(0);
	fd = open(*filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("heredoc: open");
		free(*filename);
		*filename = NULL;
	}
	return (fd);
}

int	heredoc_fork_and_wait(int fd, char *delimiter, char *filename,
		t_heredoc_state *state)
{
	pid_t	pid;
	int		result;

	pid = fork();
	if (pid == 0)
	{
		process_heredoc_input(fd, delimiter);
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
	{
		perror("heredoc: fork");
		close(fd);
		free(delimiter);
		free(filename);
		state->active = 0;
		return (-1);
	}
	result = handle_heredoc_parent(pid, fd, filename, state);
	if (result >= 0)
		state->last_filename = ft_strdup(filename);
	return (result);
}
