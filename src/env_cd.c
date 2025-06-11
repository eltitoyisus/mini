/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:31:15 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/09 19:31:15 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char	*get_cd_target(char **args)
{
	char	*dir;

	if (!args[1] || ft_strncmp(args[1], "~", 2) == 0)
	{
		dir = getenv("HOME");
		if (!dir)
			printf("cd: HOME not set\n");
		return (dir);
	}
	return (args[1]);
}

int	change_directory(char *dir, char *old_pwd)
{
	if (chdir(dir) != 0)
	{
		printf("cd: %s: No such file or directory\n", dir);
		if (old_pwd)
			free(old_pwd);
		return (1);
	}
	return (0);
}

void	update_pwd(t_sh *sh)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (new_pwd && sh)
	{
		if (sh->pwd)
			free(sh->pwd);
		sh->pwd = new_pwd;
	}
}

int	exec_cd(char **args, t_sh *sh)
{
	char	*dir;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	dir = get_cd_target(args);
	if (!dir)
	{
		if (old_pwd)
			free(old_pwd);
		return (1);
	}
	if (change_directory(dir, old_pwd))
		return (1);
	if (sh)
		update_pwd(sh);
	if (old_pwd)
		free(old_pwd);
	return (0);
}
