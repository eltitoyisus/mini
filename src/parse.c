/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:24:19 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/04/30 16:05:51 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static int	cases_builds(char *input)
{
	char	**split_in;

	split_in = ft_split(input, ' ');
	if (!ft_strncmp(split_in[0], "pwd", 4))
		return (fr_words(split_in), BUILT);
	else if (!ft_strncmp(split_in[0], "cd", 3))
		return (fr_words(split_in), BUILT);
	else if (!ft_strncmp(split_in[0], "echo", 4))
		return (fr_words(split_in), BUILT);
	else if (!ft_strncmp(split_in[0], "export", 6))
		return (fr_words(split_in), BUILT);
	else if (!ft_strncmp(split_in[0], "unset", 5))
		return (fr_words(split_in), BUILT);
	else if (!ft_strncmp(split_in[0], "env", 3))
		return (fr_words(split_in), BUILT);
	else if (!ft_strncmp(split_in[0], "exit", 5))
	{
		printf("exit\n");
		return (fr_words(split_in), exit(127), 0);
	}
	else
		return (CMD);
}

static int	cases_com(char *input, char **env)
{
	char	**split_com;
	char	**path;
	char	*line_p;
	int		i;

	path = ft_findpath(env);
	split_com = ft_split(input, ' ');
	i = 0;
	while (path[i])
	{
		line_p = creat_path(path[i], split_com[0]);
		if (!line_p)
			return (fr_words(path), fr_words(split_com),
				ft_error("ERROR: path\n", 1), ARG);
		if (access(line_p, X_OK) == 0)
			return (fr_words(path), fr_words(split_com), free(line_p), COM);
		free(line_p);
		i++;
	}
	fr_words(path);
	fr_words(split_com);
	return (ARG);
}

static int	other_cases(char *input)
{
	if (!ft_strncmp(input, "<", 1) || !ft_strncmp(input, ">", 1)
		|| !ft_strncmp(input, "<<", 1) || !ft_strncmp(input, ">>", 1))
		return (RED);
	else if (!ft_strncmp(input, "|", 1))
		return (PIPE);
	else
		return (ARG);
}

static int	n_token(char *input, char **env)
{
	int		value_token;

	value_token = cases_builds(input);
	if (value_token == BUILT)
		return (BUILT);
	value_token = cases_com(input, env);
	if (value_token == CMD)
		return (CMD);
	else if (value_token == ARG)
		return (ARG);
	value_token = other_cases(input);
	if (value_token == RED)
		return (RED);
	else if (value_token == PIPE)
		return (PIPE);
	else if (value_token == ARG)
		return (ARG);
}

void	info_to_struct(t_sh *sh, int type_token)
{
	if (type_token == BUILT)


}

void	parse_comm(t_sh *sh, char **env)
{
	int		type_token; // este va a ser el indicador de el token actual
	char	**input_split; // Spliteo el input para poder asignarle cada uno de las palabras su token correspondiente de cada palabra
	t_node	*temp;
	int		i;


	temp = sh->node;
	i = 0;
	input_split = ft_split(sh->input, ' ');
	while (input_split[i])
	{
		type_token = n_token(input_split[i], env); // Aqui recorro uno a uno identificando el tipo de token que sea la palabra.
		info_to_struct(sh->node, type_token); // Aqui como ya recorronoci ese tipo de token lo que hago es meterlo al nodo correspondiente y dentro a su estructura.


	}



}
