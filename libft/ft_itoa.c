/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:05:07 by dacastil          #+#    #+#             */
/*   Updated: 2024/10/14 12:27:01 by dacastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

//hacer funcion para long del int!!

static int	lngnmb(int n)
{
	int	i_nmb;

	i_nmb = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i_nmb++;
	while (n != 0)
	{
		n = (n / 10);
		i_nmb++;
	}
	return (i_nmb);
}

char	*ft_itoa(int n)
{
	int				i_nmb;
	char			*cad;
	unsigned int	num;

	i_nmb = lngnmb (n);
	if (n < 0)
		num = -n;
	else
		num = n;
	cad = (char *)malloc(i_nmb + 1);
	if (!cad)
		return (NULL);
	cad[i_nmb] = '\0';
	while (0 < i_nmb)
	{
		cad[i_nmb - 1] = (num % 10) + ('0');
		num = num / 10;
		i_nmb--;
	}
	if (n < 0)
		cad[0] = '-';
	return (cad);
}
