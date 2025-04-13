/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:46:10 by jramos-a          #+#    #+#             */
/*   Updated: 2025/04/13 10:26:49 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void base_error(void);

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char *line;
	
	do_signals();
	
	using_history();

	while (1)
	{
		line = readline("AM33< ");
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
