/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:17:23 by dacastil          #+#    #+#             */
/*   Updated: 2024/10/04 20:00:42 by dacastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	lenght;
	size_t	i;
	char	*dup;

	lenght = ft_strlen(s);
	dup = (char *)malloc(lenght + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < lenght)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
