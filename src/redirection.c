/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:11:23 by jramos-a          #+#    #+#             */
/*   Updated: 2025/04/25 10:11:23 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void    redir_in(char *file_in)
{
	int fd_in;

	fd_in = safe_open(file_in, READ);
	safe_dup2(fd_in, STDIN_FILENO);
	safe_close(fd_in);
}

void redir_out(char *cmd_name, char **cmd_lst, char **envp, char *stdout_file, char *stderr_file)
{
	pid_t pid;
	int fd_out;
	int fd_err;
	int status;
	(void)cmd_lst;

	if ((pid = fork()) == -1)
		exit(EXIT_FAILURE);
	if (!pid)
	{
		if (stdout_file)
		{
			fd_out = safe_open(stdout_file, WRITE);
			safe_dup2(fd_out, STDOUT_FILENO);
			safe_close(fd_out);
		}
		if (stderr_file)
		{
			fd_err = safe_open(stderr_file, WRITE);
			safe_dup2(fd_err, STDERR_FILENO);
			safe_close(fd_err);
		}
		exec_command(cmd_name, envp);
	}
	else
		waitpid(pid, &status, 0);
}

