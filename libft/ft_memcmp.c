/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:10:11 by dacastil          #+#    #+#             */
/*   Updated: 2024/10/02 21:20:42 by dacastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*pr1;
	unsigned char	*pr2;

	pr1 = (unsigned char *)s1;
	pr2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (pr1[i] != pr2[i])
		{
			return (pr1[i] - pr2[i]);
		}
		i++;
	}
	return (0);
}
