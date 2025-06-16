/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:44:46 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/16 17:13:13 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	check_quotes_validity(t_parse *parse)
{
	if ((check_open(parse, SIMPLE) == 0) || (check_open(parse, DOUBLE) == 0))
	{
		printf("Unmatched quotes found\n");
		parse->quote_error = 1;
		return (0);
	}
	if ((ft_strchr(parse->line, '\"') && ft_strchr(parse->line,
				'\"') == ft_strrchr(parse->line, '\"'))
		|| (ft_strchr(parse->line, '\'') && ft_strchr(parse->line,
				'\'') == ft_strrchr(parse->line, '\'')))
	{
		printf("Unmatched quotes found\n");
		parse->quote_error = 1;
		return (0);
	}
	return (1);
}

int	process_quotes(t_parse *parse, int case_q)
{
	int	ch_op;
	int	flag;

	flag = 0;
	if (case_q == SIMPLE)
	{
		ch_op = check_open(parse, SIMPLE);
		flag = case_simple(parse);
	}
	else if (case_q == DOUBLE)
	{
		ch_op = check_open(parse, DOUBLE);
		flag = case_double(parse);
	}
	else
		return (0);
	return (ch_op != 0 || flag != 0);
}

void	ft_quotes(t_parse *parse)
{
	int	case_q;
	int	continue_processing;

	if (!check_quotes_validity(parse))
		return ;
	while (ft_strchr(parse->line, '\'') || ft_strchr(parse->line, '\"'))
	{
		case_q = id_cases(parse);
		printf("sabes case of quotes --> %d\n", case_q);
		if (!check_quotes_validity(parse))
			return ;
		continue_processing = process_quotes(parse, case_q);
		if (!continue_processing)
			break ;
	}
}
