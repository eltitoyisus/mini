/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:01:45 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/18 09:58:41 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "headers.h"
# include "struct.h"

// SNAKE
void			init_Game(snake *snake, position *fruit, t_state *state);
void			drawGame(const snake *snake, const position *fruit);
void			updateSnake(snake *snake);
int				checkCollision(snake *snake, position *fruit, t_state *state);
int				get_botton();
char			getch();
char			ft_getchar();
void			my_srand(unsigned int new_seed, t_state *state);
int				my_rand(t_state *state);
unsigned int	generate_seed(int iteration);
int				game_main();

// UTILS TO EVERYTHING
int				ft_error(char *msg, int ret);
void			free_words(char **words);
int				can_op(char *file);
void			free_args(char **args);
void			ft_itoa_into(int n, char *str);

// FTs DE LISTAS
void			ft_lstadd_back_sh(t_sh *sh);
void			ft_lstclear_sh(t_sh *sh);
void			ft_lstadd_back_parse(t_parse *parse);
void			ft_lstadd_back_cmd(t_cmd *cmd);
void			ft_lstclear_parse(t_parse *parse);

// IDENTIFIERS
int				id_red(t_parse *parse);
int				id_file(t_parse *parse);

// FREES OF LIST OR NODES
void			destroy_node(t_node *node);
void			free_cmd(t_cmd *cmd);
void			free_red(t_reds *red);
void			free_parse(t_parse *parse);

// PARSE CMD
int				find_cmd(t_parse *parse);
void			add_flag(t_sh *sh, char *flag);
void			type_cmd_built_2(t_sh *sh, t_parse *parse, int i);
void			type_red_pipe_2(t_sh *sh, t_parse *parse, int i);

// PARSE
void			info_to_struct_2(t_parse *parse, t_sh *sh, int i);
void			bool_active(t_parse *parse);
void			case_without_space(char *sp_input, char **env, t_parse *parse);
void			ft_parse(t_parse *parse, t_sh *sh, char **env);
void			parse_comm(t_sh *sh, char **env);

// PARSE 2
int				other_cases(char *input, char **input_split, int i);
int				cases_builds(char *input);
int				cases_com(char *input, char **env);
int				n_token(char *input, char **env, char **input_split, int i);
char			**save_tokens(t_parse *parse, int *token_count);

// PARSE 3
void			handle_double_redirection(char *sp_input, int *i,
					t_parse *parse);
void			handle_single_redirection(char *sp_input, int *i,
					t_parse *parse);
void			handle_pipe(char *sp_input, int *i, t_parse *parse);
void			handle_command_segment(char *cmd_segment, char **env,
					t_parse **parse);
void			handle_other_cases(char *sp_input, int *i, t_parse **parse,
					char **env);

// PARSE 4
void			handle_space_case(t_parse *parse, t_sh *sh, char **env);
void			prepare_token(t_parse *parse, char **split_input, int i,
					char **env);
void			finalize_parsing(t_parse *parse, t_sh *sh, int count,
					char **split_input);
void			process_with_spaces(t_parse *parse, t_sh *sh, char **env);
void			process_parse_nodes(t_parse *parse, t_sh *sh, int i);

// CASE NO SPACE
void			process_double_redirection(char *sp_input, int *i,
					t_parse *parse);
void			process_single_redirection(char *sp_input, int *i,
					t_parse *parse);
void			process_pipe_token(char *sp_input, int *i, t_parse *parse);
void			handle_command_parts(char **cmd_parts, t_parse **parse,
					char **env);
void			process_command_with_spaces(char *cmd_segment, t_parse **parse,
					char **env);
void			process_command_without_spaces(char *cmd_segment,
					t_parse **parse, char **env);
void			process_command_segment(char *sp_input, int *i, int *w,
					t_parse **parse);
void			handle_input_character(char *sp_input, int *i, int *w,
					t_parse **parse);
void			ft_controls(t_parse *parse);

// QUOTES
void			ft_quotes(t_parse *parse);
char			*cut_quotes(char *input);
int				id_cases(t_parse *parse);
int				case_double(t_parse *parse);
int				case_simple(t_parse *parse);
int				check_open(t_parse *parse, int type);

// SIGNALS
void			ft_signals(void);
void			ctrl_c(int sign);
int				last_signal_code(int code);

// SHELL FACTORY OR INITS
t_sh			*shell_factory(char **envp);
t_node			*node_factory(void);
t_cmd			*cmd_factory(void);
t_reds			*init_redir(void);
t_parse			*init_parse(void);

// PROMPT
char			*ft_prompt(void);

// GET PATH
int				print_path_error(char *command, char *message);
char			*handle_direct_path(char *command);
int				is_path_command(char *command);
char			**prepare_path_dirs(char **envp);
char			*find_path(char **envp);
char			*try_executable_path(char **paths, char *command);
char			*get_path(char **envp, char *command);

