/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:03:23 by jramos-a          #+#    #+#             */
/*   Updated: 2025/04/30 13:07:37 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char *line;

	while (1)
	{
		line = readline(COLOR "Cripto$hell% " RESET);
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
	rl_clear_history();
	return (0);
}
