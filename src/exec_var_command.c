/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_var_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:00:00 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/19 12:00:00 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char	*get_var_value(char *var_name, char **envp)
{
	int		i;
	char	*value;
	size_t	name_len;

	if (!var_name || !envp)
		return (NULL);
	name_len = ft_strlen(var_name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(var_name, envp[i], name_len) == 0
			&& envp[i][name_len] == '=')
		{
			value = ft_strchr(envp[i], '=');
			if (value)
				return (value + 1);
		}
		i++;
	}
	return (NULL);
}

int	is_var_command(char *cmd)
{
	return (cmd && cmd[0] == '$' && cmd[1]);
}

int	exec_var_command(t_sh *sh, char **envp)
{
	char	*var_name;
	char	*cmd_value;
	char	**cmd_args;
	int		result;

	if (!sh || !sh->node || !sh->node->cmd || !sh->node->cmd->split_cmd
		|| !sh->node->cmd->split_cmd[0])
		return (1);
	if (!is_var_command(sh->node->cmd->split_cmd[0]))
		return (0);
	var_name = &(sh->node->cmd->split_cmd[0][1]);
	cmd_value = get_var_value(var_name, envp);
	if (!cmd_value)
	{
		ft_putstr_fd(sh->node->cmd->split_cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	free_args(sh->node->cmd->split_cmd);
	cmd_args = ft_split(cmd_value, ' ');
	if (!cmd_args)
		return (1);
	sh->node->cmd->split_cmd = cmd_args;
	result = exec_parsed_command(sh, envp);
	return (result);
}
