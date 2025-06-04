/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:51:21 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/04 23:53:39 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	find_cmd(t_parse *parse)
{
	t_parse	*node_count;

	node_count = parse;
	while (node_count != NULL)
	{
		if (node_count->is_cmd == true)
			return (1);
		node_count = node_count->prev;
	}
	return (0);
}

void	add_flag(t_sh *sh, char *flag)
{
	int		i;
	char	**new_split;

	i = 0;
	while (sh->node->cmd->split_cmd[i])
		i++;
	new_split = malloc((i + 2) * sizeof(char *));
	i = 0;
	new_split[i] = ft_strdup(sh->node->cmd->split_cmd[i]);
	i += 1;
	new_split[i] = ft_strdup(flag);
	i += 1;
	new_split[i] = NULL;
	free_words(sh->node->cmd->split_cmd);
	sh->node->cmd->split_cmd = new_split;
	free_words(new_split);
	return ;
}

// TIPO DE ENTRADA DE INFORMACION PARA BUILTINS, COMANDO Y EL CASO DEL COMANDO CON LAS FLAGS
// -----------------------------------------------------------------------------------------



int	type_cmd_built_2(t_sh *sh, t_parse *parse, int i)
{
	int	j; // count_cmd

	j = 0;
	// printf("type_tokennnmm --> %d bool -> %d\n", parse->type_token, parse->next->is_built_arg);
	if (parse->type_token == BUILT && !parse->next)
	{
		sh->node->arg = ft_strdup(parse->line);
		sh->node->line_is->built = true;
		return (1);
	}
	else if ((is_built(parse) && parse->type_token == ARG)
			|| (parse->type_token == BUILT && parse->next->type_token == ARG))
	{
		printf("ENTRA BUILT CON ARGS\n");
		sh->node->built_args = ft_built_args(parse, sh->node->built_args);
		sh->node->line_is->built_args = true;
		return (printf("1\n"), 1);
	}
	else if (parse->type_token == CMD)
	{
		printf("sabessss\n");
		if (j > 0)
			ft_lstadd_back_cmd(sh->node->cmd);
		sh->node->cmd->cmd = ft_strdup(parse->line);
		sh->node->cmd->path = find_path(sh->env);
		sh->node->cmd->split_cmd = ft_split(sh->node->cmd->cmd, ' ');
		sh->node->cmd->index_token = i;
		sh->node->line_is->cmd = true;
		printf ("t\n");
		j++;
		printf("all god\n");
		return (1);
	}
	printf("0 \n");
	return (0);
}

// void	type_cmd_built(t_sh *sh, int token, char **input_s, int i)
// {
// 	if (token == BUILT)
// 	{
// 		sh->node->built->name = ft_strdup(input_s[i]);
// 	}
// 	else if (token == CMD)
// 	{
// 		sh->node->cmd->cmd = ft_strdup(input_s[i]);
// 		sh->node->cmd->path = find_path(sh->env);
// 		sh->node->is_cmd = true;
// 		sh->node->cmd->split_cmd = ft_split(sh->node->cmd->cmd, ' ');
// 	}
// 	else if (token == FLAG && find_cmd(sh)) // ESTE ES EL CASO DE LAS FLAGS POR EJEMPLO CAT -E QUE TAMBIEN PUEDE RECIBIR "CAT MAKEFILE ./SRC/MAIN.C ./INCLUDES/MAIN.H -E"
// 	{
// 		sh->node->is_flag = true;
// 		add_flag(sh, input_s[i]); // ENTONCES USO UNA (HEAD DE REFERENCIA PARA BUSCAR SI ES UNA FLAG DE UN CMD Y LE AGREGO LA FLAG A EL SPLIT DEL COMANDO)
// 	}


// }

// TIPO DE ENTRADA DE INFORMACION PARA REDIRECCIONES, PIPE
// -----------------------------------------------------------------------------------------

int	type_red_pipe_2(t_sh *sh, t_parse *parse, int i)
{
	if (parse->type_token == RED)
	{
		sh->node->cmd->red->type = id_red(parse);
		sh->node->line_is->with_reds = true;
		return (1);
	}
	else if (parse->type_token == FILES)
	{
		sh->node->line_is->with_reds = true;
		sh->node->cmd->red->type = id_file(parse);
		if (sh->node->cmd->red->type == DELIM)
			sh->node->cmd->red->delim = ft_strdup(parse->line);
		else
			sh->node->cmd->red->file = ft_strdup(parse->line);
		return (1);
	}
	else if (parse->type_token == PIPE)
	{
		sh->node->line_is->with_pipe = true;
		sh->node->n_cmd += 1;
		if (sh->node->n_cmd == 2)
		sh->node->cmd->pipe_in = i;
		else
		sh->node->cmd->pipe_out = i;
		// pipe(sh->node->cmd->pipefd);
		ft_lstadd_back_cmd(sh->node->cmd);
		return (1);
	}
	else
		return (0);
	has_more_reds(parse, sh->node->cmd->red);
}

// void	type_red_pipe(t_sh *sh, int token, char **input_s, int i)
// {
// 	if (token == RED)
// 	{
// 		sh->node->red->type = id_red(input_s, i);
// 	}
// 	else if (token == FILE)
// 	{
// 		sh->node->red->type = id_file(input_s, i);
// 		if (sh->node->red->type == DELIM)
// 			sh->node->red->delim = ft_strdup(input_s[i]);
// 		else
// 			sh->node->red->file = ft_strdup(input_s[i]);
// 	}
// 	else if (token == PIPE)
// 		sh->pipe_count += 1;
// }


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

