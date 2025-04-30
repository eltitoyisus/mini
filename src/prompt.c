/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 21:51:47 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/04/30 13:07:51 by jramos-a         ###   ########.fr       */
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
