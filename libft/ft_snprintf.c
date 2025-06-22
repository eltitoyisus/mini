/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:08:37 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/22 13:08:37 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_snprintf_int_to_buf(char *num_buf, int num)
{
	int	k;
	int	n;
	int	is_neg;

	k = 0;
	n = num;
	is_neg = 0;
	if (num == 0)
		num_buf[k++] = '0';
	else
	{
		if (n < 0)
		{
			is_neg = 1;
			n = -n;
		}
		while (n > 0 && k < 11)
		{
			num_buf[k++] = (n % 10) + '0';
			n /= 10;
		}
		if (is_neg)
			num_buf[k++] = '-';
	}
	return (k);
}

static int	ft_snprintf_write_int(char *buffer, size_t size, int num, size_t *j)
{
	char	num_buf[12];
	int		k;

	k = ft_snprintf_int_to_buf(num_buf, num);
	while (k > 0 && *j + 1 < size)
		buffer[(*j)++] = num_buf[--k];
	return (0);
}

int	ft_snprintf(char *buffer, size_t size, const char *format, ...)
{
	va_list	args;
	size_t	i;
	size_t	j;
	int		num;

	i = 0;
	j = 0;
	va_start(args, format);
	while (format[i] && j + 1 < size)
	{
		if (format[i] == '%' && format[i + 1] == 'd')
		{
			num = va_arg(args, int);
			ft_snprintf_write_int(buffer, size, num, &j);
			i += 2;
		}
		else
			buffer[j++] = format[i++];
	}
	buffer[j] = '\0';
	va_end(args);
	return (j);
}
