/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 22:21:04 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/05/31 22:41:40 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	is_built(t_parse *parse)
{
	t_parse	*to_back;

	to_back = parse;
	while (to_back != NULL)
	{
		if (to_back->type_token == BUILT)
			return (1);
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
	while (to_back != NULL)
		i++;
	new = malloc(sizeof(char *) * i);
	i = 0;
	while (built_args[i])
	{
		new[i] = built_args[i];
		i++;
	}
	new[i] = parse->line;
	i++;
	new[i] = NULL;
	free_words(built_args);
	return (new);
}
