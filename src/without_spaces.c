/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   without_spaces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:08:57 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/03 15:35:54 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	space_case(char	*input)
{
	int	i;

	i = 0;
	if ((ft_strchr(input, '>') && ft_strchr(input, '<'))
		|| (ft_strchr(input, '>') && ft_strchr(input, '|'))
		|| (ft_strchr(input, '<') && ft_strchr(input, '|')))
		return (1);
	if (ft_strchr(input, '>') && ft_strchr(input, '>')[i + 1])
	{
		if (ft_strchr(input, '>')[i + 1] == '>' && ft_strchr(input, '>')[i + 2] != '>')
			return (1);
		if (ft_strchr(input, '>')[i + 1] != '>')
			return (1);
	}
	if (ft_strchr(input, '<') && ft_strchr(input, '<')[i + 1])
	{
		if (ft_strchr(input, '<')[i + 1] == '<' && ft_strchr(input, '<')[i + 2] != '<')
			return (1);
		if (ft_strchr(input, '<')[i + 1] != '<')
			return (1);
	}
	if ((ft_strchr(input, '|')[i + 1] != '<' || ft_strchr(input, '|')[i + 1] != '>'
		|| ft_strchr(input, '|')[i + 1] != '|') && ft_strchr(input, '|'))
		return (1);
	return (0);
}
