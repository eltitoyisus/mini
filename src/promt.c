/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 21:51:47 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/04/28 22:16:43 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char	*ft_prompt(void)
{
	char	*user;

	user = "\033[44;97m@CRIPTOSHELL\033[0m\033[38;5;82m";
	user = ft_strjoin(user, "\033[0m \033[38;5;82m");
	user = ft_strjoin(user, "-");
	user = ft_strjoin(user, getenv("PWD"));
	user = ft_strjoin(user, " ~ \033[0;0m");

	return (user);
}
