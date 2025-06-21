/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:23:00 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/21 17:27:27 by jramos-a         ###   ########.fr       */
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
	int		i;
	char	*equals_pos;
	int		var_len;

	if (!envp || !argv_var || !new_var)
		return (0);
	equals_pos = ft_strchr(argv_var, '=');
	if (!equals_pos)
		return (0);
	var_len = equals_pos - argv_var;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], argv_var, var_len) == 0
			&& envp[i][var_len] == '=')
		{
			free(envp[i]);
			envp[i] = new_var;
			return (1);
		}
		i++;
	}
	return (0);
}

void	copy_char_to_result(char *input, char *result, int *i, int *j)
{
	result[(*j)++] = input[(*i)++];
}
