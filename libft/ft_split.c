/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:02:52 by dacastil          #+#    #+#             */
/*   Updated: 2025/05/28 10:43:21 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

static void	free_parcial(char **splres, int i)
{
	while (i > 0)
	{
		i--;
		free(splres[i]);
	}
	free(splres);
}

int	ft_countsubstr(const char*s, char c)
{
	int		i;
	int		countstr;
	int		flag;

	countstr = 0;
	flag = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && !flag)
		{
			countstr++;
			flag = 1;
		}
		else if (s[i] == c && flag)
		{
			flag = 0;
		}
		i++;
	}
	return (countstr);
}

static char	*next_substrs(const char **s, char delim)
{
	char		*newstr;
	const char	*start;
	size_t		lng;

	while (**s == delim)
		(*s)++;
	if (**s == '\0')
		return (NULL);
	start = *s;
	lng = 0;
	while (**s && **s != delim)
	{
		lng++;
		(*s)++;
	}
	newstr = malloc(lng + 1);
	if (!newstr)
		return (NULL);
	ft_strlcpy(newstr, start, lng + 1);
	return (newstr);
}

char	**ft_split(char const *s, char c)
{
	size_t	i_substr;
	size_t	i;
	char	**fin;

	if (!s)
		return (NULL);
	i_substr = ft_countsubstr(s, c);
	fin = malloc((i_substr + 1) * sizeof(char *));
	if (!fin)
		return (NULL);
	i = 0;
	while (i < i_substr)
	{
		fin[i] = next_substrs(&s, c);
		if (!fin[i])
		{
			free_parcial(fin, i);
			return (NULL);
		}
		i++;
	}
	fin[i] = NULL;
	return (fin);
}
/*
#include <stdio.h>

int main()
{
	char	s[] = "^^^1^^2a,^^^^3^^^^--h^^^^";
	char	d;
	char	**result;

	d = '^';
	result = ft_split(s, d);
	if (result)
	{
		for (int i = 0; result[i]; i++)
			printf("%s\n", result[i]);  // Imprimir cada subcadena
	}
	return (0);
}
*/