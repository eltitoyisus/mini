/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:51:37 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/09 19:51:37 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	cleanup_redir_error(t_exec_params *params, t_sh *sh)
{
	printf("Failed to clean command arguments\n");
	if (params->stdin_backup != -1)
		close(params->stdin_backup);
	free_redirs(params->redirs);
	if (params->needs_cleanup && sh->node->cmd->split_cmd)
		free_args(sh->node->cmd->split_cmd);
	return (1);
}

int	handle_open_redir_error(t_exec_params *params, t_sh *sh)
{
	printf("Failed to open redirections\n");
	if (params->stdin_backup != -1)
		close(params->stdin_backup);
	free_redirs(params->redirs);
	if (params->needs_cleanup && sh->node->cmd->split_cmd)
		free_args(sh->node->cmd->split_cmd);
	return (1);
}

int	handle_parse_redir_error(t_exec_params *params, t_sh *sh)
{
	if (params->stdin_backup != -1)
		close(params->stdin_backup);
	if (params->needs_cleanup && sh->node->cmd->split_cmd)
		free_args(sh->node->cmd->split_cmd);
	return (1);
}

int	process_redirections(t_sh *sh, t_exec_params *params)
{
	printf("Processing redirections\n");
	params->redirs = parse_redirection_from_cmd(sh->node->cmd);
	if (!params->redirs)
		return (handle_parse_redir_error(params, sh));
	if (params->has_heredoc)
		printf("Heredoc detected\n");
	if (open_all_redirs(params->redirs) < 0)
		return (handle_open_redir_error(params, sh));
	params->clean_args = clean_cmd_args(sh->node->cmd);
	if (!params->clean_args)
		return (cleanup_redir_error(params, sh));
	return (0);
}
