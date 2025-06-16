/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:23:00 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/13 11:42:42 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	export_handle_no_args(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		export_no_args(&envp[i]);
		i++;
	}
	return (1);
}

int	export_validate_and_create(char **argv, char **new_var)
{
	if (!ft_strchr(argv[1], '='))
	{
		printf("export: %s is not a valid variable\n", argv[1]);
		return (-1);
	}
	*new_var = ft_strdup(argv[1]);
	if (!*new_var)
		return (-1);
	return (0);
}

int	export_find_and_replace(char **envp, char *argv_var, char *new_var)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], argv_var, ft_strchr(argv_var, '=')
				- argv_var) == 0)
		{
			free(envp[i]);
			envp[i] = new_var;
			return (1);
		}
		i++;
	}
	return (0);
}

int	env_export(char **argv, char **envp)
{
	int		i;
	char	*new_var;
	int		result;

	if (!envp)
		return (0);
	if (!argv[1])
		return (export_handle_no_args(envp));
	result = export_validate_and_create(argv, &new_var);
	if (result != 0)
		return (result);
	if (export_find_and_replace(envp, argv[1], new_var))
		return (1);
	i = 0;
	while (envp[i])
		i++;
	envp[i] = new_var;
	envp[i + 1] = NULL;
	return (1);
}
