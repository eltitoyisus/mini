/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:03:23 by jramos-a          #+#    #+#             */
/*   Updated: 2025/05/29 16:47:34 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_sh	*sh;

	if (argc != 1)
		return 0;
	ft_signals();
	sh = shell_factory(envp);
	sh->prompt = ft_prompt();
	using_history();
	while (1)
	{
		sh->input = readline(sh->prompt);
		if (!sh->input)
		{
			write(1, "exit\n", 5);
			break;
		}
		if (sh->input)
		{
			// if (ft_strncmp("tx", sh->input, 2) == 0)
			// 	ft_tx();
			add_history(sh->input);
			parse_comm(sh, envp);
			printf("linea completa --> %d %d \n", sh->node->line_is->cmd, sh->node->line_is->with_reds);
			printf("que belleza mi rey\n");
			exec_parsed_command(sh, envp);
		}
		free(sh->input);
	}
	clear_history();
	return (0);
}
