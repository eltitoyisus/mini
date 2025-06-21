/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:04:16 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/21 16:40:03 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	init_pipe_command_vars(t_sh *sh, t_pipe_vars *vars)
{
	vars->i = 0;
	vars->cmd_args = sh->node->cmd->split_cmd;
	vars->pipe_count = 0;
	vars->cmd_count = 0;
	while (vars->cmd_args[vars->i])
	{
		if (ft_strncmp(vars->cmd_args[vars->i], "|", 2) == 0)
			vars->pipe_count++;
		vars->i++;
	}
}

int	handle_command_token(char ***commands, char **cmd_args, int i,
		t_token_counters *counters)
{
	int				cmd_len;
	t_cmd_segment	seg;

	cmd_len = i - counters->start;
	if (cmd_args[i + 1] == NULL && ft_strncmp(cmd_args[i], "|", 2) != 0)
		cmd_len++;
	seg = init_cmd_segment(counters->cmd_idx, counters->start, cmd_len);
	if (!allocate_command_segment(commands, cmd_args, seg))
		return (-1);
	(counters->cmd_idx)++;
	counters->start = i + 1;
	return (0);
}

int	parse_command_segments(char ***commands, char **cmd_args, int pipe_count)
{
	int					i;
	t_token_counters	counters;

	(void)commands;
	counters.start = 0;
	counters.cmd_idx = 0;
	i = 0;
	(void)pipe_count;
	while (cmd_args[i])
	{
		if (ft_strncmp(cmd_args[i], "|", 2) == 0 || cmd_args[i + 1] == NULL)
		{
			if (handle_command_token(commands, cmd_args, i, &counters) == -1)
				return (-1);
		}
		i++;
	}
	return (counters.cmd_idx);
}
