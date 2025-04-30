/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:03:23 by jramos-a          #+#    #+#             */
/*   Updated: 2025/04/30 10:12:51 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	*line;
	char	*user;

	user = ft_prompt();
	using_history();

	while (1)
	{
		line = readline(user);
		if (!line)
		{
			write(1, "\n", 1);
			break;
		}
		if (*line)
		{
			add_history(line);
			exec_command(line, envp);
		}
		free(line);
	}
	clear_history();
	return (0);
}
