/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:24:19 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/03 16:01:30 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static int	other_cases(char *input, t_parse *parse)
{
	if (!ft_strncmp(input, "<", 1) || !ft_strncmp(input, ">", 1)
		|| !ft_strncmp(input, "<<", 2) || !ft_strncmp(input, ">>", 2))
		return (RED);
	else if ((!ft_strncmp(parse->prev->line, "<", 1) && can_op(input)) || !ft_strncmp(parse->prev->line, ">", 1)
		|| !ft_strncmp(parse->prev->line, ">>", 2) || !ft_strncmp(parse->prev->line, "<<", 2))
		return (FILES);
	else if (!ft_strncmp(input, "|", 1))
		return (PIPE);
	else
		return (ARG);
}

static int	cases_builds(char *input)
{
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
	else if (!ft_strncmp(input, "-", 1))
		return (FLAG);
	else
		return (CMD);
}

static int	cases_com(char *input, char **env)
{
	char	**split_com;
	char	*executable_path;

	printf("sapo\n");
	split_com = ft_split(input, ' ');
	if (!split_com)
		return (ft_error("ERROR: split failed\n", 1), ARG);
	executable_path = get_path(env, split_com[0]);
	if (!executable_path)
	{
		printf("$$$\n");
		free_words(split_com);
		return (RED);
	}
	if (access(executable_path, X_OK) == 0)
	{
		free_words(split_com);
		free(executable_path);
		return (CMD);
	}
	free(executable_path);
	free_words(split_com);
	return (RED);
}

static int	n_token(char **env, t_parse *parse)
{
	int		value_token;

	// input = cut_quotes(input);
	if (parse->line == NULL)
		return (-1);
	value_token = cases_builds(parse->line);
	if (value_token == FLAG)
		return (FLAG);
	else if (value_token == BUILT)
		return (BUILT);
	value_token = cases_com(parse->line, env);
	printf("tokennn --> %d\n", value_token);
	if (value_token == CMD)
		return (CMD);
	else if (value_token == ARG)
		return (ARG);
	value_token = other_cases(parse->line, parse);
	if (value_token == RED)
		return (RED);
	else if (value_token == PIPE)
		return (PIPE);
	else if (value_token == FILES)
		return (FILES);
	else
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

	count = parse;
	while (count != NULL)
	{
		if (count->type_token == CMD)
			count->is_cmd = true;
		else if (count->type_token == FLAG)
			count->is_flag = true;
		else if (count->type_token == ARG && count->prev->type_token == BUILT)
			count->is_built_arg = true;
		count = count->next;
	}
}

void	ft_controls(t_parse *parse)
{
	bool_active(parse);
	printf("lineaaa ---->> %s\n", parse->line);
}

// char	**cases_split(void)
// {
// 	if ()
// 	{

// 	}

// }

void	case_without_space(char *sp_input, char **env, t_parse *parse)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	printf("Aqui entra %s\n", sp_input);
	while (sp_input[i])
	{
		printf("ss\n");
		printf("(T->) %c\n", sp_input[i]);
		if (i > 0)
		{
			printf("nexxxt\n");
			ft_lstadd_back_parse(parse);
			parse = parse->next;
		}
		if ((sp_input[i] == '<' && sp_input[i + 1] == '<')
			|| (sp_input[i] == '>' && sp_input[i + 1] == '>'))
		{
			parse->line = ft_strldup(sp_input + i, 2);
			while (sp_input[i] == '<' || sp_input[i] == '>')
				i++;
		}
		else if ((sp_input[i] == '<' && sp_input[i + 1] != '<')
			|| (sp_input[i] == '>' && sp_input[i + 1] != '>'))
		{
			printf("odi\n");
			parse->line = ft_strldup(sp_input + i, 1);
			printf("yes\n");
			i++;
		}
		else if (sp_input[i] == '|')
		{
			parse->line = ft_strldup(sp_input + i, 1);
			i++;
		}
		else
		{
			printf("sales\n");
			w = i;
			while (sp_input[w] != '|' && sp_input[w] != '<'
				&& sp_input[w] != '>' && sp_input[w])
				w++;
			w -= i;
			printf("flipante %d  -- %s \n", w, (sp_input + i));
			parse->line = ft_strldup(sp_input + i, w);
			i += w;
		}
		parse->type_token = n_token(env, parse);
		printf("sale condicion parseline -> %s \n", parse->line);
	}
}

void	ft_parse(t_parse *parse, t_sh *sh, char **env)
{
	char	**split_input;
	int		i;
	int		count;
	t_parse	*temp;

	temp = parse;
	split_input = ft_split(sh->input, ' ');
	i = 0;
	count = ft_countsubstr(sh->input, ' ');
	while (parse != NULL && i < count)
	{
		printf("entra al bucle\n");
		if (space_case(split_input[i]))
			case_without_space(split_input[i], env, parse);
		else
			parse->line = split_input[i];
		ft_quotes(parse);
		printf ("ssss111 %s \n", parse->line);
		parse->type_token = n_token(env, parse);
		if (parse->type_token == -1)
			break ;
		printf("token --> %d\n", parse->type_token);
		ft_controls(parse); // AQUI SE HARAN LAS IMPLEMENTACION QUE TENGO QUE INVESTIGAR PARA ASEGURARNOS BIEN QUE NO HALLAN ERRORES.
		i++;
		if (i != 0 && i < count)
		{ // si no es el primer node y existe una palabra creamos un nuevo node para reconocer que tipo de token será ese y hacerle todo el procedimiento.
			printf("agrega otro nodo\n");
			ft_lstadd_back_parse(parse); // En utils puedes ver esta funcion, es de listas pero esta adaptada.
			parse = parse->next;
		}
	}
	// printf ("ssss %s \n", parse->prev->line);
	parse = temp;
	for (int j = 0; parse != NULL; j++)
	{
		printf("COMPLETO :		%s  TYPE: %d \n", parse->line, parse->type_token);
		parse = parse->next;
	}
	parse = temp;
	printf ("ssss %s \n", parse->line);
	info_to_struct_2(parse, sh, i);
	free_words(split_input);
}

void	parse_comm(t_sh *sh, char **env)
{
	t_parse	*parse;

	parse = init_parse();
	printf("reservada memoria\n");
	if (!sh || !sh->input)
		return ;
	ft_parse(parse, sh, env);
	printf("sale del parseo\n");
	ft_lstclear_parse(parse);
}
