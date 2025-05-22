/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:53:03 by dacastil          #+#    #+#             */
/*   Updated: 2024/10/14 12:21:57 by dacastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*pr;

	i = 0;
	pr = (unsigned char *)s;
	while (i < n)
	{
		if (pr[i] == (unsigned char)c)
		{
			return (pr + i);
		}
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n);

int	main(void)
{
	const char	str[] = "Hello, world!";
	char		*result;

	// Prueba 1: Encontrar 'w'
	result = ft_memchr(str, 'w', strlen(str));
	if (result != NULL)
		printf("Caracter 'w' encontrado: %s\n", result);
	else
		printf("Caracter 'w' no encontrado.\n");

	// Prueba 2: Encontrar 'z'
	result = ft_memchr(str, 'z', strlen(str));
	if (result != NULL)
		printf("Caracter 'z' encontrado: %s\n", result);
	else
		printf("Caracter 'z' no encontrado.\n");

	// Prueba 3: Buscar más allá del tamaño de la cadena
	result = ft_memchr(str, 'o', 5);
	if (result != NULL)
		printf("Caracter 'o' dentro de los primeros 5 caracteres: %s\n", result);
	else
		printf("Caracter 'o' no encontrado en los primeros 5 caracteres.\n");

	return 0;
}
*/
