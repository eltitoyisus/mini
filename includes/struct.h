/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:01:47 by jramos-a          #+#    #+#             */
/*   Updated: 2025/04/30 16:01:03 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H

# include "../includes/main.h"

enum e_type_token // TIPOS DE TOKENS
{
	BUILT,
	CMD,
	PIPE,
	RED,
	ARG,
};

enum e_type_red // TIPOS DE REDIRECCIONES --> CON SUS O_FLAGS CORRESPONDIENTES DEPENDIENDO DE LO QUE NECESITEMOS.
{
	OUTFILE_APPEND,
	OUTFILE_TRUNCATE,
	INFILE,
	HEREDOC,
};

enum e_admissions // PERMISOS PARA FILES O FLAGS!
{
	APPEND,
	TRUNCATE,
};

typedef struct s_built
{
	char	*name;
}	t_built;

typedef struct s_reds
{
	char	*file;
	char	*type;
	int		fd;
}	t_reds;


typedef struct s_pipe
{
	pid_t	*pids;
	int		pipefd[2];
	t_reds	*red;
	int		pipe_count;
	int		pipe_pos;
	int		pipe_in;
	int		pipe_out;
}	t_pipe;

typedef struct s_cmd
{
	char	**split_cmd;
	char	*line_cmd;
	char	*path;
	char	*cmd;
	char	*args;
}	t_cmd;


typedef struct s_node
{
	t_cmd	*cmd;
	t_built	*built;
	t_reds	*red;
	t_pipe	*w_pipe;
	char	*arg;
	struct s_node	*next;
}	t_node;

typedef struct s_sh
{
	t_node	*node;
	char	*input;
	char	*prompt;
	char	*pwd;
}	t_sh;

#endif
