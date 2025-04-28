/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:01:45 by jramos-a          #+#    #+#             */
/*   Updated: 2025/04/27 09:27:23 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL
# define MINISHELL

# include "headers.h"
# include "struct.h"

// EXEC COMMAND
char *find_path(char **envp);
char *try_executable_path(char **paths, char *command);
char *get_path(char **envp, char *command);
void fork_and_exec(char *command, char **envp);
void free_args(char **args);
void exec_command(char *command, char **envp);

// BUILT INS
int	exec_echo(char **args, char **envp);
int	exec_pwd(void);
int exec_cd(char **args);
int	exec_exit(void);

// EXEC BUILT INS
int is_builtin(char *command);
int	exec_builtin(char **args, char **envp);
int	exec_env(char **envp);

// ENV
int	exec_env(char **envp);
int env_unset(char **argv, char **envp);
int env_export(char **argv, char **envp);
int	echo_var(char **argv, char **envp);

// REDIRECTION
int do_redir(char *command, char **envp);
int open_redir(char *filename, char *type);
int handle_redirs(char *command, char **envp);
int has_redirection(char **args);
int exec_redir(char **args, char **envp, int fd);
int handle_redir_error(char **args);

// PIPES
int is_pipe(char **args);
char **split_args(char **argv, int pipe_pos);
void pipe_command(char **args, char **envp);
int do_pipe(char **argv, char **envp);
int handle_pipes(char *command, char **envp);

#endif
