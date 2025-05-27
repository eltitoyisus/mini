/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:01:47 by jramos-a          #+#    #+#             */
/*   Updated: 2025/05/27 11:20:36 by dacastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../includes/main.h"

// -----------------------------------------------------
typedef struct s_type // BOOLEANOS
{
	bool	cmd;
	bool	with_pipe;
	bool	built;
	bool	with_reds;
}	t_type;
//_---------------------------------------------------------


typedef struct s_reds
{
	char				*file; // NOMBRE DE ARCHIVO O DELIMITADOR
	char				*delim;
	int					type; // TIPO DE RED O ARCHIVO
	int					fd;
	struct s_reds		*next;
}	t_reds;

typedef struct s_cmd
{
	char			**split_cmd;
	char			*path;
	char			*cmd;
	int				index_token;
	t_reds			*red;
	pid_t			*pids; // array de procesos
	int				pipefd[2]; // puntero de pipes
	int				pipe_in;
	int				pipe_out;
	struct s_cmd	*next;
	struct s_cmd	*prev;
	struct s_cmd	*head;
}	t_cmd;




// ---------------------------------------------------------------

typedef struct s_node
{
	t_cmd	*cmd;
	char	*arg;
	int		n_cmd; // Número de comandos.
	bool	is_quote;
	t_type	*line_is; // el tipo de la linea completa
}	t_node;

//-------------------------------------------------------------



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
	char			*line;
	bool			is_flag;
	bool			is_cmd;
	int				type_token;
	struct s_parse	*next;
	struct s_parse	*prev;
	struct s_parse	*head;
}	t_parse;

enum e_case_quotes
{
	SIMPLE,
	DOUBLE,
	ERROR
};

enum e_type_token // TIPOS DE TOKENS
{
	BUILT,
	CMD,
	PIPE,
	RED,
	ARG,
	FLAG,
	FILES
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
