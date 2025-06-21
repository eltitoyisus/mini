/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command_args2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:56:07 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/20 14:20:57 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	null_terminate_and_print(t_sh *sh)
{
	t_cmd	*cmd_node;
	int		count;

	if (!sh || !sh->node || !sh->node->cmd)
		return ;
	cmd_node = sh->node->cmd;
	while (cmd_node && cmd_node->next)
		cmd_node = cmd_node->next;
	if (cmd_node && cmd_node->split_cmd)
	{
		count = 0;
		while (cmd_node->split_cmd[count])
			count++;
		cmd_node->split_cmd[count] = NULL;
	}
}

void	process_cmd_token(t_parse *current, t_cmd *cmd, int *count)
{
	char	*unquoted;

	if (current->line)
	{
		unquoted = cut_quotes(current->line);
		if (unquoted)
			cmd->split_cmd[(*count)++] = unquoted;
		else
			cmd->split_cmd[(*count)++] = ft_strdup(current->line);
	}
	else
		cmd->split_cmd[(*count)++] = ft_strdup("");
}

void	build_command_args(t_sh *sh, t_parse *parse)
{
	if (!sh || !sh->node || !sh->node->cmd || !parse)
		return ;
	count_pipe_commands(sh, parse);
	allocate_first_commands(sh, parse);
	allocate_last_command(sh, parse);
	fill_command_args(sh, parse);
	null_terminate_and_print(sh);
}

void	handle_pipe_token(t_cmd **cmd, int *count, t_parse **curr)
{
	if (*cmd && (*cmd)->split_cmd)
		(*cmd)->split_cmd[*count] = NULL;
	*cmd = (*cmd)->next;
	*count = 0;
	*curr = (*curr)->next;
}

void	process_pipe(int *count, t_parse **current)
{
	*count = 0;
	*current = (*current)->next;
}