// EXEC COMMAND
int				exec_parsed_command(t_sh *sh, char **envp);
int				is_command_token(int type);
void			count_pipe_commands(t_sh *sh, t_parse *parse);
void			allocate_cmd_memory(t_cmd *cmd_node, int count);
void			allocate_first_commands(t_sh *sh, t_parse *parse);
void			allocate_last_command(t_sh *sh, t_parse *parse);

// EXEC COMMAND 2
void			init_command_variables(t_command_vars *vars);
int				backup_stdin(int *stdin_backup);
void			check_command_features(t_sh *sh, int *has_pipe, int *has_redirs,
					int *has_heredoc);
int				create_default_cat(t_sh *sh, int has_redirs, int stdin_backup,
					int *needs_cleanup);
int				check_command_exists(t_sh *sh, int stdin_backup,
					int needs_cleanup);

// EXEC COMMAND 3
int				process_redirections(t_sh *sh, t_exec_params *params);

void			print_command_details(char **clean_args, t_sh *sh);
int				handle_piped_command(t_exec_args *args);
int				exec_builtin_command(t_exec_args *args, char **cmd_to_exec);
void			exec_external_with_cleanup(t_exec_args *args);

// EXEC EXTERNAL COMMAND
void			exec_external_command(t_sh *sh, char **envp);
void			print_command_debug(t_sh *sh);
int				validate_command(t_sh *sh);
int				setup_command_redirections(t_sh *sh, t_reds **redirs,
					char ***clean_args);
int				get_command_path(char **envp, char **clean_args, t_reds *redirs,
					char **path);
void			setup_redirection_fds(t_reds *redirs, int *stdin_fd,
					int *stdout_fd);
void			handle_fork_error(char *path, t_reds *redirs, char **clean_args,
					t_sh *sh);
void			execute_child_process(t_child_proc *proc_data);
void			handle_parent_process(t_parent_proc *parent_data);

void			cleanup_resources(char *path, t_reds *redirs, char **clean_args,
					char **original_args);

// EXEC COMMAND REDIRS
void			exec_external_command_with_redirs(t_sh *sh, char **envp,
					t_reds *redirs);
int				setup_redir_command_redirections(t_sh *sh, t_reds **redirs,
					char ***clean_args);
int				get_redir_command_path(char **envp, char **clean_args,
					t_reds *redirs, char **path);
void			handle_redir_fork_error(char *path, t_reds *redirs,
					char **clean_args, t_sh *sh);
void			execute_redir_child_process(t_child_proc *proc_data);
void			handle_redir_parent_process(t_parent_proc *parent_data);
void			cleanup_redir_resources(char *path, t_reds *redirs,
					char **clean_args, char **original_args);

// BUILT INS
int				exec_echo(char **args, char **envp);
int				exec_pwd(void);
int				exec_cd(char **args, t_sh *sh);
int				exec_exit(t_sh *sh);


// EXEC BUILT INS
int				is_builtin(char *command);
int				exec_builtin(char **args, char **envp, t_sh *sh);
int				exec_env(char **args, char **envp);
// ENV
int				env_unset(char **argv, char **envp);
int				env_export(char **argv, char **envp);
int				echo_var(char **argv, int index, char **envp);
void			export_no_args(char **envp);
void free_env(char **env);

// REDIRECTION
int				has_redirection_in_cmd(t_cmd *cmd);
char			**prepare_cmd_args(char **args);
int				do_redir(char *command, char **envp);
int				handle_redirs(char *command, char **envp);
void free_exec_params(t_exec_params *params);


// REDIRECTION 2
void			exec_child_process(t_redir_args *redir_data);
void			cleanup_parent_process(t_reds *redirs, pid_t pid, int *status);
int				exec_redirs(char **cmd_args, char **envp, t_reds *redirs);
int				is_redirection_with_arg(char **args, int i);
int				count_cmd_args(char **args);

// CLEAN REDIRS
t_reds			*create_redirection_node(char **cmd_array, int i);
int				is_redirection_op(char **cmd_array, int i);
t_reds			*parse_redirection_from_cmd(t_cmd *cmd);
int				count_clean_args(t_cmd *cmd);
char			**clean_cmd_args(t_cmd *cmd);

// HANDLE REDIRS
int				has_redirection(char **args);
int				handle_redir_error(char **args);
int				get_redir_type(char *redir_str);
int				is_redir_with_target(char **args, int i);
t_reds			*create_redir_node(char **args, int i);

// HANDLE REDIRS 2
t_reds			*parse_redirection(char **args);
void			free_redirs(t_reds *head);
int				open_all_redirs(t_reds *head);
void			setup_redir_fds(t_reds *redirs, int *stdin_fd, int *stdout_fd);
void			attempt_command_execution(char **cmd_args, char **envp,
					int stdin_fd);

