/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:39:59 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/18 10:17:42 by daniel-cast      ###   ########.fr       */
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
		fd = heredoc(redir->file);
	else
		return (-1);
	return (fd);
}

void	process_heredoc_input(int fd, char *delimiter)
{
	char	*line;

	signal(SIGINT, SIG_IGN);
	while (1)
	{
		rl_clear_history();
		line = readline("theredoc> ");
		if (!line)
		{
			free(delimiter);
			break ;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			free(delimiter);
			break ;
		}
		write_to_heredoc(fd, line);
		free(line);
	}
	close(fd);
	// unlink("heredoc.tmp");
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
		close(fd);
		unlink("heredoc.tmp");
		write(1, "\n", 1);
		last_signal_code(130);
		return (-1);
	}
	return (open("heredoc.tmp", O_RDONLY));
}

int	heredoc(char *delimiter)
{
	int		fd;
	pid_t	pid;
	int		result;

	fd = open("heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("heredoc: open");
		return (-1);
	}
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
		return (-1);
	}
	result = handle_heredoc_parent(pid, fd);
	return (result);
}
