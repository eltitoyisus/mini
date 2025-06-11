/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_redirs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:42:17 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/09 19:42:17 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	process_redirection_nodes(t_reds *redirs, int *stdin_fd, int *stdout_fd)
{
	t_reds	*current;

	current = redirs;
	while (current)
	{
		if (current->type == INRED || current->type == HEREDOC)
		{
			*stdin_fd = current->fd;
			if (*stdin_fd == -1)
				return (printf("Error: invalid stdin redirection fd\n"), 1);
		}
		else if (current->type == OURED || current->type == D_OURED)
		{
			*stdout_fd = current->fd;
			if (*stdout_fd == -1)
				return (printf("Error: invalid stdout redirection fd\n"), 1);
		}
		current = current->next;
	}
	return (0);
}

void	setup_redirections(int stdin_fd, int stdout_fd, int *stdin_backup,
		int *stdout_backup)
{
	if (stdin_fd != -1)
		*stdin_backup = dup(STDIN_FILENO);
	if (stdout_fd != -1)
		*stdout_backup = dup(STDOUT_FILENO);
	if (stdin_fd != -1 && *stdin_backup != -1)
		dup2(stdin_fd, STDIN_FILENO);
	if (stdout_fd != -1 && *stdout_backup != -1)
		dup2(stdout_fd, STDOUT_FILENO);
}

void	restore_redirections(int stdin_fd, int stdout_fd, int stdin_backup,
		int stdout_backup)
{
	if (stdin_fd != -1 && stdin_backup != -1)
	{
		dup2(stdin_backup, STDIN_FILENO);
		close(stdin_backup);
	}
	if (stdout_fd != -1 && stdout_backup != -1)
	{
		dup2(stdout_backup, STDOUT_FILENO);
		close(stdout_backup);
	}
}

int	exec_builtin_with_redirs(char **args, char **envp, t_sh *sh, t_reds *redirs)
{
	int	result;
	int	stdin_backup;
	int	stdout_backup;
	int	stdin_fd;
	int	stdout_fd;

	stdin_backup = -1;
	stdout_backup = -1;
	stdin_fd = -1;
	stdout_fd = -1;
	if (redirs)
	{
		if (process_redirection_nodes(redirs, &stdin_fd, &stdout_fd))
			return (1);
		setup_redirections(stdin_fd, stdout_fd, &stdin_backup, &stdout_backup);
	}
	result = exec_builtin(args, envp, sh);
	if (redirs)
		restore_redirections(stdin_fd, stdout_fd, stdin_backup, stdout_backup);
	return (result);
}
