/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:01:45 by jramos-a          #+#    #+#             */
/*   Updated: 2025/04/25 14:01:44 by jramos-a         ###   ########.fr       */
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
void    redir_in(char *file_in);
void redir_out(char *cmd_name, char **cmd_lst, char **envp, char *stdout_file, char *stderr_file);

// PIPES
void	exec_pipe(char *cmd_name, char **cmd_lst, char **envp, char *err);
void    exec_line(char *line, char **envp);
// static void _tokenize(char **ptr, char *delim, char **tokens, int *i);
int tokenize(char *linea, char *delim, char **tokens, int max_tokens);
void process_redirs(char **args, char **redir);

// SAFE
void *safe_malloc(size_t size, bool calloc_flag);
void *safe_realloc(void *ptr, size_t old_size, size_t new_size);
void safe_getcwd(char *buf, size_t size);
void safe_chdir(const char *path);
void safe_close(int fd);
int safe_open(const char *path, t_open_flags flags);
void safe_dup2(int oldfd, int newfd);

#endif
