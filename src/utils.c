/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:57:55 by jramos-a          #+#    #+#             */
/*   Updated: 2025/04/25 13:59:04 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void *safe_malloc(size_t size, bool calloc_flag)
{
    void *ptr;

    if (size == 0)
        perror(" Memory allocation failed.");
    if (calloc_flag)
        ptr = calloc(1, size);
    else
        ptr = malloc(size);
    if (!ptr)
        perror(" Memory allocation failed.");
    return (ptr);
}

void *safe_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void *new_ptr;

	if (new_size == 0)
		return (NULL);
	if (old_size == new_size)
		return (ptr);
	new_ptr = realloc(ptr, new_size);
	if (!new_ptr)
		perror(" Memory reallocation failed.");
	return (new_ptr);
}

void safe_getcwd(char *buf, size_t size)
{
	if (getcwd(buf, size) == NULL)
		perror(" getcwd failed.");
}

void safe_chdir(const char *path)
{
	if (chdir(path) == -1)
		perror(" chdir failed.");
}

void safe_close(int fd)
{
	if (close(fd) == -1)
		perror(" close failed.");
}
int safe_open(const char *path, t_open_flags flags)
{
	int fd;

	if (flags == READ)
		fd = open(path, O_RDONLY);
	else if (flags == WRITE)
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (flags == APPEND)
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		perror(" open failed.");
	return (fd);
}
void safe_dup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
		perror(" dup2 failed.");
}
