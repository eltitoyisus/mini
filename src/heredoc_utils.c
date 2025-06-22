/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:00:00 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/22 13:34:56 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

// char	*create_heredoc_filename(int index)
// {
// 	char	*filename;
// 	char	*temp;
// 	char	*index_str;
// 	pid_t	pid;

// 	(void)pid;
// 	pid = getpid();
// 	index_str = ft_itoa(index);
// 	if (!index_str)
// 		return (NULL);
// 	temp = ft_strjoin("heredoc_", index_str);
// 	free(index_str);
// 	if (!temp)
// 		return (NULL);
// 	filename = ft_strjoin(temp, ".tmp");
// 	free(temp);
// 	return (filename);
// }

// int	create_heredoc_file(int index, char **created_file)
// {
// 	char	*filename;
// 	int		fd;

// 	filename = create_heredoc_filename(index);
// 	if (!filename)
// 		return (-1);
// 	*created_file = filename;
// 	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd < 0)
// 	{
// 		perror("heredoc: open");
// 		free(filename);
// 		*created_file = NULL;
// 		return (-1);
// 	}
// 	return (fd);
// }

void	cleanup_heredoc_tempfiles(void)
{
	int		i;
	char	buffer[32];

	i = 0;
	while (1)
	{
		ft_snprintf(buffer, sizeof(buffer), "heredoc_%d.tmp", i);
		if (unlink(buffer) != 0)
			break ;
		i++;
	}
}

char	*generate_heredoc_filename(int index)
{
	char	buffer[32];

	ft_snprintf(buffer, sizeof(buffer), "heredoc_%d.tmp", index);
	return (ft_strdup(buffer));
}
