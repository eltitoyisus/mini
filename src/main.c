/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:03:23 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/05 00:01:36 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_sh	*sh;

	if (argc != 1)
		exit(0);
	ft_signals();
	using_history();
	while (1)
	{
		sh = shell_factory(envp);
		sh->prompt = ft_prompt();
		sh->input = readline(sh->prompt);
		if (!sh->input)
		{
			write(1, "exit\n", 5);
			destroy_node(sh->node);
			break ;
		}
		if (sh->input)
		{
			// if (ft_strncmp("tx", sh->input, 2) == 0)
			// 	ft_tx();
			add_history(sh->input);
			parse_comm(sh, envp);
			// printf("linea completa --> %d %d \n", sh->node->line_is->cmd, sh->node->line_is->with_reds);
			// exec();
			printf("que belleza mi rey\n");
			exec_command(sh->input, envp, sh);
		}
		destroy_node(sh->node);
		// free(sh->input);
	}
	clear_history();
	return (0);
}
