/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:59:05 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/09 11:59:05 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char	*find_path(char **envp)
{
	char	*env_path;
	int		i;

	env_path = NULL;
	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			env_path = envp[i] + 5;
			break ;
		}
		i++;
	}
	return (env_path);
}

char	*try_executable_path(char **paths, char *command)
{
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	if (!paths || !command || !command[0])
		return (NULL);
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		path = ft_strjoin(tmp, command);
		free(tmp);
		if (!path)
			return (NULL);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*get_path(char **envp, char *command)
{
	char	**paths;
	char	*executable_path;

	if (!command || !command[0])
		return (NULL);
	if (is_path_command(command))
		return (handle_direct_path(command));
	paths = prepare_path_dirs(envp);
	if (!paths)
		return (NULL);
	executable_path = try_executable_path(paths, command);
	free_args(paths);
	return (executable_path);
}
