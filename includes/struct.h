/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:01:47 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/22 13:59:25 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../includes/main.h"

typedef struct s_type
{
	bool			cmd;
	bool			with_pipe;
	bool			built;
	bool			with_reds;
}					t_type;

typedef struct s_reds
{
	char			*file;
	char			*delim;
	int				type;
	int				fd;
	int				heredoc_index;
	struct s_reds	*next;
}					t_reds;

typedef struct s_cmd
{
	char			**split_cmd;
	char			*path;
	char			*cmd;
	int				index_token;
	t_reds			*red;
	pid_t			*pids;
	int				pipefd[2];
	int				pipe_in;
	int				pipe_out;
	struct s_cmd	*next;
	struct s_cmd	*prev;
	struct s_cmd	*head;
}					t_cmd;

typedef struct s_node
{
	t_cmd			*cmd;
	char			*arg;
	int				n_cmd;
	bool			is_quote;
	t_type			*line_is;
}					t_node;

typedef struct s_sh
{
	t_node			*node;
	char			*input;
	char			*prompt;
	char			*pwd;
	char			**env;
	int				pipe_count;
}					t_sh;

typedef struct s_parse
{
	char			*line;
	bool			is_flag;
	bool			is_cmd;
	int				type_token;
	int				quote_error;
	struct s_parse	*next;
	struct s_parse	*prev;
}					t_parse;

enum				e_case_quotes
{
	SIMPLE,
	DOUBLE,
	ERROR
};

enum				e_type_token
{
	BUILT,
	CMD,
	PIPE,
	RED,
	ARG,
	FLAG,
	FILES
};

enum				e_type_red
{
	OUTFILE_APP,
	OUTFILE_TR,
	INFILE,
	DELIM,
	HEREDOC,
	INRED,
	OURED,
	D_OURED
};

typedef struct s_exec_params
{
	int				stdin_backup;
	int				has_heredoc;
	int				needs_cleanup;
	int				has_pipe;
	int				has_redirs;
	t_reds			*redirs;
	char			**clean_args;
}					t_exec_params;

typedef struct s_command_vars
{
	int				stdin_backup;
	int				has_heredoc;
	int				needs_cleanup;
	t_reds			*redirs;
	char			**clean_args;
}					t_command_vars;

typedef struct s_pipe_vars
{
	int				i;
	int				pipe_count;
	int				cmd_count;
	char			**cmd_args;
}					t_pipe_vars;

typedef struct s_exec_context
{
	pid_t			pid;
	char			*path;
	t_reds			*redirs;
	char			**clean_args;
	int				stdin_fd;
	int				stdout_fd;
	char			**envp;
}					t_exec_context;

typedef struct s_exec_args
{
	t_sh			*sh;
	char			**envp;
	t_reds			*redirs;
	char			**clean_args;
	int				stdin_backup;
	int				has_heredoc;
	int				needs_cleanup;
}					t_exec_args;

typedef struct s_child_proc
{
	int				stdin_fd;
	int				stdout_fd;
	t_reds			*redirs;
	char			*path;
	char			**clean_args;
	char			**envp;
}					t_child_proc;

typedef struct s_parent_proc
{
	pid_t			pid;
	char			*path;
	t_reds			*redirs;
	char			**clean_args;
	t_sh			*sh;
}					t_parent_proc;

typedef struct s_redir_exec
{
	pid_t			pid;
	char			*path;
	int				stdin_fd;
	int				stdout_fd;
	char			**clean_args;
}					t_redir_exec;

typedef struct s_redir_args
{
	int				stdin_fd;
	int				stdout_fd;
	t_reds			*redirs;
	char			*path;
	char			**clean_args;
	char			**envp;
}					t_redir_args;

typedef struct s_pipe_command_args
{
	int				i;
	int				cmd_count;
	char			***commands;
	char			**envp;
	pid_t			*pids;
	int				*prev_pipe;
}					t_pipe_command_args;

typedef struct s_pipe_execution
{
	int				i;
	int				cmd_count;
	int				prev_pipe;
	int				pipefd[2];
	t_reds			*redirs;
	char			**clean_args;
	char			**exec_args;
	pid_t			*pids;
	char			**envp;
}					t_pipe_execution;

typedef struct s_pipe_setup
{
	int				pipefd[2];
	t_reds			*redirs;
	char			**clean_args;
	pid_t			*pids;
}					t_pipe_setup;

typedef struct s_cmd_segment
{
	int				start;
	int				cmd_len;
	int				cmd_idx;
}					t_cmd_segment;

typedef struct s_token_counters
{
	int				start;
	int				cmd_idx;
}					t_token_counters;

typedef struct s_pipe_cmd_args
{
	int				i;
	t_sh			*sh;
	int				fd_prev;
	int				fd[2];
	t_cmd			*current_cmd;
	char			**envp;
}					t_pipe_cmd_args;

typedef struct s_pipe_handle
{
	int				i;
	int				fd_prev;
	int				fd[2];
	t_cmd			*current_cmd;
	pid_t			*pids;
}					t_pipe_handle;

typedef struct s_pipe_context
{
	int				i;
	int				cmd_count;
	int				pipefd[2];
	t_reds			*redirs;
	char			**clean_args;
}					t_pipe_context;

typedef struct s_pipe_child_args
{
	char			**cmd_args;
	char			**envp;
	t_reds			*redirs;
	int				stdin_fd;
	int				stdout_fd;
	char			*path;
}					t_pipe_child_args;

typedef struct s_parent_cleanup
{
	int				*prev_pipe;
	int				pipefd[2];
	int				i;
	int				cmd_count;
	t_reds			**redirs;
	char			***clean_args;
}					t_parent_cleanup;

typedef struct s_heredoc_state
{
	int				active;
	int				last_fd;
	char			*last_filename;
}					t_heredoc_state;

typedef struct s_heredoc_context
{
	int				fd;
}					t_heredoc_context;

typedef struct s_cleanup_args
{
	t_reds			**redirs;
	char			***clean_args;
}					t_cleanup_args;

typedef struct s_position
{
	int				x;
	int				y;
}					t_position;

typedef struct s_rng_state
{
	unsigned int	seed;
	unsigned int	fake_time;
}					t_state;

typedef struct s_snake
{
	t_position		body[100];
	int				length;
	int				direction;
}					t_snake;

#endif
