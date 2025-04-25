/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:04:02 by jramos-a          #+#    #+#             */
/*   Updated: 2025/04/24 14:37:53 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	exec_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		write(1, envp[i], ft_strlen(envp[i]));
		write(1, "\n", 1);
		i++;
	}
	return (1);
}

int	env_unset(char **argv, char **envp)
{
	int i;
	int j;
	char *var;

	i = 0;
	if (!argv[1])
		return (0);
	var = argv[1];
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0
			&& envp[i][ft_strlen(var)] == '=')
		{
			j = i;
			while (envp[j])
			{
				envp[j] = envp[j + 1];
				j++;
			}
			return (1);
		}
		i++;
	}
	printf("unset: variable %s not found\n", var);
	return (1);
}

int env_export(char **argv, char **envp)
{
	int i;
	char *new_var;
	
	i = 0;
	if (!argv[1] || !envp)	
		return (0);
	new_var = ft_strdup(argv[1]);
	if (!new_var)
		return (0);
	while (envp[i])
		i++;
	envp[i] = new_var;
	envp[i + 1] = NULL;
	return (1);
}

int	echo_var(char **argv, char **envp)
{
	int i;
	int j;
	char *value;

	i = 0;
	j = 0;
	while (argv[i])
	{
		if (argv[i][0] == '$')
		{
			j = 0;
			while (envp[j])
			{
				if (ft_strncmp(&argv[i][1], envp[j], ft_strlen(&argv[i][1])) == 0)
				{
					value = ft_strchr(envp[j], '=');
					if (value)
						write(1, value + 1, ft_strlen(value + 1));
					return (1);
					write(1, "\n", 1);
				}
				j++;
			}
			return (1);
		}
		i++;
	}
	return (0);
}
