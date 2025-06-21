/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:53:26 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/19 16:05:26 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	ft_error(char *msg, int ret)
{
	write(2, msg, ft_strlen(msg));
	exit(ret);
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}

void	free_words(char **words)
{
	int	i;

	i = 0;
	if (!words)
		return ;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
}

int	can_op(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	else
	{
		close(fd);
		return (1);
	}
}

int	error_quotes(char *line, int op)
{
	if (op == SIMPLE)
	{
		if ((ft_strchr(line, '\'') && ft_strchr(line, '\'')
				== ft_strrchr(line, '\'')) || (ft_strchr(line, '\'')
				&& ft_strchr(line, '\'') == ft_strrchr(line, '\'')))
			return (1);
	}
	else if (op == DOUBLE)
	{
		if ((ft_strchr(line, '\"') && ft_strchr(line, '\"')
				== ft_strrchr(line, '\"')) || (ft_strchr(line, '\'')
				&& ft_strchr(line, '\'') == ft_strrchr(line, '\'')))
			return (1);
	}
	return (0);
}
