/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 07:55:53 by marvin            #+#    #+#             */
/*   Updated: 2024/10/23 09:09:27 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	result;
	size_t	i;
	size_t	j;
	size_t	d_len;
	size_t	s_len;

	j = 0;
	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	i = d_len;
	if (d_len >= size)
		return (s_len + size);
	while (src[j] && i < size - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if (i < size)
		dst[i] = '\0';
	result = d_len + s_len;
	return (result);
}
