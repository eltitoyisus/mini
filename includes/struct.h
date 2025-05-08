/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:01:47 by jramos-a          #+#    #+#             */
/*   Updated: 2025/05/08 19:49:28 by daniel-cast      ###   ########.fr       */
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
	FLAG,
	FILE
};

enum e_type_red // TIPOS DE REDIRECCIONES --> CON SUS O_FLAGS CORRESPONDIENTES DEPENDIENDO DE LO QUE NECESITEMOS.
{
	OUTFILE_APP,
	OUTFILE_TR,
	INFILE,
	DELIM,
	HEREDOC, // "<<"
	INRED, // "<"
	OURED, // ">"
	D_OURED // ">>"

};

typedef struct s_built
{
	char	*name;
}	t_built;

typedef struct s_reds
{
	char	*file; // NOMBRE DE ARCHIVO O DELIMITADOR
	char	*delim;
	int		type; // TIPO DE RED O ARCHIVO
	int		fd;
	bool	is_quote;

}	t_reds;


typedef struct s_pipe
{
	pid_t	*pids;
	int		pipefd[2];
	int		pipe_pos;
	int		pipe_in;
	int		pipe_out;
}	t_pipe;

typedef struct s_cmd
{
	char	**split_cmd;
	char	*path;
	char	*cmd;
}	t_cmd;


typedef struct s_node
{
	t_cmd	*cmd;
	t_built	*built;
	t_reds	*red;
	t_pipe	*w_pipe;
	char	*arg;
	bool	is_cmd;
	bool	is_flag;
	struct s_node	*head;
	struct s_node	*next;
}	t_node;

typedef struct s_sh
{
	t_node	*node;
	char	*input;
	char	*prompt;
	char	*pwd;
	char	**env;
	int		pipe_count; // Numero de pipes mejor tenerlo aqui
}	t_sh;

typedef struct s_parse
{
	char	*line;
	bool	is_flag;
	bool	is_cmd;
	int		type_token;
	struct s_parse	*next;
	struct s_parce	*head;
}	t_parse;


//	TETRIS DEJAMELO A MI JEJE

typedef struct s_tx
{
	int		x;
	int		y;
	char	**matx;
}	t_tx;

typedef struct s_piece
{
	int	x;
	int	y;
	char	***piece;
}	t_piece;


#endif
