/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:00:00 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/20 10:00:00 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char	**create_minimal_env(void)
{
	char	**env;
	char	*cwd;

	env = malloc(sizeof(char *) * 4);
	if (!env)
		return (NULL);
	env[0] = ft_strdup("PATH=/usr/local/bin:/usr/bin:/bin");
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		env[1] = ft_strjoin("PWD=", cwd);
		free(cwd);
	}
	else
		env[1] = ft_strdup("PWD=/");
	env[2] = ft_strdup("SHLVL=1");
	env[3] = NULL;
	return (env);
}

char	**ft_envdup(char **envp)
{
	char	**new_env;
	int		count;
	int		i;

	if (!envp || !envp[0])
		return (create_minimal_env());
	count = 0;
	while (envp[count])
		count++;
	new_env = (char **)malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			while (--i >= 0)
				free(new_env[i]);
			return (free(new_env), NULL);
		}
		i++;
	}
	return (new_env[count] = NULL, new_env);
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}
