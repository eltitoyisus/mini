/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:53:18 by dacastil          #+#    #+#             */
/*   Updated: 2024/10/03 21:13:34 by dacastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dst;
	unsigned char	*sr;

	if (!dest && !src)
		return (NULL);
	i = 0;
	dst = (unsigned char *)dest;
	sr = (unsigned char *)src;
	while (i < n)
	{
		dst[i] = sr[i];
		i++;
	}
	return (dest);
}
/*
int main(void)
{

	const char src[] = "me voy mi vida";
		 char dest[] = "hola vida";
	size_t n = 9;

	printf("funcion original: %s\n", (char*)memcpy(dest, src, n));
	printf("funcion mia     : %s\n", (char*)ft_memcpy(dest, src, n));

	return (0);
}*/
