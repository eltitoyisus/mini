/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:07:12 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/11 18:54:12 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	setup_command_execution(t_sh *sh, t_exec_params *params)
{
	printf("Executing parsed command\n");
	if (!sh->node || !sh->node->cmd)
		return (1);
	if (backup_stdin(&params->stdin_backup))
		return (1);
	check_command_features(sh, &params->has_pipe, &params->has_redirs,
		&params->has_heredoc);
	if (create_default_cat(sh, params->has_redirs, params->stdin_backup,
			&params->needs_cleanup))
		return (1);
	if (check_command_exists(sh, params->stdin_backup, params->needs_cleanup))
		return (1);
	return (0);
}

int	process_command_features(t_sh *sh, char **envp, t_exec_params *params)
{
	t_exec_args	args;

	args.sh = sh;
	args.envp = envp;
	args.redirs = params->redirs;
	args.clean_args = params->clean_args;
	args.stdin_backup = params->stdin_backup;
	args.has_heredoc = params->has_heredoc;
	args.needs_cleanup = params->needs_cleanup;
	if (params->has_redirs)
		if (process_redirections(sh, params))
			return (1);
	if (params->has_pipe)
		return (handle_piped_command(&args));
	print_command_details(params->clean_args, sh);
	return (0);
}

int	execute_command(t_sh *sh, char **envp, t_exec_params *params)
{
	t_exec_args	args;
	char		**cmd_to_exec;

	args.sh = sh;
	args.envp = envp;
	args.redirs = params->redirs;
	args.clean_args = params->clean_args;
	args.stdin_backup = params->stdin_backup;
	args.has_heredoc = params->has_heredoc;
	args.needs_cleanup = params->needs_cleanup;
	if (params->clean_args)
		cmd_to_exec = params->clean_args;
	else
		cmd_to_exec = sh->node->cmd->split_cmd;
	if (cmd_to_exec && is_builtin(cmd_to_exec[0]))
		return (exec_builtin_command(&args, cmd_to_exec));
	else
	{
		exec_external_with_cleanup(&args);
		return (0);
	}
}

int	exec_parsed_command(t_sh *sh, char **envp)
{
	t_exec_params	params;
	t_command_vars	vars;

	params.redirs = NULL;
	params.clean_args = NULL;
	init_command_variables(&vars);
	params.stdin_backup = vars.stdin_backup;
	params.has_heredoc = vars.has_heredoc;
	params.needs_cleanup = vars.needs_cleanup;
	params.redirs = vars.redirs;
	params.clean_args = vars.clean_args;
	if (setup_command_execution(sh, &params))
		return (1);
	if (process_command_features(sh, envp, &params))
		return (1);
	return (execute_command(sh, envp, &params));
}
