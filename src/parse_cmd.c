/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:51:21 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/05/08 16:29:16 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	find_cmd(t_sh *sh)
{
	t_node	*node_count;
	node_count = sh->node->head;

	while (node_count != NULL)
	{
		if (node_count->is_cmd == true)
			return (1);
		node_count = node_count->next;
	}
	return (0);
}

char	**add_flag(char *flag, char **split_cmd)
{
	int		i;
	char	**new_split;

	new_split = split_cmd;
	i = 1;
	new_split[i] = malloc(ft_strlen(flag) * sizeof(char));
	new_split[i] = flag;
	return (new_split);
}

// TIPO DE ENTRADA DE INFORMACION PARA BUILTINS, COMANDO Y EL CASO DEL COMANDO CON LAS FLAGS
// -----------------------------------------------------------------------------------------

void	type_cmd_built(t_sh *sh, int token, char **input_s, int i)
{
	if (token == BUILT)
	{
		sh->node->built->name = ft_strdup(input_s[i]);
	}
	else if (token == CMD)
	{
		sh->node->cmd->cmd = ft_strdup(input_s[i]);
		sh->node->cmd->path = find_path(sh->env);
		sh->node->is_cmd = true;
		sh->node->cmd->split_cmd = ft_split(sh->node->cmd->cmd, ' ');
	}
	else if (token == FLAG && find_cmd(sh)) // ESTE ES EL CASO DE LAS FLAGS POR EJEMPLO CAT -E QUE TAMBIEN PUEDE RECIBIR "CAT MAKEFILE ./SRC/MAIN.C ./INCLUDES/MAIN.H -E"
	{
		sh->node->cmd->split_cmd = add_flag(input_s[i], sh->node->cmd->split_cmd); // ENTONCES USO UNA (HEAD DE REFERENCIA PARA BUSCAR SI ES UNA FLAG DE UN CMD Y LE AGREGO LA FLAG A EL SPLIT DEL COMANDO)
	}


}

// TIPO DE ENTRADA DE INFORMACION PARA REDIRECCIONES, PIPE
// -----------------------------------------------------------------------------------------


void	type_red_pipe(t_sh *sh, int token, char **input_s, int i)
{
	if (token == RED)
	{
		sh->node->red->type = id_red();
		sh->node->red->type = ft_strdup(input_s[i]);
	}
	else if (token == PIPE)
		sh->node->w_pipe->pipe_count += 1;
}


// int	c_flag(char *input)
// {
// 	if ()
// }

// int	is_flag(char *input)
// {
// 	if (ft_strncmp(input, "-", 1) == 0)
// 		return (FLAG);
// 	else
// 		return (CMD);
// }


// char	*case_flag(t_sh *sh, char **split_input, int i, int type_tok)
// {
// 	char	*res;

// 	res = split_input[i];
// 	if (type_tok == CMD && !ft_strncmp(split_input[i + 1], "-", 1))
// 	{
// 		res = ft_strjoin(split_input[i], " ");
// 		res = ft_strjoin(split_input[i], split_input[i + 1]);
// 		i++;
// 		return (res);
// 	}
// 	else
// 		return (res);
// }

