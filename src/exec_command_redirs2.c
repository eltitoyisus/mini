/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_redirs2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:44:01 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/15 15:18:50 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	setup_redir_command_redirections(t_sh *sh, t_reds **redirs,
		char ***clean_args)
{
	if (!sh->node->cmd || !sh->node->cmd->split_cmd
		|| !sh->node->cmd->split_cmd[0])
	{
		write(2, "Command not found\n", 18);
		return (-1);
	}
	*redirs = parse_redirection_from_cmd(sh->node->cmd);
	if (!(*redirs))
		return (-1);
	if (open_all_redirs(*redirs) < 0)
	{
		write(2, "Error opening redirections\n", 26);
		free_redirs(*redirs);
		return (-1);
	}
	*clean_args = clean_cmd_args(sh->node->cmd);
	if (!(*clean_args))
	{
		free_redirs(*redirs);
		return (-1);
	}
	return (0);
}

int	get_redir_command_path(char **envp, char **clean_args, t_reds *redirs,
		char **path)
{
	*path = get_path(envp, clean_args[0]);
	if (!(*path))
	{
		if (ft_strchr(clean_args[0], '/') == NULL)
		{
			write(2, clean_args[0], ft_strlen(clean_args[0]));
			write(2, ": command not found\n", 20);
		}
		if (redirs)
			free_redirs(redirs);
		if (clean_args)
			free_args(clean_args);
		return (-1);
	}
	return (0);
}

void	handle_redir_fork_error(char *path, t_reds *redirs, char **clean_args,
		t_sh *sh)
{
	write(2, "fork: failed to create process\n", 31);
	if (path)
		free(path);
	if (redirs)
		free_redirs(redirs);
	if (clean_args && sh->node->cmd && clean_args != sh->node->cmd->split_cmd)
		free_args(clean_args);
}

void	execute_redir_child_process(t_child_proc *proc_data)
{
	t_reds	*current;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (proc_data->stdin_fd != -1)
		dup2(proc_data->stdin_fd, STDIN_FILENO);
	if (proc_data->stdout_fd != -1)
		dup2(proc_data->stdout_fd, STDOUT_FILENO);
	if (proc_data->redirs)
	{
		current = proc_data->redirs;
		while (current)
		{
			if (current->fd != -1)
				close(current->fd);
			current = current->next;
		}
	}
	execve(proc_data->path, proc_data->clean_args, proc_data->envp);
	write(2, proc_data->clean_args[0], ft_strlen(proc_data->clean_args[0]));
	write(2, ": execution failed\n", 19);
	free(proc_data->path);
	exit(EXIT_FAILURE);
}

void	handle_redir_parent_process(t_parent_proc *parent_data)
{
	int		status;
	t_reds	*current;

	(void)parent_data->clean_args;
	(void)parent_data->sh;
	signal(SIGINT, SIG_IGN);
	if (parent_data->redirs)
	{
		current = parent_data->redirs;
		while (current)
		{
			if (current->fd != -1)
				close(current->fd);
			current = current->next;
		}
	}
	waitpid(parent_data->pid, &status, 0);
	ft_signals();
	free(parent_data->path);
	if (WIFSIGNALED(status))
		last_signal_code(128 + WTERMSIG(status));
	else if (WIFEXITED(status))
		last_signal_code(WEXITSTATUS(status));
}
