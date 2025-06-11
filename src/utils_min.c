/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_min.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:20:48 by dacastil          #+#    #+#             */
/*   Updated: 2025/06/11 11:12:04 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static char	*remove_surrounding_quotes(char *input, int len)
{
	char	*result;

	if (len >= 2 && ((input[0] == '\'' && input[len - 1] == '\'')
			|| (input[0] == '\"' && input[len - 1] == '\"')))
	{
		result = ft_substr(input, 1, len - 2);
		return (result);
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
	int		len;
	char	*result;

	if (!input)
		return (NULL);
	len = ft_strlen(input);
	result = remove_surrounding_quotes(input, len);
	if (result)
		return (result);
	result = process_inner_quotes(input);
	if (result)
		return (result);
	return (ft_strdup(input));
}
