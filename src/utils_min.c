/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_min.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:20:48 by dacastil          #+#    #+#             */
/*   Updated: 2025/06/04 14:18:35 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char	*cut_quotes(char	*input)
{
	int	i;

	i = 0;
	while (input[i] == '\'' || input[i] == '\"' || input[i] == i)
		i++;
	if (i > 0)
		return (input + i);
	else
		return (input);
}

void	has_more_reds(t_parse *parse, t_reds *red)
{
	t_parse	*temp;
	int		i;

	temp = parse;
	i = 0;
	while (temp != NULL)
	{
		if (i != 0)
		{
			if (temp->type_token == RED || temp->type_token == FILES
			|| temp->type_token == PIPE)
			{
				ft_lstadd_back_red(red);
				red = red->next;
				return ;
			}
		}
		i++;
	}
}
