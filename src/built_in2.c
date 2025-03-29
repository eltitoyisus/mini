/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:35:29 by jramos-a          #+#    #+#             */
/*   Updated: 2025/03/29 12:36:43 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int exec_export(char **args, char ***envp)
{
	int i;
	
	i = 1;
	if (!args[1])
	{
		while (envp[i])
		{
			write(1, envp[i], ft_strlen(envp[i]));
			write(1, "\n", 1);
			i++;
		}
	}
	else
	{
		while (args[i])
		{
			write(1, args[i], ft_strlen(args[i]));
			write(1, "\n", 1);
			i++;
		}
	}
	return (1);
}

int exec_unset(char **args, char ***envp)
{
	int i;
	
	i = 1;
	if (!args[1])
	{
		write(1, "unset: not enough arguments\n", 28);
		return (0);
	}
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));\
		write(1, "\n", 1);
		i++;
	}
	return (1);
}

int exec_cd(char **args)
{
	if (!args[1])
	{
		write(1, "cd: not enough arguments\n", 25);
		return (0);
	}
	if (chdir(args[1]) != 0)
	{
		perror("cd");
		return (0);
	}
	return (1);
}
