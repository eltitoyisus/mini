/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_pieces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 01:15:27 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/05 01:22:17 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void get_O(char pattern[4][4])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	char temp[4][4] = {
		{' ', '▓', '▓', ' '},
		{' ', '▓', '▓', ' '},
		{' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' '}
	};
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			pattern[i][j] = temp[i][j];
			j++;
		}
		i++;
	}
}

void get_T(char pattern[4][4])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	char temp[4][4] = {
		{' ', '▓', ' ', ' '},
		{'▓', '▓', '▓', ' '},
		{' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' '}
	};
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			pattern[i][j] = temp[i][j];
			j++;
		}
		i++;
	}
}

void get_L(char pattern[4][4])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	char temp[4][4] = {
		{'▓', ' ', ' ', ' '},
		{'▓', ' ', ' ', ' '},
		{'▓', '▓', ' ', ' '},
		{' ', ' ', ' ', ' '}
	};
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			pattern[i][j] = temp[i][j];
			j++;
		}
		i++;
	}
}

void get_J(char pattern[4][4])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	char temp[4][4] = {
		{' ', ' ', '▓', ' '},
		{' ', ' ', '▓', ' '},
		{' ', '▓', '▓', ' '},
		{' ', ' ', ' ', ' '}
	};
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			pattern[i][j] = temp[i][j];
			j++;
		}
		i++;
	}
}

void get_S(char pattern[4][4])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	char temp[4][4] = {
			{' ', '▓', '▓', ' '},
			{'▓', '▓', ' ', ' '},
			{' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' '}
	};
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			pattern[i][j] = temp[i][j];
			j++;
		}
		i++;
	}
}
