/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 21:51:47 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/10 12:45:56 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char	*join_prompt(char *old_user, char *join)
{
	char	*prompt;

	prompt = ft_strjoin(old_user, join);
	free(old_user);
	return (prompt);
}

char	*ft_prompt(void)
{
	char	*user;

	user = ft_strdup("\001\033[44;97m@CRIPTOSHELL\033[0m\033[38;5;82m\002");
	user = join_prompt(user, "\033[0m \033[38;5;82m");
	user = join_prompt(user, "-");
	user = join_prompt(user, getenv("PWD"));
	user = join_prompt(user, " ~ \033[0;0m");

	return (user);
}
