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

static void free_words(char **words)
{
	int i;
	
	i = 0;
	if (!words)
		return;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
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

static int ft_error(char *msg, int ret)
{
	write(2, msg, ft_strlen(msg));
	return (ret);
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
	while (input_split[i])
	{
		type_token = n_token(input_split[i], env);
		info_to_struct(sh, type_token, input_split[i]);
		i++;
	}
	free_words(input_split);
}

