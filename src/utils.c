/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:53:26 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/05/01 16:33:07 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int ft_error(char *msg, int ret)
{
	write(2, msg, ft_strlen(msg));
	return (ret);
}

void free_words(char **words)
{
	int i;

	i = 0;
	if (!words)
		return;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
}



// DESPUÉS IMPLEMENTARÉ ESTO QUE SERA NECESARIO DESPUÉS, AÚN NO.
