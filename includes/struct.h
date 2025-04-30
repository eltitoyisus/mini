/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:01:47 by jramos-a          #+#    #+#             */
/*   Updated: 2025/04/30 10:13:17 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H

# include "../includes/main.h"

typedef struct s_built
{
	char	*name;

}	t_built;

typedef struct s_pipe
{
	pid_t	*pids; // Mejor pensamos los pipes como si fueran multiples desde el inicio mi OPINION.
	int		*pipefd[2];
	t_reds	*rds;
}	t_pipe;

typedef struct s_reds // REDIRECCIONES
{
	char *red;
	// FALTA MIRAR MÁS ESTA PARTE QUE NO ESTOY MUY SEGURO DE COMO HACERLO

}	t_reds;

typedef struct s_cmd
{
	char	**split_cmd;
	char	*line_cmd;
	t_pipe	w_pipe; // "with pipe" <---- Esto es por si el comando tiene pipe entonces entra a esta estructura a gestionar los pipes
	// Falta mirar si nos conviene más tener la path spliteada aqui para reusarla con otros comandos

}	t_cmd;

// Falta saber que más tipos de datos

typedef struct s_node
{
	t_cmd	*cmd;
	t_built	*built;

}	t_node;

typedef struct s_sh
{
	t_node	*node;
	char	*input;
	char	*prompt;

}	t_sh;

#endif

