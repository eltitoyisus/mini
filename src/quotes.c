/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:49:21 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/05/20 19:09:13 by daniel-cast      ###   ########.fr       */
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

int	check_open(t_parse *parse)
{ // Esto indica si esta abierto o cerrado las comillas
	int	i;

	i = 0;
	while (parse->line[i])
	{
		if (parse->line[i] == '\'')
		{
			i++;
			if (parse->line[i] == '\'')
				 return (1);
		}
		else if (parse->line[i] == '\"')
		{
			i++;
			if (parse->line[i] == '\"')
				return (1);
		}
		else
			i++;
	}
	return (0);
}
int	id_cases(t_parse *parse)
{
	if (ft_strchr(parse->line, '\'') && ft_strchr(parse->line, '\"'))
	{
		if (ft_strlen(ft_strchr(parse->line, '\'')) > ft_strlen(ft_strchr(parse->line, '\"')))
			return (SIMPLE);
		else if (ft_strlen(ft_strchr(parse->line, '\'')) < ft_strlen(ft_strchr(parse->line, '\"')))
			return (DOUBLE);
	}
}

void	ft_quotes(t_parse *parse)
{
	int	ch_op;
	int	case_q;
	int	flag; // Esta flag lo que va a hacer es representar si se realizo bien el recorte de comillas, sean simples o dobles.

	flag = 0;
	ch_op = check_open(parse);
	while(ft_strchr(parse->line, '\'') || ft_strchr(parse->line, '\"'))
	{
		case_q = id_cases(parse);
		if ((ft_strchr(parse->line, '\"') && ft_strchr(parse->line, '\"') == ft_strrchr(parse->line, '\"')) || (ft_strchr(parse->line, '\'') && ft_strchr(parse->line, '\'') == ft_strrchr(parse->line, '\'')))
			ft_error("sabes sale \n", 1);
		printf("bucle infinito\n"); // Aqui estoy comparando longitudes de los punteros que devuelven quiere decir cual caracter esta mas cerca del inicio
		if (case_q == SIMPLE)
			flag = case_simple(parse);
		else if (case_q == DOUBLE)
			flag = case_double(parse);
		if (flag == 1 || flag == 0)
			break ;
		// else if (flag == 1)
		// 	break ;
	}
}
