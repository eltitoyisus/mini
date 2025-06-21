/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:07:08 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/19 16:21:07 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	is_builtin(char *command)
{
	int	result;

	if (!command)
		return (0);
	result = (ft_strncmp(command, "cd", 3) == 0 || ft_strncmp(command, "echo",
				5) == 0 || ft_strncmp(command, "pwd", 4) == 0
			|| ft_strncmp(command, "exit", 5) == 0 || ft_strncmp(command, "env",
				4) == 0 || ft_strncmp(command, "export", 7) == 0
			|| ft_strncmp(command, "unset", 6) == 0);
	return (result);
}

int	exec_builtin(char **args, char **envp, t_sh *sh)
{
	if (!args || !args[0])
		return (0);
	if (ft_strncmp(args[0], "echo", 5) == 0)
		return (exec_echo(sh));
	else if (ft_strncmp(args[0], "pwd", 4) == 0)
		return (exec_pwd());
	else if (ft_strncmp(args[0], "exit", 5) == 0)
		return (exec_exit(sh, args));
	else if (ft_strncmp(args[0], "cd", 3) == 0)
		return (exec_cd(args, sh));
	else if (ft_strncmp(args[0], "env", 4) == 0)
		return (exec_env(args, envp));
	else if (ft_strncmp(args[0], "export", 7) == 0)
		return (env_export(args, sh));
	else if (ft_strncmp(args[0], "unset", 6) == 0)
		return (env_unset(args, sh));
	return (0);
}

char	**inc_shlvl(char **envp)
{
	int		i;
	int		shlvl;
	char	*new_value;
	char	*new_var;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
		{
			shlvl = ft_atoi(envp[i] + 6);
			new_value = ft_itoa(shlvl + 1);
			if (new_value)
			{
				new_var = ft_strjoin("SHLVL=", new_value);
				free(new_value);
				if (new_var)
					envp[i] = new_var;
			}
			break ;
		}
		i++;
	}
	return (envp);
}
