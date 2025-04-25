/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 08:19:30 by marvin            #+#    #+#             */
/*   Updated: 2024/10/23 09:46:14 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*s_cpy;

	s_cpy = (char *)s;
	while (*s_cpy)
	{
		if (*s_cpy == (char)c)
			return (s_cpy);
		s_cpy++;
	}
	if ((char)c == '\0')
		return (s_cpy);
	return (NULL);
}
