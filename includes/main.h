/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:01:45 by jramos-a          #+#    #+#             */
/*   Updated: 2025/05/09 10:25:05 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL
# define MINISHELL

# include "headers.h"
# include "struct.h"

//TX
void	ft_tx();
void	save_info(t_tx *tx, int i, int j);

// UTILS TO EVERYTHING
int		ft_error(char *msg, int ret);
void	free_words(char **words);
int		can_op(char *file);

// FTs DE LISTAS
void	ft_lstadd_back_sh(t_sh *sh); // Adaptada para la mini.
void	ft_lstclear_sh(t_sh *sh); // Adaptada para la mini.
void	ft_lstadd_back_parse(t_parse *parse);

// FREES OF LIST OR NODES
void	destroy_node(t_node *node);
void	free_built(t_built *built);
void	free_cmd(t_cmd *cmd);
void	free_red(t_reds *red);
void	free_pipe(t_pipe *w_pipe);

// PARSE
void	parse_comm(t_sh *sh, char **env);
// void	info_to_struct(t_sh *sh, int type_token, char **input_s, int i);
void info_to_struct_2(t_parse *parse, t_sh *sh, int i, char **split_input);
// void	type_cmd_built(t_sh *sh, int token, char **input_s, int i);
void	type_cmd_built_2(t_sh *sh, t_parse *parse, int i);
void	type_red_pipe_2(t_sh *sh, t_parse *parse, int i, char **split_input);
// void	type_red_pipe(t_sh *sh, int token, char **input_s, int i);
char	**add_flag(char *flag, char **split_cmd);
int		find_cmd(t_sh *sh);


// SIGNALS
void	ft_signals(void);
void	ctrl_c(int sign);

// SHELL FACTORY OR INITS

t_sh	*shell_factory(char **envp);
t_node	*node_factory(void);
t_cmd	*cmd_factory(void);

t_built	*init_built(void);
t_pipe	*init_pipe(void);
t_reds	*init_redir(void);
t_parse	*init_parse(void);

// PROMPT
char	*ft_prompt(void);

// EXEC COMMAND
char *find_path(char **envp);
char *try_executable_path(char **paths, char *command);
char *get_path(char **envp, char *command);
void fork_and_exec(char *command, char **envp);
void free_args(char **args);
void exec_command(char *command, char **envp, t_sh *sh);

// BUILT INS
int	exec_echo(char **args, char **envp);
int	exec_pwd(void);
int exec_cd(char **args, t_sh *sh);
int	exec_exit(void);

// EXEC BUILT INS
int is_builtin(char *command);
int	exec_builtin(char **args, char **envp, t_sh *sh);
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
// void *safe_malloc(size_t size, bool calloc_flag);
// void *safe_realloc(void *ptr, size_t old_size, size_t new_size);
// void safe_getcwd(char *buf, size_t size);
// void safe_chdir(const char *path);
// void safe_close(int fd);
// int safe_open(const char *path, t_open_flags flags);
// void safe_dup2(int oldfd, int newfd);

#endif
