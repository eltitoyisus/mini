/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:24:19 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/05/08 16:13:31 by daniel-cast      ###   ########.fr       */
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

	// parse_cmd(char);
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

static int n_token(char *input, char **env, char **input_split, int i)
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

void info_to_struct(t_sh *sh, int type_token, char **input_s, int i)
{
	if (!sh || !sh->node || !input_s)
		return;
	type_cmd_built(sh, type_token, input_s, i);
	type_red_pipe(sh, type_token, input_s, i);
	if (type_token == ARG)
	{
		sh->node->arg = ft_strdup(input_s[i]);
	}
	// Siempre que metamos la info del node que estemos creamos otro
	ft_lstadd_back_sh(sh);
}

void parse_comm(t_sh *sh, char **env)
{
	int		type_token;
	char	**input_split;
	int		i;

	if (!sh || !sh->input)
		return;
	i = 0;
	input_split = ft_split(sh->input, ' ');
	if (!input_split)
		return;
	while (input_split[++i])
	{
		if (i != 0)
		{ // si no es el primer node y existe una palabra creamos un nuevo node para reconocer que tipo de token será ese y hacerle todo el procedimiento.
			ft_lstadd_back_sh(sh); // En utils puedes ver esta funcion, es de listas pero esta adaptada.
			sh->node = sh->node->next;
		}
			// input_split[i] = case_flag(sh, input_split, i, type_token);
			type_token = n_token(input_split[i], env, input_split, i);
		info_to_struct(sh, type_token, input_split, i);
	}
	ft_lstclear_sh(sh);
	free_words(input_split);
}
