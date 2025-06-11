/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_redirs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:19:47 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/09 13:19:47 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	cleanup_redir_resources(char *path, t_reds *redirs, char **clean_args,
		char **original_args)
{
	if (path)
		free(path);
	if (redirs)
		free_redirs(redirs);
	if (clean_args && clean_args != original_args)
		free_args(clean_args);
}

int	validate_and_prepare_command(t_sh *sh, char **envp, char ***clean_args,
		char **path)
{
	if (!sh->node->cmd || !sh->node->cmd->split_cmd
		|| !sh->node->cmd->split_cmd[0])
	{
		write(2, "Command not found\n", 18);
		return (0);
	}
	*clean_args = sh->node->cmd->split_cmd;
	*path = get_path(envp, (*clean_args)[0]);
	if (!*path)
	{
		if (ft_strchr((*clean_args)[0], '/') == NULL)
		{
			write(2, (*clean_args)[0], ft_strlen((*clean_args)[0]));
			write(2, ": command not found\n", 20);
		}
		return (0);
	}
	return (1);
}

void	setup_child_data(t_child_proc *child_data, t_redir_exec *re,
		t_reds *redirs, char **envp)
{
	child_data->stdin_fd = re->stdin_fd;
	child_data->stdout_fd = re->stdout_fd;
	child_data->redirs = redirs;
	child_data->path = re->path;
	child_data->clean_args = re->clean_args;
	child_data->envp = envp;
}

void	setup_parent_data(t_parent_proc *parent_data, t_redir_exec *re,
		t_reds *redirs, t_sh *sh)
{
	parent_data->pid = re->pid;
	parent_data->path = re->path;
	parent_data->redirs = redirs;
	parent_data->clean_args = re->clean_args;
	parent_data->sh = sh;
}

void	exec_external_command_with_redirs(t_sh *sh, char **envp, t_reds *redirs)
{
	t_redir_exec	re;
	t_child_proc	child_data;
	t_parent_proc	parent_data;

	setup_redir_fds(redirs, &re.stdin_fd, &re.stdout_fd);
	if (!validate_and_prepare_command(sh, envp, &re.clean_args, &re.path))
		return ;
	re.pid = fork();
	if (re.pid == -1)
		handle_redir_fork_error(re.path, redirs, re.clean_args, sh);
	else if (re.pid == 0)
	{
		setup_child_data(&child_data, &re, redirs, envp);
		execute_redir_child_process(&child_data);
	}
	else
	{
		setup_parent_data(&parent_data, &re, redirs, sh);
		handle_redir_parent_process(&parent_data);
	}
}