// HEREDOC
int				open_redir(t_reds *redir);
void			process_heredoc_input(int fd, char *delimiter);
int				handle_heredoc_parent(pid_t pid, int fd);
int				heredoc(char *delimiter);

// PIPES 2
int				is_pipe(char **args);
int				count_pipes(char **args);
void			free_commands(char ***commands, int k);
void			pipe_command(char **args, char **envp);
void			close_pipe_fds(int fd_prev, int fd[2], int pipe_stage);

// PIPES 3
void			initialize_pipe_chain(int cmd_count, pid_t **pids,
					int *prev_pipe);
void			handle_redirections(t_cmd *temp_cmd, t_reds **redirs,
					char ***clean_args);
void			setup_pipe(int i, int cmd_count, int pipefd[2]);
void			handle_pipe_setup_error(t_reds *redirs, char **clean_args,
					pid_t *pids);
int				create_pipe_if_needed(int i, int cmd_count, int pipefd[2]);
void			apply_redirections(t_reds *redirs);
void			initialize_cleanup(t_parent_cleanup *cleanup,
					t_pipe_command_args *args, int pipefd[2],
					t_cleanup_args *output);
void			execute_pipe_child_process(t_pipe_execution *pipe_exec);
void			handle_parent_cleanup(t_parent_cleanup *cleanup);

// PIPES 4
void			init_pipe_command_vars(t_sh *sh, t_pipe_vars *vars);
char			***allocate_commands_array(int pipe_count);
int				allocate_command_segment(char ***commands, char **cmd_args,
					t_cmd_segment seg);

void			cleanup_commands(char ***commands, int cmd_idx, int j);
int				parse_command_segments(char ***commands, char **cmd_args,
					int pipe_count);

// PIPES 5
int				setup_pipe_execution(t_sh *sh, pid_t **pids, int *fd_prev,
					t_cmd **current_cmd);
int				create_pipe_for_command(t_sh *sh, int i, int fd[2],
					pid_t *pids);
int				fork_pipe_command(pid_t *pids, int i);
void			execute_pipe_command(t_pipe_cmd_args args);
t_pipe_cmd_args	init_pipe_cmd_args(t_pipe_handle *ph, t_sh *sh, char **envp);

void			handle_pipe_parent_cleanup(int *fd_prev, int fd[2], int i,
					t_sh *sh);
t_cmd_segment	init_cmd_segment(int cmd_idx, int start, int cmd_len);

// PIPES
void			wait_for_children(pid_t *pids, int cmd_count);
void			execute_pipe_chain_new(char ***commands, int cmd_count,
					char **envp);
int				process_piped_command(t_sh *sh, char **envp);
void			wait_for_pipe_commands(pid_t *pids, int cmd_count);
int				handle_pipes(t_sh *sh, char **envp);

// EXEC PIPE CHAIN
void			handle_pipe_fork_error(pid_t *pids, t_reds *redirs,
					char **clean_args);
void			prepare_pipe_command(t_cmd *temp_cmd, char **commands_i,
					t_reds **redirs, char ***clean_args);
char			**select_exec_args(char **clean_args, char **commands_i);
void			process_pipe_command(t_pipe_command_args *args);
void			execute_pipe_chain_new(char ***commands, int cmd_count,
					char **envp);

// COMMANDS
int				is_command_token(int type);
void			count_pipe_commands(t_sh *sh, t_parse *parse);
void			allocate_first_commands(t_sh *sh, t_parse *parse);
void			allocate_last_command(t_sh *sh, t_parse *parse);
void			fill_command_args(t_sh *sh, t_parse *parse);
void			null_terminate_and_print(t_sh *sh);
void			build_command_args(t_sh *sh, t_parse *parse);
void			handle_pipe_token(t_cmd **cmd, int *count, t_parse **curr);
void			process_cmd_token(t_parse *current, t_cmd *cmd, int *count);
void			process_pipe(int *count, t_parse **current);

int				exec_parsed_command(t_sh *sh, char **envp);
t_type			*init_bools(void);
// int		process_piped_command(t_sh *sh, char **envp);
int				has_redirection_in_cmd(t_cmd *cmd);
t_reds			*parse_redirection_from_cmd(t_cmd *cmd);
char			**clean_cmd_args(t_cmd *cmd);
int				exec_builtin(char **args, char **envp, t_sh *sh);
int				exec_builtin_with_redirs(char **args, char **envp, t_sh *sh,
					t_reds *redirs);
int				open_all_redirs(t_reds *head);
int				space_case(char *input);
char			**inc_shlvl(char **envp);
void			process_input(t_sh *sh, char **envp);
void			shell_loop(t_sh *sh, char **envp);
void			free_shell(t_sh *sh);
void free_exec_params(t_exec_params *params);

#endif
