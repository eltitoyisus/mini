/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:11:23 by jramos-a          #+#    #+#             */
/*   Updated: 2025/04/25 10:11:23 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int has_redirection(char **args)
{
	int i = 0;
	while (args[i])
	{
		if (ft_strncmp(args[i], ">", 2) == 0
			|| ft_strncmp(args[i], ">>", 3) == 0)
			return (1);
		i++;
	}
	return (0);
}

int open_redir(char *filename, char *type)
{
	int fd;

	if (ft_strncmp(type, ">>", 3) == 0)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (0);
	return (fd);
}

int handle_redir_error(char **args)
{
	free_args(args);
	fprintf(stderr, "Invalid redirection syntax\n");
	return (1);
}

int exec_redir(char **args, char **envp, int fd)
{
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("fork");
		close(fd);
		free_args(args);
		return (1);
	}
	if (pid == 0)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			perror("dup2");
		close(fd);
		execve(get_path(envp, args[0]), args, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	close(fd);
	free_args(args);
	waitpid(pid, NULL, 0);
	return (0);
}

int do_redir(char *command, char **envp)
{
	char **args;
	int pos, fd;

	args = ft_split(command, ' ');
	if (!args)
		return (1);
	pos = has_redirection(args);
	if (!pos || !args[pos + 1])
		return handle_redir_error(args);
	fd = open_redir(args[pos + 1], args[pos]);
	if (fd < 0)
		return (1);
	args[pos] = NULL;
	return exec_redir(args, envp, fd);
}

int handle_redirs(char *command, char **envp)
{
	char **args;
	int result;

	result = 0;
	args = ft_split(command, ' ');
	if (!args)
		return 1;
	if (has_redirection(args))
		result = do_redir(command, envp);
	free_args(args);
	return (result);
}
