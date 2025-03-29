/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 10:12:50 by jramos-a          #+#    #+#             */
/*   Updated: 2025/03/29 12:08:29 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	exec_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (args[1] && ft_strncmp(args[1], "-n", 3) == 0)
	{
		newline = 0;
		i = 2;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (1);
}

int	exec_pwd(void)
{
	char	cwd[1024];
	
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_putendl_fd(cwd, STDOUT_FILENO);
	else
		perror("pwd");
	return (1);
}

int	exec_env(char **envp)
{
	int	i;
	
	i = 0;
	while (envp[i])
		ft_putendl_fd(envp[i++], STDOUT_FILENO);
	return (1);
}

int	exec_exit(void)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(0);
	return (1);
}
