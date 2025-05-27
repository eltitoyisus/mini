/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:03:23 by jramos-a          #+#    #+#             */
/*   Updated: 2025/05/27 12:00:39 by dacastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_sh	*sh;

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
			// exec();
			printf("que belleza mi rey\n");
			exec_command(sh->input, envp, sh);
		}
		free(sh->input);
	}
	clear_history();
	return (0);
}
