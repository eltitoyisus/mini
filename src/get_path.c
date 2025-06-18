/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 20:42:32 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/18 09:44:27 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	print_path_error(char *command, char *message)
{
	write(2, command, ft_strlen(command));
	write(2, message, ft_strlen(message));
	return (0);
}

char	*handle_direct_path(char *command)
{
	if (access(command, F_OK) == 0)
	{
		if (access(command, X_OK) != 0)
		{
			print_path_error(command, ": Permission denied\n");
			return (NULL);
		}
		return (ft_strdup(command));
	}
	print_path_error(command, ": No such file or directory\n");
	return (NULL);
}

int	is_path_command(char *command)
{
	if (!command || !command[0])
		return (0);
	return (command[0] == '/' || command[0] == '.' || ft_strchr(command,
			'/') != NULL);
}

char	**prepare_path_dirs(char **envp)
{
	char	*env_path;
	char	**paths;

	env_path = find_path(envp);
	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ':');
	return (paths);
}
