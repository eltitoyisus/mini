/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:18:01 by dacastil          #+#    #+#             */
/*   Updated: 2024/09/27 18:07:02 by dacastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <stdio.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	totalsz;
	void	*pr;

	totalsz = (nmemb * size);
	pr = malloc(totalsz);
	if (pr == NULL)
	{
		return (NULL);
	}
	ft_bzero(pr, totalsz);
	return (pr);
}

/*int main() {
    // Usamos ft_calloc para asignar memoria para un array de 5 enteros
    int *array = (int *)ft_calloc(5, sizeof(int));

    // Verificamos si ft_calloc devolvió
	NULL, lo que indicaría un error de asignación
    if (array == NULL) {
        printf("Error al asignar memoria.\n");
        return 1;
    }

    // Imprimimos los valores del array para comprobar que
	están inicializados a cero
    for (int i = 0; i < 5; i++) {
        printf("array[%d] = %d\n", i, array[i]);
    }

    // Liberamos la memoria asignada para evitar fugas de memoria
    free(array);

    return 0;
} */
