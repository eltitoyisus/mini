/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:10:34 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/19 11:10:34 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	check_env_export_preconditions(t_sh *sh, char **argv)
{
	if (!sh->env)
		return (0);
	if (!argv[1])
		return (export_handle_no_args(sh->env));
	return (-1);
}

int	prepare_new_env_variable(char **argv, char **new_var)
{
	int	result;

	result = export_validate_and_create(argv, new_var);
	if (result != 0)
		return (result);
	return (-1);
}

int	try_update_existing_variable(char **env, char *argv_var, char *new_var)
{
	if (export_find_and_replace(env, argv_var, new_var))
		return (1);
	return (-1);
}

char	**allocate_and_fill_env(char **env, char *new_var)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	return (new_env);
}

int	env_export(char **argv, t_sh *sh)
{
	char	*new_var;
	int		result;
	char	**new_env;

	new_var = NULL;
	result = check_env_export_preconditions(sh, argv);
	if (result >= 0)
		return (result);
	result = prepare_new_env_variable(argv, &new_var);
	if (result >= 0)
		return (result);
	result = try_update_existing_variable(sh->env, argv[1], new_var);
	if (result >= 0)
		return (result);
	new_env = allocate_and_fill_env(sh->env, new_var);
	if (!new_env)
	{
		free(new_var);
		return (-1);
	}
	free(sh->env);
	sh->env = new_env;
	return (1);
}
