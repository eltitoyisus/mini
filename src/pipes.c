/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:11:40 by jramos-a          #+#    #+#             */
/*   Updated: 2025/04/25 10:11:40 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int is_pipe(char **args)
{
	int i = 0;
	while (args[i])
	{
		if (ft_strncmp(args[i], "|", 2) == 0)
			return (i);
		i++;
	}
	return 0;
}

char **split_args(char **argv, int pipe_pos)
{
	int count = 0;
	int i = 0;
	char **right_args;

	while (argv[pipe_pos + 1 + count])
		count++;
	right_args = malloc(sizeof(char *) * (count + 1));
	if (!right_args)
		return NULL;
	while (i < count)
	{
		right_args[i] = ft_strdup(argv[pipe_pos + 1 + i]);
		i++;
	}
	right_args[i] = NULL;
	argv[pipe_pos] = NULL;
	return right_args;
}

void pipe_command(char **args, char **envp)
{
	char *path;

	if (is_builtin(args[0]))
	{
		if (exec_builtin(args, envp))
			exit(EXIT_SUCCESS);
		exit(EXIT_FAILURE);
	}
	path = get_path(envp, args[0]);
	if (path)
	{
		execve(path, args, envp);
		free(path);
	}
	fprintf(stderr, "Command not found: %s\n", args[0]);
	exit(EXIT_FAILURE);
}

static int first_process(char **argv, char **envp, int *pipe_fd)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		pipe_command(argv, envp);
	}
	return pid;
}

static int second_process(char **args, char **envp, int *pipe_fd)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		pipe_command(args, envp);
	}
	return pid;
}

int do_pipe(char **argv, char **envp)
{
	int pipe_fd[2], status;
	char **right_args;
	pid_t pid1, pid2;
	int pipe_pos = is_pipe(argv);

	if (!pipe_pos || !argv[pipe_pos + 1])
		return (fprintf(stderr, "Invalid pipe syntax\n"), 1);
	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), 1);
	right_args = split_args(argv, pipe_pos);
	if (!right_args)
		return (close(pipe_fd[0]), close(pipe_fd[1]), 1);
	pid1 = first_process(argv, envp, pipe_fd);
	pid2 = second_process(right_args, envp, pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	free_args(right_args);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	return 0;
}

int handle_pipes(char *command, char **envp)
{
	char **args;
	int result = 0;

	args = ft_split(command, ' ');
	if (!args)
		return 1;
	if (is_pipe(args))
		result = do_pipe(args, envp);
	free_args(args);
	return result;
}
