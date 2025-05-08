/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:51:21 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/05/08 17:25:48 by daniel-cast      ###   ########.fr       */
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

char	add_flag(t_sh *sh, char *flag)
{
	int		i;
	char	**new_split;
	t_node	*node_count;

	i = 1;
	node_count = sh->node->head;
	new_split = NULL;
	while (node_count != NULL)
	{
		if (node_count->is_cmd == true)
		{
			new_split = node_count->cmd->split_cmd;
			new_split[i] = malloc(ft_strlen(flag) * sizeof(char));
			new_split[i] = flag;
			new_split[++i] = NULL;
			node_count->cmd->split_cmd = new_split;
			free_words(new_split);
			return ;
		}
		node_count = node_count->next;
	}
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
		sh->node->is_flag = true;
		add_flag(sh, input_s[i]); // ENTONCES USO UNA (HEAD DE REFERENCIA PARA BUSCAR SI ES UNA FLAG DE UN CMD Y LE AGREGO LA FLAG A EL SPLIT DEL COMANDO)
	}


}

// TIPO DE ENTRADA DE INFORMACION PARA REDIRECCIONES, PIPE
// -----------------------------------------------------------------------------------------


void	type_red_pipe(t_sh *sh, int token, char **input_s, int i)
{
	if (token == RED)
	{
		sh->node->red->type = id_red(input_s, i);
	}
	else if (token == FILE)
	{
		sh->node->red->type = id_file(input_s, i);
		if (sh->node->red->type == DELIM)
			sh->node->red->delim = ft_strdup(input_s[i]);
		else
			sh->node->red->file = ft_strdup(input_s[i]);
	}
	else if (token == PIPE)
		sh->pipe_count += 1;
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

