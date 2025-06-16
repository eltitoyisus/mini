/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:41:53 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/16 21:24:47 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	free_redirs(t_reds *head)
{
	free_red(head);
}

int	open_all_redirs(t_reds *head)
{
	t_reds	*current;

	current = head;
	while (current)
	{
		current->fd = open_redir(current);
		if (current->fd < 0)
		{
			perror("open");
			return (-1);
		}
		current = current->next;
	}
	return (0);
}

void	setup_redir_fds(t_reds *redirs, int *stdin_fd, int *stdout_fd)
{
	t_reds	*current;

	*stdin_fd = -1;
	*stdout_fd = -1;
	current = redirs;
	while (current)
	{
		if (current->type == INRED || current->type == HEREDOC)
			*stdin_fd = current->fd;
		else if (current->type == OURED || current->type == D_OURED)
			*stdout_fd = current->fd;
		current = current->next;
	}
}

void	execute_specific_command(char *path, char **args, char **envp)
{
	if (path)
	{
		execve(path, args, envp);
		free(path);
	}
}

void	attempt_command_execution(char **cmd_args, char **envp, int stdin_fd)
{
	char	*path;
	char	*cat_args[2];

	cat_args[0] = "cat";
	cat_args[1] = NULL;
	if (cmd_args && cmd_args[0])
	{
		path = get_path(envp, cmd_args[0]);
		if (path)
		{
			execute_specific_command(path, cmd_args, envp);
			free(path);
		}
		else if (is_builtin(cmd_args[0]))
		{
			exec_builtin(cmd_args, envp, NULL);
			exit(EXIT_SUCCESS);
		}
	}
	else if (stdin_fd != -1)
	{
		path = get_path(envp, "cat");
		execute_specific_command(path, cat_args, envp);
	}
	exit(EXIT_FAILURE);
}
