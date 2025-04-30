/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 21:51:47 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/04/30 20:05:08 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char *ft_prompt(void)
{
	char *user;
	char *tmp;
	char *cwd = getenv("PWD");

	if (!cwd)
		cwd = "";
	user = ft_strdup("\033[44;97m@CRIPTOSHELL\033[0m\033[38;5;82m");
	if (!user)
		return (NULL);
	tmp = ft_strjoin(user, " -");
	free(user);
	if (!tmp)
		return (NULL);
	user = ft_strjoin(tmp, cwd);
	free(tmp);
	if (!user)
		return (NULL);
	tmp = ft_strjoin(user, " ~ \033[0;0m");
	free(user);
	return tmp;
}

