/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:46:06 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/16 17:15:30 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	other_cases(char *input, char **input_split, int i)
{
	if (!ft_strncmp(input, "<", 1) || !ft_strncmp(input, ">", 1)
		|| !ft_strncmp(input, "<<", 2) || !ft_strncmp(input, ">>", 2))
		return (RED);
	else if ((!ft_strncmp(input_split[i - 1], "<", 1) && can_op(input))
		|| !ft_strncmp(input_split[i - 1], ">", 1) || !ft_strncmp(input_split[i
				- 1], ">>", 2) || !ft_strncmp(input_split[i - 1], "<<", 2))
		return (FILES);
	else if (!ft_strncmp(input, "|", 1))
		return (PIPE);
	else
		return (ARG);
}

int	cases_builds(char *input)
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

int	cases_com(char *input, char **env)
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
	return (RED);
}

int	n_token(char *input, char **env, char **input_split, int i)
{
	int	value_token;

	if (input == NULL)
		return (-1);
	value_token = cases_builds(input);
	if (value_token == FLAG)
		return (FLAG);
	else if (value_token == BUILT)
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
	else
		return (ARG);
}

char	**save_tokens(t_parse *parse, int *token_count)
{
	char	**saved_tokens;
	t_parse	*temp;
	int		j;

	saved_tokens = malloc(sizeof(char *) * 500);
	if (!saved_tokens)
		return (NULL);
	*token_count = 0;
	temp = parse;
	j = 0;
	while (temp)
	{
		saved_tokens[*token_count] = ft_strdup(temp->line);
		if (!saved_tokens[*token_count])
		{
			while (j < *token_count)
				free(saved_tokens[j++]);
			free(saved_tokens);
			return (NULL);
		}
		(*token_count)++;
		temp = temp->next;
	}
	saved_tokens[*token_count] = NULL;
	return (saved_tokens);
}
