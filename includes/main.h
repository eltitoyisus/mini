/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:01:45 by jramos-a          #+#    #+#             */
/*   Updated: 2025/04/29 11:43:50 by jramos-a         ###   ########.fr       */
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
int has_redirection(char **args);
int handle_redir_error(char **args);
t_reds *parse_redirection(char **args);
int open_redir(t_reds *redir);
int exec_redir(char **args, char **envp, t_reds *redir);
int do_redir(char *command, char **envp);
int handle_redirs(char *command, char **envp);

// PIPES
int is_pipe(char **args);
char	***split_command(char **args, int num_cmds);
int	count_pipes(char **args);
void	pipe_command(char **args, char **envp);
void	execute_pipe_chain(t_pipe *pipe_info, char ***cmds, char **envp);
int do_pipe(char **argv, char **envp);
int handle_pipes(char *command, char **envp);

#endif
