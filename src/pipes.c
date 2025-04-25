/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:11:40 by jramos-a          #+#    #+#             */
/*   Updated: 2025/04/25 10:11:40 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	exec_pipe(char *cmd_name, char **cmd_lst, char **envp, char *err)
{
	int	pipe_fd[2];
	pid_t pid;
	int fd_err;
	int status;
	(void)cmd_lst;

	if (pipe(pipe_fd) == -1)
		exit(EXIT_FAILURE);
	if ((pid = fork()) == -1)
		exit(EXIT_FAILURE);
	if (!pid)
	{
		safe_close(pipe_fd[0]);
		safe_dup2(pipe_fd[1], STDOUT_FILENO);
		safe_close(pipe_fd[1]);
		if (err)
		{
			fd_err = safe_open(err, WRITE);
			safe_dup2(fd_err, STDERR_FILENO);
			safe_close(fd_err);
		}
		exec_command(cmd_name, envp);
	}
	else
	{
		safe_close(pipe_fd[1]);
		safe_dup2(pipe_fd[0], STDIN_FILENO);
		safe_close(pipe_fd[0]);
		waitpid(pid, &status, 0);
	}
}

void exec_line(char *line, char **envp)
{
	char *cmds[MAX_CMDS];
	char *args[MAX_ARGS];
	char *redirs[MAX_REDIRS];
	int num_comandos;
	int i;
	(void)envp;

	tokenize(line, "|", cmds, MAX_CMDS);
	i = -1;
	while (cmds[++i])
	{
		num_comandos = tokenize(cmds[i], " \t\n", args, MAX_ARGS);
		process_redirs(args, redirs);

		if (i == 0 && redirs[0])
			redir_in(redirs[0]);
		if (i != num_comandos - 1)
			exec_pipe(args[0], args, envp, redirs[2]);
		else
			redir_out(args[0], args, envp, redirs[1], redirs[2]);
	}
}

void process_redirs(char **args, char **redir)
{
	int i;

	i = -1;
	redir[0] = NULL;
	redir[1] = NULL;
	redir[2] = NULL;
	while (args[++i])
	{
		if (!strcmp(args[i], "<"))
		{
			redir[0] = args[i+1];
			args[i] = NULL;
			args[i + 1] = NULL;
			i++; // Añadiendo i++ en cada uno de los if's, conseguimos que se puedan detectar más de una redirecciones para el mismo comando
		}
		else if (!strcmp(args[i], ">"))
		{
			redir[1] = args[i+1];
			args[i] = NULL;
			args[i + 1] = NULL;
			i++;
		}
		else if (!strcmp(args[i], "2>"))
		{
			redir[2] = args[i+1];
			args[i] = NULL;
			args[i + 1] = NULL;
			i++;
		}
	}
}

static void _tokenize(char **ptr, char *delim, char **tokens, int *i)
{
	char quote;

	if (**ptr == '\"' || **ptr == '\'')
	{
		quote = **ptr;
		(*ptr)++; // Saltamos la comilla
		tokens[(*i)++] = *ptr;  // El token comienza después de la comilla
		while (**ptr && **ptr != quote) // Buscamos la comilla de cierre correspondiente
			(*ptr)++;
		if (**ptr == quote)
		{
			**ptr = '\0';  // Finalizamos el token y avanzamos con el siguiente
			(*ptr)++;
		}
	}
	else
	{
		tokens[(*i)++] = *ptr; // Mismo proceso para argumentos sin comillas
		while (**ptr && !ft_strchr(delim, **ptr))
			(*ptr)++;
		if (**ptr)
		{
			**ptr = '\0';
			(*ptr)++;
		}
	}
}

int tokenize(char *linea, char *delim, char **tokens, int max_tokens)
{
	int i;
	char *ptr;

	i = 0;
	ptr = linea;
	while (*ptr && i < max_tokens - 1) // Recorremos la línea hasta que es distinto de \0 o hasta que hallamos obtenido (max_tokens) -1 strings
	{
		while (*ptr && ft_strchr(delim, *ptr)) // Saltamos delimitadores al inicio
			ptr++;
		if (!*ptr)
			break;
		_tokenize(&ptr, delim, tokens, &i);
	}
	tokens[i] = NULL;
	return (i);
}
