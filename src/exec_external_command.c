/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:05:40 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/09 12:05:40 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	setup_command_redirections(t_sh *sh, t_reds **redirs, char ***clean_args)
{
	if (has_redirection_in_cmd(sh->node->cmd))
	{
		*redirs = parse_redirection_from_cmd(sh->node->cmd);
		if (!*redirs)
			return (0);
		if (open_all_redirs(*redirs) < 0)
		{
			free_redirs(*redirs);
			return (0);
		}
		*clean_args = clean_cmd_args(sh->node->cmd);
		if (!*clean_args)
		{
			free_redirs(*redirs);
			return (0);
		}
	}
	else
	{
		*redirs = NULL;
		*clean_args = sh->node->cmd->split_cmd;
	}
	return (1);
}

int	get_command_path(char **envp, char **clean_args, t_reds *redirs,
		char **path)
{
	(void)redirs;
	*path = get_path(envp, clean_args[0]);
	if (!*path)
	{
		if (ft_strchr(clean_args[0], '/') == NULL)
		{
			write(2, clean_args[0], ft_strlen(clean_args[0]));
			write(2, ": command not found\n", 20);
			last_signal_code(127);
		}
		return (0);
	}
	return (1);
}

void	setup_redirection_fds(t_reds *redirs, int *stdin_fd, int *stdout_fd)
{
	t_reds	*current;

	if (redirs)
	{
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
}

void	handle_fork_error(char *path, t_reds *redirs, char **clean_args,
		t_sh *sh)
{
	write(2, "fork: failed to create process\n", 31);
	free(path);
	if (redirs)
		free_redirs(redirs);
	if (clean_args != sh->node->cmd->split_cmd)
		free_args(clean_args);
}
