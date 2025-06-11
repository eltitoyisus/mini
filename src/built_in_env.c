/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:04:02 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/11 11:17:28 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	env_unset(char **argv, char **envp)
{
	int		i;
	int		j;
	char	*var;

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

void	export_no_args(char **envp)
{
	char	*equals;
	int		i;

	i = 0;
	write(1, "declare -x ", 11);
	equals = ft_strchr(envp[i], '=');
	if (equals)
	{
		write(1, envp[i], equals - envp[i]);
		write(1, "=\"", 2);
		write(1, equals + 1, ft_strlen(equals + 1));
		write(1, "\"", 1);
	}
	else
		write(1, envp[i], ft_strlen(envp[i]));
	write(1, "\n", 1);
	i++;
}

int	echo_var(char **argv, int index, char **envp)
{
	int		j;
	char	*value;

	if (argv[index][0] != '$')
		return (0);
	j = 0;
	while (envp[j])
	{
		if (ft_strncmp(&argv[index][1], envp[j],
			ft_strlen(&argv[index][1])) == 0
			&& envp[j][ft_strlen(&argv[index][1])] == '=')
		{
			value = ft_strchr(envp[j], '=');
			if (value)
				write(1, value + 1, ft_strlen(value + 1));
			return (1);
		}
		j++;
	}
	return (1);
}
