/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   without_spaces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:08:57 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/04 14:24:01 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	check_double_redir(char *input, int i)
{
	if ((input[i] == '<' && input[i + 1] == '<') || (input[i] == '>' && input[i
				+ 1] == '>'))
	{
		if (input[i + 2] && input[i + 2] != ' ')
			return (1);
		return (2);
	}
	return (0);
}

int	space_case(char *input)
{
	int	i;
	int	skip;

	if (!input)
		return (0);
	i = 0;
	while (input[i])
	{
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		{
			if (i > 0 && input[i - 1] != ' ')
				return (1);
			if (input[i + 1] && input[i + 1] != ' ' && !((input[i] == '<'
						&& input[i + 1] == '<') || (input[i] == '>' && input[i
							+ 1] == '>')))
				return (1);
			skip = check_double_redir(input, i);
			if (skip == 1)
				return (1);
			if (skip == 2)
				i++;
		}
		i++;
	}
	return (0);
}
