/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_min.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:20:48 by dacastil          #+#    #+#             */
/*   Updated: 2025/06/20 14:15:17 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static char	*remove_surrounding_quotes(char *input, int len)
{
	char	*result;

	if (len >= 2)
	{
		if (input[0] == '\'' && input[len - 1] == '\'')
		{
			result = malloc(len + 1);
			if (!result)
				return (NULL);
			ft_memcpy(result + 1, input + 1, len - 2);
			result[0] = '\001';
			result[len - 2 + 1] = '\002';
			result[len] = '\0';
			return (result);
		}
		else if (input[0] == '\"' && input[len - 1] == '\"')
		{
			result = ft_substr(input, 1, len - 2);
			return (result);
		}
	}
	return (NULL);
}

static char	*concatenate_parts(char *before, char *middle, char *after)
{
	char	*temp1;
	char	*result;

	temp1 = ft_strjoin(before, middle);
	result = ft_strjoin(temp1, after);
	free(before);
	free(middle);
	free(after);
	free(temp1);
	return (result);
}

static char	*create_quote_parts(char *input, int i, int j)
{
	char	*before;
	char	*middle;
	char	*after;

	before = ft_substr(input, 0, i);
	middle = ft_substr(input, i + 1, j - i - 1);
	after = ft_strdup(input + j + 1);
	return (concatenate_parts(before, middle, after));
}

static char	*process_inner_quotes(char *input)
{
	int		i;
	int		j;
	char	quote_type;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			quote_type = input[i];
			j = i + 1;
			while (input[j] && input[j] != quote_type)
				j++;
			if (input[j] == quote_type)
				return (create_quote_parts(input, i, j));
		}
		i++;
	}
	return (NULL);
}

char	*cut_quotes(char *input)
{
	char	*result;
	char	*temp;
	int		are_equal;

	if (!input)
		return (NULL);
	result = remove_surrounding_quotes(input, ft_strlen(input));
	if (!result)
	{
		result = process_inner_quotes(input);
		if (!result)
			return (ft_strdup(input));
	}
	while (ft_strchr(result, '\'') || ft_strchr(result, '\"'))
	{
		temp = result;
		result = cut_quotes(result);
		are_equal = (ft_strncmp(temp, result, ft_strlen(temp) + 1) == 0);
		free(temp);
		if (are_equal)
			break ;
	}
	return (result);
}
