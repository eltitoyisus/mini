/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:11:40 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/21 17:33:41 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	wait_for_children(pid_t *pids, int cmd_count)
{
	int	status;
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &status, 0);
		if (i == cmd_count - 1)
		{
			if (WIFEXITED(status))
				last_signal_code(WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				last_signal_code(128 + WTERMSIG(status));
		}
		i++;
	}
	free(pids);
}

void	assign_split_cmds_to_nodes(t_cmd *cmd_list, char ***commands,
		int cmd_count)
{
	int		i;
	t_cmd	*current;

	i = 0;
	current = cmd_list;
	while (current && i < cmd_count)
	{
		if (current->split_cmd)
			free_args(current->split_cmd);
		current->split_cmd = commands[i];
		current = current->next;
		i++;
	}
}

int	process_piped_command(t_sh *sh, char **envp)
{
	t_pipe_vars	vars;
	char		***commands;
	int			cmd_idx;

	init_pipe_command_vars(sh, &vars);
	commands = allocate_commands_array(vars.pipe_count);
	if (!commands)
		return (1);
	cmd_idx = parse_command_segments(commands, vars.cmd_args, vars.pipe_count);
	assign_split_cmds_to_nodes(sh->node->cmd, commands, cmd_idx);
	execute_pipe_chain_new(commands, cmd_idx, envp);
	if (sh->node && sh->node->cmd && sh->node->cmd->split_cmd)
	{
		free_args(sh->node->cmd->split_cmd);
		sh->node->cmd->split_cmd = NULL;
	}
	free(commands);
	return (0);
}

void	wait_for_pipe_commands(pid_t *pids, int cmd_count)
{
	int	status;
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &status, 0);
		if (i == cmd_count - 1)
		{
			if (WIFEXITED(status))
				last_signal_code(WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				last_signal_code(128 + WTERMSIG(status));
		}
		i++;
	}
	ft_signals();
	free(pids);
}
