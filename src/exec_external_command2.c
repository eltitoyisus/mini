/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_command2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:54:59 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/21 17:01:02 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	initialize_exec_context(t_exec_context *ctx)
{
	ctx->pid = -1;
	ctx->path = NULL;
	ctx->redirs = NULL;
	ctx->clean_args = NULL;
	ctx->stdin_fd = -1;
	ctx->stdout_fd = -1;
}

int	prepare_exec_context(t_sh *sh, char **envp, t_exec_context *ctx)
{
	if (!validate_command(sh))
		return (0);
	if (!setup_command_redirections(sh, &ctx->redirs, &ctx->clean_args))
		return (0);
	if (!get_command_path(envp, ctx->clean_args, ctx->redirs, &ctx->path))
	{
		cleanup_resources(ctx->path, ctx->redirs, ctx->clean_args,
			sh->node->cmd->split_cmd);
		return (0);
	}
	return (1);
}

void	execute_command_fork(t_sh *sh, char **envp, t_exec_context *ctx)
{
	t_child_proc	child_data;
	t_parent_proc	parent_data;

	ctx->pid = fork();
	if (ctx->pid == -1)
		handle_fork_error(ctx->path, ctx->redirs, ctx->clean_args, sh);
	else if (ctx->pid == 0)
	{
		child_data.stdin_fd = ctx->stdin_fd;
		child_data.stdout_fd = ctx->stdout_fd;
		child_data.redirs = ctx->redirs;
		child_data.path = ctx->path;
		child_data.clean_args = ctx->clean_args;
		child_data.envp = envp;
		execute_child_process(&child_data);
	}
	else
	{
		parent_data.pid = ctx->pid;
		parent_data.path = ctx->path;
		parent_data.redirs = ctx->redirs;
		parent_data.clean_args = ctx->clean_args;
		parent_data.sh = sh;
		handle_parent_process(&parent_data);
	}
}

void	exec_external_command(t_sh *sh, char **envp)
{
	t_exec_context	ctx;

	initialize_exec_context(&ctx);
	if (!prepare_exec_context(sh, envp, &ctx))
		return ;
	setup_redirection_fds(ctx.redirs, &ctx.stdin_fd, &ctx.stdout_fd);
	execute_command_fork(sh, envp, &ctx);
}
