/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:09 by jramos-a          #+#    #+#             */
/*   Updated: 2025/03/29 12:35:09 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int is_builtin(char *command)
{
	if (!command)
		return (0);
	
	if (ft_strncmp(command, "cd", 3) == 0 ||
		ft_strncmp(command, "echo", 5) == 0 ||
		ft_strncmp(command, "pwd", 4) == 0 ||
		ft_strncmp(command, "export", 7) == 0 ||
		ft_strncmp(command, "unset", 6) == 0 ||
		ft_strncmp(command, "env", 4) == 0 ||
		ft_strncmp(command, "exit", 5) == 0)
		return (1);
	return (0);
}


int	exec_builtin(char **args, char **envp)
{
	if (!args || !args[0])
		return (0);
	if (ft_strncmp(args[0], "echo", 5) == 0)
		return (exec_echo(args));
	else if (ft_strncmp(args[0], "pwd", 4) == 0)
		return (exec_pwd());
	else if (ft_strncmp(args[0], "env", 4) == 0)
		return (exec_env(envp));
	else if (ft_strncmp(args[0], "exit", 5) == 0)
		return (exec_exit());
	else if (ft_strncmp(args[0], "export", 6) == 0)
		return (exec_export(args));
	else if (ft_strncmp(args[0], "unset", 6) == 0)
		return (exec_unset(args));
	else if (ft_strncmp(args[0], "cd", 3) == 0)
		return (exec_cd(args));
	return (0);
}

