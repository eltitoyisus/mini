/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 21:51:47 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/12 12:32:41 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char	*ft_prompt(void)
{
	char	*user;
	char	*cwd;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	user = "\001\033[44;97m@CRIPTOSHELL\033[0m\033[38;5;82m\002";
	tmp = ft_strjoin(user, "\033[0m \033[38;5;82m");
	user = tmp;
	tmp = ft_strjoin(user, "-");
	free(user);
	user = tmp;
	if (cwd)
	{
		tmp = ft_strjoin(user, cwd);
		free(user);
		user = tmp;
		free(cwd);
	}
	tmp = ft_strjoin(user, " ~ \033[0;0m");
	free(user);
	user = tmp;
	return (user);
}
