/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:00:03 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/11 11:00:03 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static void	execute_command_with_no_env(char *cmd, char **cmd_args, char **envp)
{
	char	*path;

	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
		path = cmd;
	else
		path = get_path(envp, cmd);
	if (!path)
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	if (execve(path, cmd_args, NULL) == -1)
	{
		perror(cmd);
		if (path != cmd)
			free(path);
		exit(EXIT_FAILURE);
	}
}

static int	handle_env_i_command(char **args, char **envp)
{
	pid_t	pid;
	int		status;
	char	*cmd;

	if (!args[2])
		return (0);
	cmd = args[2];
	pid = fork();
	if (pid == 0)
	{
		execute_command_with_no_env(cmd, &args[2], envp);
	}
	else if (pid < 0)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	return (0);
}

static int	print_environment(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		ft_putendl_fd(envp[i], 1);
		i++;
	}
	return (0);
}

static int	print_env_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (i > 0)
			ft_putendl_fd(args[i], 1);
		i++;
	}
	return (i);
}

int	exec_env(char **args, char **envp)
{
	int	arg_count;

	if (args[1] && ft_strncmp(args[1], "-i", 3) == 0)
	{
		return (handle_env_i_command(args, envp));
	}
	else
	{
		arg_count = print_env_args(args);
		if (arg_count <= 1)
			print_environment(envp);
		return (0);
	}
}
