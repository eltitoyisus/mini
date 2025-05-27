/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:49:21 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/05/27 11:44:52 by dacastil         ###   ########.fr       */
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
		// if (ft_strlen(ft_strchr(parse->line, '\'')) > ft_strlen(ft_strchr(parse->line, '\"')))
		if (ft_strrchr(parse->line, '\'') != ft_strchr(parse->line, '\''))
			parse->line = ft_strtrim(parse->line, "'");
		if (ft_strchr(parse->line, '\'') && (ft_strchr(parse->line, '\'') == ft_strrchr(parse->line, '\'')))
			ft_error("sabes sale \n", 1);
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
	printf("entra\n");
	if (ft_strchr(parse->line, '\"') && ft_strrchr(parse->line, '\"') != ft_strchr(parse->line, '\"'))
	{
		// if (ft_strlen(ft_strchr(parse->line, '\'')) < ft_strlen(ft_strchr(parse->line, '\"')))
		parse->line = ft_strtrim(parse->line, "\"");
		if (ft_strrchr(parse->line, '\'') != ft_strchr(parse->line, '\''))
			return (0);
	}
	return (1);
}
//														|
// Esto indica si esta abierto o cerrado las comillas 	v

int	check_open(t_parse *parse, int type)
{
	int	i;
	int	flag;

	i = 0;
	flag = -1;
	if (type == SIMPLE)
	{
		while (parse->line[i] == '\'')
		{
			flag = 0;
			i++;
			if (parse->line[i++] == '\'')
				flag = 1;
		}
	}
	else if (type == DOUBLE)
	{
		while (parse->line[i] == '\"')
		{
			flag = 0;
			i++;
			if (parse->line[i++] == '\"')
				flag = 1;
		}
	}
	return (flag);
}

int	id_cases(t_parse *parse)
{
	if (ft_strchr(parse->line, '\'') && ft_strchr(parse->line, '\"'))
	{
		if (ft_strlen(ft_strchr(parse->line, '\'')) > ft_strlen(ft_strchr(parse->line, '\"')))
			return (SIMPLE);
		else if (ft_strlen(ft_strchr(parse->line, '\'')) < ft_strlen(ft_strchr(parse->line, '\"')))
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

void	ft_quotes(t_parse *parse)
{
	int	ch_op;
	int	case_q;
	int	flag; // Esta flag lo que va a hacer es representar si se realizo bien el recorte de comillas, sean simples o dobles.

	flag = 0;
	while(ft_strchr(parse->line, '\'') || ft_strchr(parse->line, '\"'))
	{
		case_q = id_cases(parse);
		printf("sabes case of quotes --> %d\n", case_q);
		if ((ft_strchr(parse->line, '\"') && ft_strchr(parse->line, '\"') == ft_strrchr(parse->line, '\"')) || (ft_strchr(parse->line, '\'') && ft_strchr(parse->line, '\'') == ft_strrchr(parse->line, '\'')))
			ft_error("sabes sale \n", 1);
		printf("bucle infinito\n"); // Aqui estoy comparando longitudes de los punteros que devuelven quiere decir cual caracter esta mas cerca del inicio
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
		if (ch_op == 0 && flag == 0)
			break ;
	}
}

