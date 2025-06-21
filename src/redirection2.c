/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:44:09 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/20 12:37:17 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	exec_child_process(t_redir_args *redir_data)
{
	t_reds	*current;

	if (redir_data->stdin_fd != -1)
	{
		if (dup2(redir_data->stdin_fd, STDIN_FILENO) == -1)
			perror("dup2 error on stdin");
	}
	if (redir_data->stdout_fd != -1)
	{
		if (dup2(redir_data->stdout_fd, STDOUT_FILENO) == -1)
			perror("dup2 error on stdout");
	}
	current = redir_data->redirs;
	while (current)
	{
		if (current->fd != -1)
			close(current->fd);
		current = current->next;
	}
	attempt_command_execution(redir_data->clean_args, redir_data->envp,
		redir_data->stdin_fd);
}

void	cleanup_parent_process(t_reds *redirs, pid_t pid, int *status)
{
	t_reds	*current;

	current = redirs;
	while (current)
	{
		if (current->fd != -1)
			close(current->fd);
		current->fd = -1;
		current = current->next;
	}
	waitpid(pid, status, 0);
}

int	exec_redirs(char **cmd_args, char **envp, t_reds *redirs)
{
	pid_t			pid;
	int				stdin_fd;
	int				stdout_fd;
	int				status;
	t_redir_args	redir_data;

	setup_redir_fds(redirs, &stdin_fd, &stdout_fd);
	redir_data.stdin_fd = stdin_fd;
	redir_data.stdout_fd = stdout_fd;
	redir_data.redirs = redirs;
	redir_data.clean_args = cmd_args;
	redir_data.envp = envp;
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
		exec_child_process(&redir_data);
	cleanup_parent_process(redirs, pid, &status);
	if (WIFEXITED(status))
		last_signal_code(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		last_signal_code(128 + WTERMSIG(status));
	return (0);
}

int	is_redirection_with_arg(char **args, int i)
{
	return ((ft_strncmp(args[i], ">", 2) == 0 || ft_strncmp(args[i], ">>",
				3) == 0 || ft_strncmp(args[i], "<", 2) == 0
			|| ft_strncmp(args[i], "<<", 3) == 0) && args[i + 1]);
}

int	count_cmd_args(char **args)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (args[i])
	{
		if (is_redirection_with_arg(args, i))
			i += 2;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}
