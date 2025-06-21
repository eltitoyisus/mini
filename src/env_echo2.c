/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_echo2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:20:29 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/19 18:20:29 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	check_quotes_type(char *input, int len, int *is_single_quoted,
		int *is_double_quoted)
{
	if (!input)
		return (0);
	*is_single_quoted = (len >= 2 && input[0] == '\'' && input[len
			- 1] == '\'');
	*is_double_quoted = (len >= 2 && input[0] == '\"' && input[len
			- 1] == '\"');
	return (1);
}

char	*init_quotes_result(int len)
{
	char	*result;

	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	return (result);
}

void	handle_quote_char(char *input, int *i, int *in_quotes, char *quote_type)
{
	if ((input[*i] == '\'' || input[*i] == '\"') && !(*in_quotes))
	{
		*in_quotes = 1;
		*quote_type = input[*i];
		(*i)++;
	}
	else if (*in_quotes && input[*i] == *quote_type)
	{
		*in_quotes = 0;
		(*i)++;
	}
}

void	handle_dollar_in_single_quotes(char *input, char *result, int *i,
		int *j)
{
	if (input[*i] == '$')
		result[(*j)++] = '\001';
}

char	*process_quotes_loop(char *result, char *input, int is_single_quoted)
{
	int		i;
	int		j;
	int		in_quotes;
	char	quote_type;

	i = 0;
	j = 0;
	in_quotes = 0;
	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '\"') && !in_quotes)
			handle_quote_char(input, &i, &in_quotes, &quote_type);
		else if (in_quotes && input[i] == quote_type)
			handle_quote_char(input, &i, &in_quotes, &quote_type);
		else
		{
			if (is_single_quoted)
				handle_dollar_in_single_quotes(input, result, &i, &j);
			copy_char_to_result(input, result, &i, &j);
		}
	}
	result[j] = '\0';
	return (result);
}
