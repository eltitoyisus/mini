/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:07:12 by jramos-a          #+#    #+#             */
/*   Updated: 2025/04/25 16:33:25 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char *find_path(char **envp)
{
	char *env_path;
	int i;

	env_path = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			env_path = envp[i] + 5;
			break ;
		}
		i++;
	}
	return (env_path);
}

char *try_executable_path(char **paths, char *command)
{
	char *path;
	int i;

	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path, command);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char *get_path(char **envp, char *command)
{
	char *env_path;
	char **paths;
	char *executable_path;

	env_path = find_path(envp);
	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ':');
	if (!paths)
		return (NULL);
	executable_path = try_executable_path(paths, command);
	free(paths);
	return (executable_path);
}

void fork_and_exec(char *command, char **envp)
{
	pid_t pid;
	int status;
	char **args;

	args = ft_split(command, ' ');
	if (!args)
		return;
	pid = fork();
	if (pid == 0)
	{
		char *path = get_path(envp, args[0]);
		if (path)
		{
			execve(path, args, envp);
			perror("execve");
			free(path);
		}
		else
			write(2, "Command not found\n", 18);
		free_args(args);
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0);
	free_args(args);
}

void free_args(char **args)
{
	int i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}

void exec_command(char *command, char **envp)
{
	char **args = ft_split(command, ' ');
	if (!args)
	{
		perror("ft_split");
		return;
	}
	if (is_builtin(args[0]))
	{
		if (exec_builtin(args, envp))
		{
			free_args(args);
			return;
		}
	}
	else
	{
		free_args(args);
		fork_and_exec(command, envp);
		return;
	}
	free_args(args);
}

