/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:00:00 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/17 12:00:00 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char	*create_heredoc_filename(int index)
{
	char	*filename;
	char	*temp;
	char	*index_str;
	pid_t	pid;

	(void)pid;
	pid = getpid();
	index_str = ft_itoa(index);
	if (!index_str)
		return (NULL);
	temp = ft_strjoin("heredoc_", index_str);
	free(index_str);
	if (!temp)
		return (NULL);
	filename = ft_strjoin(temp, ".tmp");
	free(temp);
	return (filename);
}

int	create_heredoc_file(int index, char **created_file)
{
	char	*filename;
	int		fd;

	filename = create_heredoc_filename(index);
	if (!filename)
		return (-1);
	*created_file = filename;
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("heredoc: open");
		free(filename);
		*created_file = NULL;
		return (-1);
	}
	return (fd);
}

void	unlink_heredoc_files(int max_index)
{
	int		i;
	char	*filename;

	i = 0;
	while (i <= max_index)
	{
		filename = create_heredoc_filename(i);
		if (filename)
		{
			unlink(filename);
			free(filename);
		}
		i++;
	}
	unlink("heredoc.tmp");
}
