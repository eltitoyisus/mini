/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:24:19 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/05/13 16:31:35 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static int	other_cases(char *input, char **input_split, int i)
{
	if (!ft_strncmp(input, "<", 1) || !ft_strncmp(input, ">", 1)
		|| !ft_strncmp(input, "<<", 1) || !ft_strncmp(input, ">>", 1))
		return (RED);
	else if (!ft_strncmp(input_split[i - 1], "<", 1) && can_op(input) || !ft_strncmp(input_split[i - 1], ">", 1)
		|| !ft_strncmp(input_split[i - 1], ">>", 2) || !ft_strncmp(input_split[i - 1], "<<", 2))
		return (FILE);
	else if (!ft_strncmp(input, "|", 1))
		return (PIPE);
	else
		return (ARG);
}

static int cases_builds(char *input)
{
	if (ft_strncmp(input, "-", 1))
		return (FLAG);
	if (!input)
		return (ARG);
	if (!ft_strncmp(input, "pwd", 3))
		return (BUILT);
	else if (!ft_strncmp(input, "cd", 2))
		return (BUILT);
	else if (!ft_strncmp(input, "echo", 4))
		return (BUILT);
	else if (!ft_strncmp(input, "export", 6))
		return (BUILT);
	else if (!ft_strncmp(input, "unset", 5))
		return (BUILT);
	else if (!ft_strncmp(input, "env", 3))
		return (BUILT);
	else if (!ft_strncmp(input, "exit", 4))
	{
		free(input);
		ft_error("exit", 127);
	}
	else
		return (CMD);
}

static int	cases_com(char *input, char **env)
{
	char	**split_com;
	char	*executable_path;

	split_com = ft_split(input, ' ');
	if (!split_com)
		return (ft_error("ERROR: split failed\n", 1), ARG);
	executable_path = get_path(env, split_com[0]);
	if (!executable_path)
	{
		free_words(split_com);
		return (ARG);
	}
	if (access(executable_path, X_OK) == 0)
	{
		free_words(split_com);
		free(executable_path);
		return (CMD);
	}
	free(executable_path);
	free_words(split_com);
	return (ARG);
}

static int	n_token(char *input, char **env, char **input_split, int i)
{
	int	value_token;

	value_token = cases_builds(input);
	if (value_token == FLAG)
		return (FLAG);
	if (value_token == BUILT)
		return (BUILT);
	value_token = cases_com(input, env);
	if (value_token == CMD)
		return (CMD);
	else if (value_token == ARG)
		return (ARG);
	value_token = other_cases(input, input_split, i);
	if (value_token == RED)
		return (RED);
	else if (value_token == PIPE)
		return (PIPE);
	else if (value_token == FILE)
			return (FILE);
	return (ARG);
}

// void info_to_struct(t_sh *sh, int type_token, char **input_s, int i)
// {
// 	if (!sh || !sh->node || !input_s)
// 		return;
// 	type_cmd_built(sh, type_token, input_s, i);
// 	type_red_pipe(sh, type_token, input_s, i);
// 	if (type_token == ARG)
// 	{
// 		sh->node->arg = ft_strdup(input_s[i]);
// 	}
// 	// Siempre que metamos la info del node que estemos creamos otro
// 	ft_lstadd_back_sh(sh);
// }
void	info_to_struct_2(t_parse *parse, t_sh *sh, int i, char **split_input)
{
	if (!parse || !parse->line)
		return;
	type_cmd_built_2(sh, parse, i);
	type_red_pipe_2(sh, parse, i, split_input);
	if (parse->type_token == ARG)
	{
		sh->node->arg = ft_strdup(parse->line);
		sh->node->index_token_arg = i;
	}
		// Siempre que metamos la info del node que estemos creamos otro
}


void	bool_active(t_parse *parse)
{
	t_parse	*count;

	count = parse->head;
	while (count != NULL)
	{
		if (count->type_token == CMD)
			count->is_cmd = true;
		else if (parse->type_token == FLAG)
			count->is_flag = true;
		count = count->next;
	}
}

void	ft_quotes(t_parse *parse)
{
	while (ft_strchr(parse->line, '\"'))
	{
		ft_strtrim(parse->line, '"');
		if (ft_strchr(parse->line, "\'"))
			return ;
	}
	while (ft_strchr(parse->line, '\'') && !ft_strchr(parse->line, '"'))
	{
		ft_strtrim(parse->line, "'");
		if (ft_strchr(parse->line, '\"'))
			return ;
	}
	if (!ft_strchr(parse->line, '\"') && ft_strchr(parse->line, '"'))
		ft_menu_quote();
	if (!ft_strchr(parse->line, '\'') && ft_strchr(parse->line, "'"))
		ft_menu_quote();
}

void	ft_controls(t_parse *parse)
{
	bool_active(parse);
	ft_quotes(parse);
}

void	ft_parse(t_parse *parse, t_sh *sh, char **env)
{
	char	**split_input;
	int		i;

	split_input = ft_split(sh->input, ' ');
	i = 0;
	while (parse != NULL)
	{
		if (i != 0)
		{ // si no es el primer node y existe una palabra creamos un nuevo node para reconocer que tipo de token será ese y hacerle todo el procedimiento.
			ft_lstadd_back_parse(parse); // En utils puedes ver esta funcion, es de listas pero esta adaptada.
			parse = parse->next;
		}
		parse->line = split_input[i];
		parse->type_token = n_token(split_input[i], env, split_input, i);
		ft_controls(parse); // AQUI SE HARAN LAS IMPLEMENTACION QUE TENGO QUE INVESTIGAR PARA ASEGURARNOS BIEN QUE NO HALLAN ERRORES.
		info_to_struct_2(parse, sh, i, split_input);
		parse = parse->next;
		i++;
	}
	free_words(split_input);
}

void	parse_comm(t_sh *sh, char **env)
{
	// int		type_token;
	// char	**input_split;
	// int		i;
	t_parse	*parse;

	parse = init_parse();
	parse->head = parse;
	if (!sh || !sh->input)
		return;
	// i = 0;
	// input_split = ft_split(sh->input, ' ');
	// if (!input_split)
	// 	return;
	// while (input_split[++i])
	// {
	// 	if (i != 0)
	// 	{ // si no es el primer node y existe una palabra creamos un nuevo node para reconocer que tipo de token será ese y hacerle todo el procedimiento.
	// 		ft_lstadd_back_sh(sh); // En utils puedes ver esta funcion, es de listas pero esta adaptada.
	// 		sh->node = sh->node->next;
	// 	}
		ft_parse(parse, sh, env);
		// input_split[i] = case_flag(sh, input_split, i, type_token);
	// 	type_token = n_token(input_split[i], env, input_split, i);
	// 	info_to_struct(sh, type_token, input_split, i);
	// }
	ft_lstclear_sh(sh);
	// free_words(input_split);
}
