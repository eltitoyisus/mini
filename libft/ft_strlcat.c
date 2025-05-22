/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:55:25 by dacastil          #+#    #+#             */
/*   Updated: 2024/10/04 17:17:06 by dacastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	j_src;

	i = 0;
	j = 0;
	j_src = 0;
	while (dst[i] != '\0' && i < size)
	{
		i++;
	}
	while (src[j_src] != '\0')
	{
		j_src++;
	}
	if (size <= i)
		return (size + j_src);
	while ((i + j) < (size - 1) && src[j] != '\0')
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (i + j_src);
}
