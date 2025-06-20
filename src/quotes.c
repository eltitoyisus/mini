/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:49:21 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/05/27 19:46:00 by dacastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	case_simple(t_parse *parse)
{
	int	i;
	int	j;

	i = 0;
	if (!ft_strchr(parse->line, '\''))
		return (0);
	while (parse->line[i] && parse->line[i] == '\'')
	{
		if (parse->line[i] == '\"')
			break ;
		i++;
	}
	j = 0;
	while (ft_strchr(parse->line, '\'') && j < i)
	{
		if (ft_strrchr(parse->line, '\'') != ft_strchr(parse->line, '\''))
			parse->line = ft_strtrim(parse->line, "'");
		if (ft_strchr(parse->line, '\'') && (ft_strchr(parse->line,
					'\'') == ft_strrchr(parse->line, '\'')))
			if (ft_strrchr(parse->line, '\"') != ft_strchr(parse->line, '\"'))
				return (0);
		j++;
	}
	return (1);
}

int	case_double(t_parse *parse)
{
	if (!ft_strchr(parse->line, '\"'))
		return (0);
	if (ft_strchr(parse->line, '\"') && ft_strrchr(parse->line,
			'\"') != ft_strchr(parse->line, '\"'))
	{
		parse->line = ft_strtrim(parse->line, "\"");
		if (ft_strrchr(parse->line, '\'') != ft_strchr(parse->line, '\''))
			return (0);
	}
	return (1);
}

int	check_open(t_parse *parse, int type)
{
	int		i;
	int		count;
	char	quote_char;

	i = 0;
	count = 0;
	if (type == SIMPLE)
		quote_char = '\'';
	else
		quote_char = '\"';
	while (parse->line[i])
	{
		if (parse->line[i] == quote_char)
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (1);
	else
		return (0);
}

int	id_cases(t_parse *parse)
{
	if (ft_strchr(parse->line, '\'') && ft_strchr(parse->line, '\"'))
	{
		if (ft_strlen(ft_strchr(parse->line,
					'\'')) > ft_strlen(ft_strchr(parse->line, '\"')))
			return (SIMPLE);
		else if (ft_strlen(ft_strchr(parse->line,
					'\'')) < ft_strlen(ft_strchr(parse->line, '\"')))
			return (DOUBLE);
		else
			return (ERROR);
	}
	else if (ft_strchr(parse->line, '\''))
		return (SIMPLE);
	else if (ft_strchr(parse->line, '\"'))
		return (DOUBLE);
	else
		return (ERROR);
}
