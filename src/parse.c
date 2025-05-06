/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:24:19 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/05/02 15:06:05 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

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

static int cases_builds(char *input)
{
	char **split_in;
	int result;

	split_in = ft_split(input, ' ');
	if (!split_in)
		return (ARG);
	if (!ft_strncmp(split_in[0], "pwd", 4))
		result = BUILT;
	else if (!ft_strncmp(split_in[0], "cd", 3))
		result = BUILT;
	else if (!ft_strncmp(split_in[0], "echo", 4))
		result = BUILT;
	else if (!ft_strncmp(split_in[0], "export", 6))
		result = BUILT;
	else if (!ft_strncmp(split_in[0], "unset", 5))
		result = BUILT;
	else if (!ft_strncmp(split_in[0], "env", 3))
		result = BUILT;
	else if (!ft_strncmp(split_in[0], "exit", 5))
	{
		printf("exit\n");
		free_words(split_in);
		exit(127);
	}
	else
		result = CMD;
	free_words(split_in);
	return (result);
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

static int n_token(char *input, char **env)
{
	int	value_token;

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
	return (ARG);
}

void info_to_struct(t_sh *sh, int type_token, char *token_str)
{
	if (!sh || !sh->node || !token_str)
		return;
	if (type_token == BUILT)
	{
		if (sh->node->built->name)
			free(sh->node->built->name);
		sh->node->built->name = ft_strdup(token_str);
	}
	else if (type_token == CMD)
	{
		if (sh->node->cmd->cmd)
			free(sh->node->cmd->cmd);
		sh->node->cmd->cmd = ft_strdup(token_str);
	}
	else if (type_token == RED)
	{
		if (sh->node->red->type)
			free(sh->node->red->type);
		sh->node->red->type = ft_strdup(token_str);
	}
	else if (type_token == PIPE)
		sh->node->w_pipe->pipe_count += 1;
	else if (type_token == ARG)
	{
		if (sh->node->arg)
			free(sh->node->arg);
		sh->node->arg = ft_strdup(token_str);
	}
	// Siempre que metamos la info del node que estemos creamos otro
	ft_lstadd_back_sh(sh);
}

void parse_comm(t_sh *sh, char **env)
{
	int		type_token;
	char	**input_split;
	int		i;
	t_node	*temp;

	if (!sh || !sh->input)
		return;
	i = 0;
	temp = sh->node;
	input_split = ft_split(sh->input, ' ');
	if (!input_split)
		return;
	while (input_split[i])
	{
		if (i != 0)
		{ // si no es el primer node y existe una palabra creamos un nuevo node para reconocer que tipo de token será ese y hacerle todo el procedimiento.
			ft_lstadd_back_sh(sh); // En utils puedes ver esta funcion, es de listas pero esta adaptada.
			sh->node = sh->node->next;
		}
			type_token = n_token(input_split[i], env);
		info_to_struct(sh, type_token, input_split[i]);
		i++;
	}
	ft_lstclear_sh(sh, temp);
	sh->node = node_factory();
	free_words(input_split);
}
