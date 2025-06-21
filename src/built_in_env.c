/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:04:02 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/21 17:23:49 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	remove_env_var(char **envp, char *var)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0
			&& envp[i][ft_strlen(var)] == '=')
		{
			free(envp[i]);
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

int	env_unset(char **argv, t_sh *sh)
{
	if (!sh || !sh->env || !argv[1])
		return (0);
	return (remove_env_var(sh->env, argv[1]));
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

int	find_and_print_env_var(char *var_name, char **envp)
{
	int		j;
	char	*value;

	j = 0;
	while (envp[j])
	{
		if (ft_strncmp(var_name, envp[j], ft_strlen(var_name)) == 0
			&& envp[j][ft_strlen(var_name)] == '=')
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

int	echo_var(char **argv, int index, char **envp)
{
	char	*ptr;

	if (argv[index][0] != '$')
		return (0);
	ptr = argv[index];
	while (ptr > argv[index] - index && *ptr != '\001')
		ptr--;
	if (*ptr == '\001')
		return (0);
	return (find_and_print_env_var(&argv[index][1], envp));
}
