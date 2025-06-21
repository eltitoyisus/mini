/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:59:05 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/20 14:22:54 by jramos-a         ###   ########.fr       */
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

char	*clean_control_chars(char *str)
{
	char	*clean;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	clean = malloc(ft_strlen(str) + 1);
	if (!clean)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\001' && str[i] != '\002')
			clean[j++] = str[i];
		i++;
	}
	clean[j] = '\0';
	return (clean);
}

char	*search_in_path_dirs(char **envp, char *command)
{
	char	**paths;
	char	*result;

	if (!command || !command[0])
		return (NULL);
	paths = prepare_path_dirs(envp);
	if (!paths)
		return (NULL);
	result = try_executable_path(paths, command);
	free_args(paths);
	return (result);
}

char	*get_path(char **envp, char *command)
{
	char	*clean_command;
	char	*path;

	if (!command)
		return (NULL);
	clean_command = clean_control_chars(command);
	if (!clean_command)
		return (NULL);
	if (is_path_command(clean_command))
	{
		path = handle_direct_path(clean_command);
		free(clean_command);
		return (path);
	}
	path = search_in_path_dirs(envp, clean_command);
	free(clean_command);
	return (path);
}
