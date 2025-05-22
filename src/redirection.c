/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:11:23 by jramos-a          #+#    #+#             */
/*   Updated: 2025/05/22 17:55:21 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	has_redirection(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_strncmp(args[i], ">", 2) == 0 || ft_strncmp(args[i], ">>",
				3) == 0 || ft_strncmp(args[i], "<", 2) == 0
			|| ft_strncmp(args[i], "<<", 3) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	handle_redir_error(char **args)
{
	free_args(args);
	printf("Invalid redirection syntax\n");
	return (1);
}

int	get_redir_type(char *redir_str)
{
	if (ft_strncmp(redir_str, ">>", 3) == 0)
		return (D_OURED);
	if (ft_strncmp(redir_str, ">", 2) == 0)
		return (OURED);
	if (ft_strncmp(redir_str, "<<", 3) == 0)
		return (HEREDOC);
	if (ft_strncmp(redir_str, "<", 2) == 0)
		return (INRED);
	return (-1);
}

t_reds	*parse_redirection(char **args)
{
	t_reds	*head;
	t_reds	*current;
	int		i;
	t_reds	*new;

	head = NULL;
	current = NULL;
	i = 0;
	while (args[i])
	{
		if ((ft_strncmp(args[i], ">", 2) == 0 || ft_strncmp(args[i], ">>",
					3) == 0 || ft_strncmp(args[i], "<", 2) == 0
				|| ft_strncmp(args[i], "<<", 3) == 0) && args[i + 1])
		{
			new = malloc(sizeof(t_reds));
			if (!new)
			{
				free_redirs(head);
				return (NULL);
			}
			new->type = get_redir_type(args[i]);
			new->file = ft_strdup(args[i + 1]);
			new->delim = NULL;
			new->next = NULL;
			new->fd = -1;
			if (!head)
				head = new;
			else
				current->next = new;
			current = new;
			args[i] = NULL;
			args[i + 1] = NULL;
			i += 2;
		}
		else
			i++;
	}
	return (head);
}

int	open_redir(t_reds *redir)
{
	int	fd;

	if (!redir || !redir->file)
		return (-1);
	if (redir->type == D_OURED)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->type == OURED)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == INRED)
		fd = open(redir->file, O_RDONLY);
	else if (redir->type == HEREDOC)
		fd = heredoc(redir->file);
	else
		return (-1);
	return (fd);
}

int	heredoc(char *delimiter)
{
	char	*line;
	int		fd;
	pid_t	pid;
	int		status;

	fd = open("heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("heredoc: open");
		return (-1);
	}
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		while (1)
		{
			line = readline("heredoc> ");
			if (!line)
				exit(1);
			if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
			{
				free(line);
				exit(0);
			}
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
	}
	close(fd);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	ft_signals();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		last_signal_code(130);
		unlink("heredoc.tmp");
		return (-1);
	}
	return (open("heredoc.tmp", O_RDONLY));
}

void	free_redirs(t_reds *head)
{
	t_reds	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		if (temp->file)
			free(temp->file);
		if (temp->delim)
			free(temp->delim);
		if (temp->fd != -1)
			close(temp->fd);
		free(temp);
	}
}

int	open_all_redirs(t_reds *head)
{
	t_reds	*current;

	current = head;
	while (current)
	{
		current->fd = open_redir(current);
		if (current->fd < 0)
			return (-1);
		current = current->next;
	}
	return (0);
}

int	exec_redirs(char **args, char **envp, t_reds *redirs)
{
	pid_t	pid;
	char	*path;
	t_reds	*current;
	int		stdin_fd;
	int		stdout_fd;
	char	*cat_args[] = {"cat", NULL};
	int		status;

	stdin_fd = -1;
	stdout_fd = -1;
	current = redirs;
	while (current)
	{
		if (current->type == INRED || current->type == HEREDOC)
			stdin_fd = current->fd;
		else if (current->type == OURED || current->type == D_OURED)
			stdout_fd = current->fd;
		current = current->next;
	}
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		if (stdin_fd != -1)
			dup2(stdin_fd, STDIN_FILENO);
		if (stdout_fd != -1)
			dup2(stdout_fd, STDOUT_FILENO);
		current = redirs;
		while (current)
		{
			if (current->fd != -1)
				close(current->fd);
			current = current->next;
		}
		if (args && args[0])
		{
			path = get_path(envp, args[0]);
			if (path)
			{
				execve(path, args, envp);
				free(path);
			}
			else if (is_builtin(args[0]))
			{
				exec_builtin(args, envp, NULL);
				exit(EXIT_SUCCESS);
			}
		}
		if (stdin_fd != -1 && (!args || !args[0]))
		{
			path = get_path(envp, "cat");
			if (path)
			{
				execve(path, cat_args, envp);
				free(path);
			}
		}
		perror("execve");
		exit(EXIT_FAILURE);
	}
	current = redirs;
	while (current)
	{
		if (current->fd != -1)
			close(current->fd);
		current->fd = -1;
		current = current->next;
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		last_signal_code(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		last_signal_code(128 + WTERMSIG(status));
	return (0);
}

int	do_redir(char *command, char **envp)
{
	char	**args;
	t_reds	*redirs;
	int		result;

	args = ft_split(command, ' ');
	if (!args)
		return (1);
	redirs = parse_redirection(args);
	if (!redirs)
		return (handle_redir_error(args));
	if (open_all_redirs(redirs) < 0)
	{
		free_args(args);
		free_redirs(redirs);
		return (1);
	}
	result = exec_redirs(args, envp, redirs);
	free_args(args);
	free_redirs(redirs);
	return (result);
}

int	handle_redirs(char *command, char **envp)
{
	char	**args;
	int		result;

	args = ft_split(command, ' ');
	if (!args)
		return (1);
	if (has_redirection(args))
		result = do_redir(command, envp);
	else
		result = 0;
	free_args(args);
	return (result);
}
