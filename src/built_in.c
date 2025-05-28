/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:07:10 by jramos-a          #+#    #+#             */
/*   Updated: 2025/05/28 17:01:49 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	exec_echo(char **args, char **envp)
{
	int	i;
	int	newline;

	write(2, "Echo args: ", 11);
	for (int j = 0; args[j]; j++)
	{
		write(2, args[j], ft_strlen(args[j]));
		write(2, " ", 1);
	}
	write(2, "\n", 1);
	i = 1;
	newline = 1;
	if (args[1] && ft_strncmp(args[1], "-n", 3) == 0)
	{
		newline = 0;
		i = 2;
	}
	while (args[i])
	{
		if (args[i][0] == '$')
		{
			if (echo_var(args, i, envp) == 0)
				write(1, args[i], ft_strlen(args[i]));
		}
		else
		{
			write(1, args[i], ft_strlen(args[i]));
		}
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (1);
}

int	exec_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
	return (1);
}

int	exec_cd(char **args, t_sh *sh)
{
	char	*home_dir;

	if (!args[1])
	{
		home_dir = getenv("HOME");
		if (!home_dir)
		{
			write(2, "cd: HOME not set\n", 17);
			return (0);
		}
		if (chdir(home_dir) != 0)
		{
			write(2, "cd: ", 4);
			write(2, home_dir, ft_strlen(home_dir));
			write(2, ": No such file or directory\n", 28);
			return (0);
		}
	}
	else if (chdir(args[1]) != 0)
	{
		write(2, "cd: ", 4);
		write(2, args[1], ft_strlen(args[1]));
		write(2, ": No such file or directory\n", 28);
		return (0);
	}
	free(sh->prompt);
	sh->prompt = "\033[44;97m@CRIPTOSHELL\033[0m \033[38;5;82m";
	sh->prompt = ft_strjoin(sh->prompt, "-");
	sh->prompt = ft_strjoin(sh->prompt, getcwd(NULL, 0));
	sh->prompt = ft_strjoin(sh->prompt, " ~ \033[0;0m");
	return (1);
}

int	exec_exit(void)
{
	int	status;

	status = 0;
	write(1, "exit\n", 5);
	exit(status);
	return (1);
}
