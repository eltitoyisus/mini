/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:05:23 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/21 18:05:23 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static int	handle_operator(const char *input, char *result, int i, int *j)
{
	if (i > 0 && result[*j - 1] != ' ')
		result[(*j)++] = ' ';
	result[(*j)++] = input[i];
	if ((input[i] == '>' && input[i + 1] == '>') || (input[i] == '<' && input[i
				+ 1] == '<'))
		result[(*j)++] = input[++i];
	if (input[i + 1] && input[i + 1] != ' ')
		result[(*j)++] = ' ';
	return (i);
}

char	*insert_spaces_around_operators(const char *input)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = malloc(ft_strlen(input) * 3 + 1);
	if (!result)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '>' || input[i] == '<' || input[i] == '|')
			i = handle_operator(input, result, i, &j);
		else
			result[j++] = input[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}
