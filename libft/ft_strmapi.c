/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:33:12 by dacastil          #+#    #+#             */
/*   Updated: 2024/10/04 20:14:16 by dacastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned
int, char))
{
	int		lng;
	int		i;
	char	*result;

	if (!s || !f)
		return (NULL);
	lng = ft_strlen(s);
	i = 0;
	result = malloc(lng + 1);
	if (!result)
		return (NULL);
	while (s[i] != '\0')
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
