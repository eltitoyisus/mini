/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:57:55 by jramos-a          #+#    #+#             */
/*   Updated: 2025/05/02 12:37:09 by jramos-a         ###   ########.fr       */
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
