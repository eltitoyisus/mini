/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:01:20 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/09 18:01:20 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	is_pipe(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return (0);
	while (args[i])
	{
		if (ft_strncmp(args[i], "|", 2) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	count_pipes(char **args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!args)
		return (0);
	while (args[i])
	{
		if (ft_strncmp(args[i], "|", 2) == 0)
			count++;
		i++;
	}
	return (count);
}

void	free_commands(char ***commands, int k)
{
	int	i;
	int	j;

	i = 0;
	if (!commands)
		return ;
	while (i < k)
	{
		j = 0;
		while (commands[i] && commands[i][j])
		{
			free(commands[i][j]);
			j++;
		}
		free(commands[i]);
		i++;
	}
	free(commands);
}

void	pipe_command(char **args, char **envp)
{
	char	*path;

	if (!args || !args[0])
	{
		printf("Invalid command\n");
		exit(EXIT_FAILURE);
	}
	if (is_builtin(args[0]))
	{
		if (exec_builtin(args, envp, NULL))
			exit(EXIT_SUCCESS);
		exit(EXIT_FAILURE);
	}
	path = get_path(envp, args[0]);
	if (path)
	{
		execve(path, args, envp);
		free(path);
	}
	printf("Command not found: %s\n", args[0]);
	exit(EXIT_FAILURE);
}

void	close_pipe_fds(int fd_prev, int fd[2], int pipe_stage)
{
	if (fd_prev != -1)
		close(fd_prev);
	if (pipe_stage)
	{
		close(fd[0]);
		close(fd[1]);
	}
}
