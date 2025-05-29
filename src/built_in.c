/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:07:10 by jramos-a          #+#    #+#             */
/*   Updated: 2025/05/29 20:02:49 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	exec_echo(char **args, char **envp)
{
	int	i;
	int	n_flag;

	(void)envp;
	i = 1;
	n_flag = 0;
	if (args[1] && ft_strncmp(args[1], "-n", 3) == 0)
	{
		n_flag = 1;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (0);
}

int	exec_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
}

int	exec_exit(void)
{
	exit(0);
}

int	exec_cd(char **args, t_sh *sh)
{
	char	*dir;

	(void)sh;
	if (!args[1] || ft_strncmp(args[1], "~", 2) == 0)
	{
		dir = getenv("HOME");
		if (!dir)
		{
			printf("cd: HOME not set\n");
			return (1);
		}
	}
	else
		dir = args[1];
	if (chdir(dir) != 0)
	{
		printf("cd: %s: No such file or directory\n", dir);
		return (1);
	}
	return (0);
}
