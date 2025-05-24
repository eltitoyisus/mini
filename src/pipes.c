/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:11:40 by jramos-a          #+#    #+#             */
/*   Updated: 2025/05/24 08:45:09 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	is_pipe(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return (0);
	while (args[i])
	{
		if (ft_strncmp(args[i], "|", 2) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	count_pipes(char **args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!args)
		return (0);
	while (args[i])
	{
		if (ft_strncmp(args[i], "|", 2) == 0)
			count++;
		i++;
	}
	return (count);
}

void	free_commands(char ***commands, int k)
{
	int	i;
	int	j;

	i = 0;
	if (!commands)
		return ;
	while (i < k)
	{
		j = 0;
		while (commands[i] && commands[i][j])
		{
			free(commands[i][j]);
			j++;
		}
		free(commands[i]);
		i++;
	}
	free(commands);
}

char	***split_command(char **args, int num_cmds)
{
	char	***commands;
	int		i;
	int		j;
	int		k;
	int		start;
	int		len;

	i = 0;
	j = 0;
	k = 0;
	start = 0;
	commands = malloc(sizeof(char **) * (num_cmds + 1));
	if (!commands)
		return (NULL);
	while (args[j])
	{
		if (ft_strncmp(args[j], "|", 2) == 0 || args[j + 1] == NULL)
		{
			if (args[j + 1] == NULL && ft_strncmp(args[j], "|", 2) != 0)
				len = j - start + 1;
			else
				len = j - start;
			commands[k] = malloc(sizeof(char *) * (len + 1));
			if (!commands[k])
			{
				free_commands(commands, k);
				return (NULL);
			}
			i = 0;
			while (i < len)
			{
				commands[k][i] = ft_strdup(args[start + i]);
				if (!commands[k][i])
				{
					while (--i >= 0)
						free(commands[k][i]);
					free_commands(commands, k + 1);
					return (NULL);
				}
				i++;
			}
			commands[k][i] = NULL;
			k++;
			start = j + 1;
		}
		j++;
	}
	commands[k] = NULL;
	return (commands);
}

void	pipe_command(char **args, char **envp)
{
	char	*path;

	if (!args || !args[0])
	{
		printf("Invalid command\n");
		exit(EXIT_FAILURE);
	}
	if (is_builtin(args[0]))
	{
		if (exec_builtin(args, envp, NULL))
			exit(EXIT_SUCCESS);
		exit(EXIT_FAILURE);
	}
	path = get_path(envp, args[0]);
	if (path)
	{
		execve(path, args, envp);
		free(path);
	}
	printf("Command not found: %s\n", args[0]);
	exit(EXIT_FAILURE);
}

void	close_pipe_fds(int fd_prev, int fd[2], int pipe_stage)
{
	if (fd_prev != -1)
		close(fd_prev);
	if (pipe_stage)
	{
		close(fd[0]);
		close(fd[1]);
	}
}

void	execute_pipe_chain(t_sh *sh, char ***cmds, char **envp)
{
	int		i;
	int		fd_prev;
	int		fd[2];
	int		status;
	pid_t	*pids;

	i = 0;
	fd_prev = -1;
	if (!sh->node || !sh->node->cmd)
		return ;
	pids = malloc(sizeof(pid_t) * sh->pipe_count);
	if (!pids)
		return ;
	sh->node->cmd->pids = pids;
	while (i < sh->pipe_count)
	{
		if (i < sh->pipe_count - 1)
			if (pipe(fd) == -1)
			{
				free(pids);
				sh->node->cmd->pids = NULL;
				return ;
			}
		pids[i] = fork();
		if (pids[i] == -1)
		{
			free(pids);
			sh->node->cmd->pids = NULL;
			return ;
		}
		if (pids[i] == 0)
		{
			if (i > 0)
			{
				dup2(fd_prev, STDIN_FILENO);
				close(fd_prev);
			}
			if (i < sh->pipe_count - 1)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
			}
			pipe_command(cmds[i], envp);
		}
		if (i > 0)
			close(fd_prev);
		if (i < sh->pipe_count - 1)
		{
			fd_prev = fd[0];
			close(fd[1]);
		}
		i++;
	}
	i = 0;
	while (i < sh->pipe_count)
	{
		waitpid(pids[i], &status, 0);
		if (i == sh->pipe_count - 1)
		{
			if (WIFEXITED(status))
				last_signal_code(WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				last_signal_code(128 + WTERMSIG(status));
		}
		i++;
	}
	free(pids);
	sh->node->cmd->pids = NULL;
}

int	do_pipe(char **argv, char **envp, t_sh *sh)
{
	char	***all_cmds;
	int		i;
	int		saved_pipe_count;
	int		saved_n_cmd;
	int		saved_pipefd[2];

	if (!sh || !sh->node || !sh->node->cmd)
		return (-1);
	saved_pipe_count = sh->pipe_count;
	saved_n_cmd = sh->node->n_cmd;
	saved_pipefd[0] = sh->node->cmd->pipefd[0];
	saved_pipefd[1] = sh->node->cmd->pipefd[1];
	i = 0;
	sh->pipe_count = count_pipes(argv) + 1;
	sh->node->cmd->pipefd[0] = -1;
	sh->node->cmd->pipefd[1] = -1;
	sh->node->cmd->pipe_in = 0;
	sh->node->cmd->pipe_out = 0;
	sh->node->n_cmd = sh->pipe_count;
	all_cmds = split_command(argv, sh->pipe_count);
	if (!all_cmds)
	{
		sh->pipe_count = saved_pipe_count;
		sh->node->n_cmd = saved_n_cmd;
		sh->node->cmd->pipefd[0] = saved_pipefd[0];
		sh->node->cmd->pipefd[1] = saved_pipefd[1];
		return (-1);
	}
	execute_pipe_chain(sh, all_cmds, envp);
	if (all_cmds)
	{
		for (i = 0; i < sh->pipe_count && all_cmds[i]; i++)
			free_args(all_cmds[i]);
		free(all_cmds);
	}
	sh->pipe_count = saved_pipe_count;
	sh->node->n_cmd = saved_n_cmd;
	sh->node->cmd->pipefd[0] = saved_pipefd[0];
	sh->node->cmd->pipefd[1] = saved_pipefd[1];
	return (0);
}

int	handle_pipes(t_sh *sh, char **envp)
{
	char	**args;
	int		result;

	result = 0;
	if (!sh || !sh->input)
		return (1);
	args = ft_split(sh->input, ' ');
	if (!args)
		return (1);
	if (is_pipe(args))
		result = do_pipe(args, envp, sh);
	free_args(args);
	return (result);
}
