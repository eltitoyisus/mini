/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:25:54 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/09 19:25:54 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static int	ft_itoa_len(long int num)
{
	int	len;

	len = 0;
	if (num <= 0)
		len = 1;
	while (num)
	{
		num /= 10;
		len++;
	}
	return (len);
}

void	ft_itoa_into(int n, char *str)
{
	long int	num;
	int			i;
	int			len;
	int			sign;

	num = n;
	sign = 0;
	if (num < 0)
	{
		sign = 1;
		num = -num;
		str[0] = '-';
	}
	len = ft_itoa_len(num);
	i = len + sign - 1;
	str[len + sign] = '\0';
	if (num == 0)
		str[0] = '0';
	while (num > 0)
	{
		str[i--] = (num % 10) + '0';
		num /= 10;
	}
}
