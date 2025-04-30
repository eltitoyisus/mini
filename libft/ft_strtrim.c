/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:29:24 by dacastil          #+#    #+#             */
/*   Updated: 2024/10/14 12:27:35 by dacastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

static int	check_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static char	*mi_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strtrim(const char *s1, char const *set)
{
	size_t	inc;
	size_t	fin;
	size_t	lngnew;
	char	*newstr;

	if (!s1 || !set)
		return (NULL);
	inc = 0;
	fin = ft_strlen(s1);
	while (s1[inc] && check_set(s1[inc], set))
	{
		inc++;
	}
	while (fin > inc && check_set(s1[fin - 1], set))
	{
		fin--;
	}
	lngnew = fin - inc;
	newstr = (char *)malloc(lngnew + 1);
	if (!newstr)
		return (NULL);
	mi_strncpy(newstr, (s1 + inc), lngnew);
	newstr[lngnew] = '\0';
	return (newstr);
}
