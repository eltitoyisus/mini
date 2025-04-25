/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 10:55:24 by marvin            #+#    #+#             */
/*   Updated: 2024/10/23 09:20:33 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_counter(const char *s, char c)
{
	int		word;

	word = 0;
	if (!s)
		return (0);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			word++;
			while (*s && *s != c)
				s++;
		}
	}
	return (word);
}

static void	ft_free(char **a)
{
	int	i;

	i = 0;
	if (!a)
		return ;
	while (a[i])
	{
		free(a[i]);
		i++;
	}
	free(a);
}

static char	*ft_read_word(char *s, char c, int *index)
{
	int		start;
	int		end;
	char	*word;
	int		len;

	while (s[*index] == c)
		(*index)++;
	start = *index;
	while (s[*index] && s[*index] != c)
		(*index)++;
	end = *index;
	len = end - start;
	if (start < end)
	{
		word = (char *)malloc((len + 1) * sizeof(char));
		if (!word)
			return (NULL);
		ft_strlcpy(word, &s[start], len + 1);
		return (word);
	}
	return (NULL);
}

static char	**ft_split_word(char *s, char c)
{
	char	**arr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	arr = malloc((ft_counter(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (s[j])
	{
		arr[i] = ft_read_word(s, c, &j);
		if (arr[i])
			i++;
		else if (s[j])
			return (ft_free(arr), NULL);
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	if (!s)
		return (NULL);
	return (ft_split_word((char *)s, c));
}
