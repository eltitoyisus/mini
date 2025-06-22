/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:14:26 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/22 12:52:13 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	free_exec_params(t_exec_params *params)
{
	if (params->stdin_backup != -1)
	{
		dup2(params->stdin_backup, STDIN_FILENO);
		close(params->stdin_backup);
		params->stdin_backup = -1;
	}
	if (params->has_heredoc)
		unlink("heredoc.tmp");
	if (params->redirs)
	{
		free_redirs(params->redirs);
		params->redirs = NULL;
	}
	if (params->clean_args && params->needs_cleanup)
	{
		free_args(params->clean_args);
		params->clean_args = NULL;
	}
}

void	print_command_details(char **clean_args, t_sh *sh)
{
	int	i;

	printf("Executing command: ");
	if (clean_args)
	{
		i = 0;
		while (clean_args[i])
		{
			printf("[%s] ", clean_args[i]);
			i++;
		}
		printf("\n");
	}
	else if (sh->node->cmd->split_cmd)
	{
		i = 0;
		while (sh->node->cmd->split_cmd[i])
		{
			printf("[%s] ", sh->node->cmd->split_cmd[i]);
			i++;
		}
		printf("\n");
	}
}

int	handle_piped_command(t_exec_args *args)
{
	if (args->stdin_backup != -1)
		close(args->stdin_backup);
	if (args->redirs)
		free_redirs(args->redirs);
	if (args->clean_args)
		free_args(args->clean_args);
	if (args->needs_cleanup && args->sh->node->cmd->split_cmd)
		free_args(args->sh->node->cmd->split_cmd);
	return (process_piped_command(args->sh, args->envp));
}

int	exec_builtin_command(t_exec_args *args, char **cmd_to_exec)
{
	int	result;

	if (args->redirs)
		result = exec_builtin_with_redirs(cmd_to_exec, args->envp, args->sh,
				args->redirs);
	else
		result = exec_builtin(cmd_to_exec, args->envp, args->sh);
	if (args->stdin_backup != -1)
	{
		dup2(args->stdin_backup, STDIN_FILENO);
		close(args->stdin_backup);
	}
	if (args->has_heredoc)
		unlink("heredoc.tmp");
	if (args->redirs)
		free_redirs(args->redirs);
	if (args->clean_args && args->clean_args != args->sh->node->cmd->split_cmd)
		free_args(args->clean_args);
	if (args->needs_cleanup && args->sh->node->cmd->split_cmd)
		free_args(args->sh->node->cmd->split_cmd);
	return (result);
}

void	exec_external_with_cleanup(t_exec_args *args)
{
	char	**temp;

	if (args->redirs && args->clean_args)
	{
		temp = args->sh->node->cmd->split_cmd;
		args->sh->node->cmd->split_cmd = args->clean_args;
		exec_external_command_with_redirs(args->sh, args->envp, args->redirs);
		args->sh->node->cmd->split_cmd = temp;
		free_args(args->clean_args);
	}
	else
		exec_external_command(args->sh, args->envp);
	if (args->stdin_backup != -1)
	{
		dup2(args->stdin_backup, STDIN_FILENO);
		close(args->stdin_backup);
	}
	if (args->has_heredoc)
		unlink("heredoc.tmp");
	if (args->redirs)
		free_redirs(args->redirs);
	if (args->needs_cleanup && args->sh->node->cmd->split_cmd)
		free_args(args->sh->node->cmd->split_cmd);
}
