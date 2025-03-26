/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:30:28 by marvin            #+#    #+#             */
/*   Updated: 2024/11/04 11:48:30 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*s_cpy;

	if (!s || !c)
		return (NULL);
	i = 0;
	s_cpy = (char *)s;
	while (s_cpy[i])
	{
		if (s_cpy[i] == (char) c)
			return (&s_cpy[i]);
		i++;
	}
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	size_t			i;
	unsigned int	strlen;

	if (!s)
		return (NULL);
	strlen = ft_strlen(s);
	if (((strlen - start) > len) && (start < strlen))
		substr = malloc((len * sizeof(char) + 1));
	else if (start > strlen)
		substr = malloc(sizeof(char));
	else
		substr = malloc(((strlen - start) * sizeof(char) + 1));
	if (!substr)
		return (NULL);
	i = 0;
	if ((start < strlen))
	{
		while ((i < len) && s[start])
			substr[i++] = s[start++];
	}
	substr[i] = '\0';
	return (substr);
}

int	ft_putend(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		return (1);
	return (0);
}
