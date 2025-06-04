/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 22:21:04 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/04 22:46:51 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	is_built(t_parse *parse)
{
	t_parse	*to_back;

	printf("jelou\n");
	to_back = parse;
	while (to_back != NULL)
	{
		if (to_back->type_token == BUILT)
			return (printf("ES BUILT\n"), 1);
		to_back = to_back->prev;
	}
	return (0);
}

char	**ft_built_args(t_parse *parse, char **built_args)
{
	char	**new;
	t_parse	*to_back;
	int		i;

	to_back = parse;
	i = 0;
	while (to_back != NULL)
	{
		to_back = to_back->prev;
		i++;
	}
	printf("odi  -> %d\n", i);
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		printf("sabes\n");
	i = 0;
	if (!built_args)
	{
		printf("you know\n");
		new[i] = ft_strdup(parse->line);
		i++;
		new[i] = NULL;
		return (printf("retorna\n"), new);
	}
	while (built_args[i])
	{
		new[i] = ft_strdup(built_args[i]);
		i++;
	}
	new[i] = ft_strdup(parse->line);
	i++;
	new[i] = NULL;
	printf("todo melocoton\n");
	free_words(built_args);
	return (new);
}
