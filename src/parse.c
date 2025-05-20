/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:24:19 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/05/20 18:50:27 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static int	other_cases(char *input, char **input_split, int i)
{
	if (!ft_strncmp(input, "<", 1) || !ft_strncmp(input, ">", 1)
		|| !ft_strncmp(input, "<<", 1) || !ft_strncmp(input, ">>", 1))
		return (RED);
	else if ((!ft_strncmp(input_split[i - 1], "<", 1) && can_op(input)) || !ft_strncmp(input_split[i - 1], ">", 1)
		|| !ft_strncmp(input_split[i - 1], ">>", 2) || !ft_strncmp(input_split[i - 1], "<<", 2))
		return (FILES);
	else if (!ft_strncmp(input, "|", 1))
		return (PIPE);
	else
		return (ARG);
}

static int cases_builds(char *input)
{
	if (!input)
		return (ARG);
	if (ft_strncmp(input, "-", 1))
		return (FLAG);
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
	// else if (!ft_strncmp(input, "exit", 4))
	// {
	// 	free(input);
	// 	ft_error("exit", 127);
	// }
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

	if (input == NULL)
		return (-1);
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
	else if (value_token == FILES)
			return (FILES);
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
void	info_to_struct_2(t_parse *parse, t_sh *sh, int i)
{
	while (parse != NULL)
	{
		if (!parse || !parse->line)
		return ;
		type_cmd_built_2(sh, parse, i);
		type_red_pipe_2(sh, parse, i);
		if (parse->type_token == ARG)
		{
			sh->node->arg = ft_strdup(parse->line);
		}
		parse = parse->next;
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

void	ft_controls(t_parse *parse)
{
	bool_active(parse);
	ft_quotes(parse);
	printf("lineaaa ---->> %s\n", parse->line);
}

// char	**cases_split(void)
// {
// 	if ()
// 	{

// 	}

// }

void	ft_parse(t_parse *parse, t_sh *sh, char **env)
{
	char	**split_input;
	int		i;

	split_input = ft_split(sh->input, ' ');
	i = 0;
	while (parse != NULL)
	{
		printf("entra al bucle\n");
		parse->line = split_input[i];
		parse->type_token = n_token(split_input[i], env, split_input, i);
		if (parse->type_token == -1)
			break ;
		printf("token --> %d\n", parse->type_token);
		ft_controls(parse); // AQUI SE HARAN LAS IMPLEMENTACION QUE TENGO QUE INVESTIGAR PARA ASEGURARNOS BIEN QUE NO HALLAN ERRORES.
		i++;
		if (i != 0)
		{ // si no es el primer node y existe una palabra creamos un nuevo node para reconocer que tipo de token será ese y hacerle todo el procedimiento.
			printf("agrega otro nodo\n");
			ft_lstadd_back_parse(parse); // En utils puedes ver esta funcion, es de listas pero esta adaptada.
			parse = parse->next;
		}
		else
			parse = parse->next;
	}
	parse = parse->head;
	info_to_struct_2(parse, sh, i);
	free_words(split_input);
}

void	parse_comm(t_sh *sh, char **env)
{
	t_parse	*parse;

	parse = init_parse();
	printf("reservada memoria\n");
	parse->head = parse;
	if (!sh || !sh->input)
		return;
	ft_parse(parse, sh, env);
	printf("sale del parseo\n");
	ft_lstclear_parse(parse);
}
