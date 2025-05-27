/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 21:51:47 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/05/27 13:11:28 by dacastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char	*ft_prompt(void)
{
	char	*user;

	user = "\001\033[44;97m@CRIPTOSHELL\033[0m\033[38;5;82m\002";
	user = ft_strjoin(user, "\033[0m \033[38;5;82m");
	user = ft_strjoin(user, "-");
	user = ft_strjoin(user, getenv("PWD"));
	user = ft_strjoin(user, " ~ \033[0;0m");

	return (user);
}
