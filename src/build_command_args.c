/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:53:59 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/16 17:17:16 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	is_command_token(int type)
{
	return (type == CMD || type == BUILT || type == FLAG || type == ARG
		|| type == INRED || type == OURED || type == D_OURED || type == HEREDOC
		|| type == DELIM || type == INFILE || type == OUTFILE_TR
		|| type == OUTFILE_APP);
}

void	count_pipe_commands(t_sh *sh, t_parse *parse)
{
	t_parse	*current;
	int		cmd_count;

	cmd_count = 1;
	current = parse;
	while (current)
	{
		if (current->type_token == PIPE)
			cmd_count++;
		current = current->next;
	}
	sh->node->n_cmd = cmd_count;
}

void	allocate_cmd_memory(t_cmd *cmd_node, int count)
{
	if (count > 0)
	{
		cmd_node->split_cmd = malloc(sizeof(char *) * (count + 1));
		if (!cmd_node->split_cmd)
			return ;
	}
}

void	allocate_first_commands(t_sh *sh, t_parse *parse)
{
	t_parse	*current;
	t_cmd	*cmd_node;
	int		count;

	current = parse;
	cmd_node = sh->node->cmd;
	count = 0;
	while (current)
	{
		if (current->type_token == PIPE)
		{
			allocate_cmd_memory(cmd_node, count);
			ft_lstadd_back_cmd(cmd_node);
			cmd_node = cmd_node->next;
			count = 0;
			current = current->next;
		}
		else
		{
			if (is_command_token(current->type_token))
				count++;
			current = current->next;
		}
	}
}

void	allocate_last_command(t_sh *sh, t_parse *parse)
{
	t_parse	*current;
	t_cmd	*cmd_node;
	int		count;

	current = parse;
	cmd_node = sh->node->cmd;
	count = 0;
	while (current)
	{
		if (current->type_token == PIPE)
			process_pipe(&count, &current);
		else
		{
			if (is_command_token(current->type_token))
				count++;
			current = current->next;
		}
	}
	allocate_cmd_memory(cmd_node, count);
}
