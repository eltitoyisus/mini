/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:07:12 by jramos-a          #+#    #+#             */
/*   Updated: 2025/05/06 09:50:18 by jramos-a         ###   ########.fr       */
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
	char *tmp;
	int i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		path = ft_strjoin(tmp, command);
		free(tmp);
		if (!path)
			return (NULL);
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

	if (command[0] == '/' || (command[0] == '.' && command[1] == '/'))
	{
		if (access(command, X_OK) == 0)
			return ft_strdup(command);
		return NULL;
	}
	env_path = find_path(envp);
	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ':');
	if (!paths)
		return (NULL);
	executable_path = try_executable_path(paths, command);
	free_args(paths);
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

void exec_command(char *command, char **envp, t_sh *sh)
{
	char **args;
	
	args = ft_split(command, ' ');
	if (!command || !*command)
	{
		free_args(args);
		return ;
	}
	if (!args)
	{
		perror("ft_split");
		return;
	}
	if (is_pipe(args))
	{
		free_args(args);
		handle_pipes(command, envp);
		return;
	}
	if (has_redirection(args))
	{
		free_args(args);
		handle_redirs(command, envp);
		return;
	}
	if (is_builtin(args[0]))
	{
		if (exec_builtin(args, envp, sh))
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

char **inc_shlvl(char **envp)
{
	int i = 0;
	
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
		{
			int shlvl = ft_atoi(envp[i] + 6);
			char *new_value = ft_itoa(shlvl + 1);
			if (new_value)
			{
				char *new_var = ft_strjoin("SHLVL=", new_value);
				free(new_value);
				if (new_var)
					envp[i] = new_var;
			}
			break;
		}
		i++;
	}
	return (envp);
}

