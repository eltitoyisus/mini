/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:11:23 by jramos-a          #+#    #+#             */
/*   Updated: 2025/04/30 10:14:41 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int has_redirection(char **args)
{
	int i = 0;
	while (args[i])
	{
		if (ft_strncmp(args[i], ">", 2) == 0 || ft_strncmp(args[i], ">>", 3) == 0
			|| ft_strncmp(args[i], "<", 2) == 0 || ft_strncmp(args[i], "<<", 3) == 0)
			return (1);
		i++;
	}
	return (0);
}

int handle_redir_error(char **args)
{
	free_args(args);
	printf("Invalid redirection syntax\n");
	return (1);
}

t_reds *parse_redirection(char **args)
{
	t_reds *redir;
	int i = 0;

	redir = malloc(sizeof(t_reds));
	if (!redir)
		return NULL;
	while (args[i])
	{
		if (ft_strncmp(args[i], ">", 2) == 0 || ft_strncmp(args[i], ">>", 3) == 0
			|| ft_strncmp(args[i], "<", 2) == 0 || ft_strncmp(args[i], "<<", 3) == 0)
		{
			redir->type = ft_strdup(args[i]);
			redir->file = ft_strdup(args[i + 1]);
			args[i] = NULL;
			return redir;
		}
		i++;
	}
	free(redir);
	return (NULL);
}

int open_redir(t_reds *redir)
{
	int fd;

	if (!redir || !redir->file || !redir->type)
		return (-1);
	if (ft_strncmp(redir->type, ">>", 3) == 0)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (ft_strncmp(redir->type, ">", 2) == 0)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (ft_strncmp(redir->type, "<", 2) == 0)
		fd = open(redir->file, O_RDONLY);
	else if (ft_strncmp(redir->type, "<<", 3) == 0)
		heredoc();
	else
		return (-1);
	return (fd);
}

void heredoc()
{
	char *line;
	int fd;

	fd = open("heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("invalid syntax\n");
		return;
	}
	while (1)
	{
		line = readline("theredoc> ");
		if (!line || ft_strncmp(line, "EOF", 3) == 0)
			break;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	free(line);
}

int exec_redir(char **args, char **envp, t_reds *redir)
{
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		if (ft_strncmp(redir->type, ">", 2) == 0 ||
			ft_strncmp(redir->type, ">>", 3) == 0)
			dup2(redir->fd, STDOUT_FILENO);
		else if (ft_strncmp(redir->type, "<", 2) == 0)
			dup2(redir->fd, STDIN_FILENO);
		close(redir->fd);
		execve(get_path(envp, args[0]), args, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	close(redir->fd);
	waitpid(pid, NULL, 0);
	return 0;
}

int do_redir(char *command, char **envp)
{
	char **args = ft_split(command, ' ');
	t_reds *redir;
	int result;

	if (!args)
		return 1;
	redir = parse_redirection(args);
	if (!redir)
		return handle_redir_error(args);
	redir->fd = open_redir(redir);
	if (redir->fd < 0)
	{
		printf("Invalid syntax\n");
		free_args(args);
		free(redir);
		return 1;
	}
	result = exec_redir(args, envp, redir);
	free_args(args);
	free(redir->file);
	free(redir->type);
	free(redir);
	return result;
}

int handle_redirs(char *command, char **envp)
{
	char **args;
	int result;

	args = ft_split(command, ' ');
	if (!args)
		return 1;
	if (has_redirection(args))
		result = do_redir(command, envp);
	else
		result = 0;
	free_args(args);
	return result;
}
