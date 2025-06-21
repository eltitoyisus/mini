/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:14:44 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/21 13:03:32 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char	***allocate_commands_array(int pipe_count)
{
	char	***commands;
	int		i;

	commands = malloc(sizeof(char **) * (pipe_count + 2));
	if (!commands)
		return (NULL);
	i = 0;
	while (i <= pipe_count + 1)
	{
		commands[i] = NULL;
		i++;
	}
	return (commands);
}

int	allocate_command_segment(char ***commands, char **cmd_args,
		t_cmd_segment seg)
{
	int	j;

	commands[seg.cmd_idx] = malloc(sizeof(char *) * (seg.cmd_len + 1));
	if (!commands[seg.cmd_idx])
		return (0);
	j = 0;
	while (j < seg.cmd_len)
	{
		commands[seg.cmd_idx][j] = ft_strdup(cmd_args[seg.start + j]);
		if (!commands[seg.cmd_idx][j])
			return (0);
		j++;
	}
	commands[seg.cmd_idx][seg.cmd_len] = NULL;
	return (1);
}

t_cmd_segment	init_cmd_segment(int cmd_idx, int start, int cmd_len)
{
	t_cmd_segment	seg;

	seg.cmd_idx = cmd_idx;
	seg.start = start;
	seg.cmd_len = cmd_len;
	return (seg);
}

void	cleanup_commands(char ***commands, int cmd_idx, int j)
{
	int	k;

	k = 0;
	while (k < j)
	{
		free(commands[cmd_idx][k]);
		k++;
	}
	free(commands[cmd_idx]);
	k = 0;
	while (k < cmd_idx)
	{
		free_args(commands[k]);
		k++;
	}
	free(commands);
}
