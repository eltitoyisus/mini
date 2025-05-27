/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_min.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:20:48 by dacastil          #+#    #+#             */
/*   Updated: 2025/05/27 19:38:20 by dacastil         ###   ########.fr       */
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
