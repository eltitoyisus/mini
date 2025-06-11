/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:10:11 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/09 19:10:11 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	fill_command_args(t_sh *sh, t_parse *parse)
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
			handle_pipe_token(&cmd_node, &count, &current);
		}
		else if (is_command_token(current->type_token) && cmd_node
			&& cmd_node->split_cmd)
		{
			process_cmd_token(current, cmd_node, &count);
			current = current->next;
		}
		else
			current = current->next;
	}
	if (cmd_node && cmd_node->split_cmd)
		cmd_node->split_cmd[count] = NULL;
}

void	execute_child_process(t_child_proc *proc_data)
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
	if (execve(proc_data->path, proc_data->clean_args, proc_data->envp) == -1)
	{
		write(2, proc_data->clean_args[0], ft_strlen(proc_data->clean_args[0]));
		write(2, ": execution failed\n", 19);
		exit(EXIT_FAILURE);
	}
}

void	handle_parent_process(t_parent_proc *parent_data)
{
	int		status;
	t_reds	*current;

	signal(SIGINT, SIG_IGN);
	if (parent_data->redirs)
	{
		current = parent_data->redirs;
		while (current)
		{
			if (current->fd != -1)
				close(current->fd);
			current->fd = -1;
			current = current->next;
		}
		free_redirs(parent_data->redirs);
	}
	waitpid(parent_data->pid, &status, 0);
	ft_signals();
	free(parent_data->path);
	if (parent_data->clean_args != parent_data->sh->node->cmd->split_cmd)
		free_args(parent_data->clean_args);
	if (WIFSIGNALED(status))
		last_signal_code(128 + WTERMSIG(status));
	else if (WIFEXITED(status))
		last_signal_code(WEXITSTATUS(status));
}

void	cleanup_resources(char *path, t_reds *redirs, char **clean_args,
		char **original_args)
{
	if (path)
		free(path);
	if (redirs)
		free_redirs(redirs);
	if (clean_args != original_args && clean_args)
		free_args(clean_args);
}

int	validate_command(t_sh *sh)
{
	if (!sh->node->cmd || !sh->node->cmd->split_cmd
		|| !sh->node->cmd->split_cmd[0])
	{
		write(2, "Command not found\n", 18);
		return (0);
	}
	return (1);
}
