/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:00:22 by marvin            #+#    #+#             */
/*   Updated: 2024/10/21 10:05:04 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*len_s1;
	const unsigned char	*len_s2;
	size_t				i;

	len_s1 = (const unsigned char *)s1;
	len_s2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (len_s1[i] != len_s2[i])
			return (len_s1[i] - len_s2[i]);
		i++;
	}
	return (0);
}
