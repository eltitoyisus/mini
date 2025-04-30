/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:03:23 by jramos-a          #+#    #+#             */
/*   Updated: 2025/04/30 10:59:00 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_sh	*sh;

	sh = shell_factory();
	sh->prompt = ft_prompt();
	using_history();

	while (1)
	{
		sh->input = readline(sh->prompt);
		if (!sh->input)
		{
			write(1, "\n", 1);
			break;
		}
		if (sh->input)
		{
			add_history(sh->input);
			exec_command(sh->input, envp);
		}
		free(sh->input);
	}
	clear_history();
	return (0);
}
