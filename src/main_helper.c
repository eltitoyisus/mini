/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:05:16 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/11 16:05:16 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	process_input(t_sh *sh, char **envp)
{
	if (sh->node)
	{
		if (sh->node->cmd)
			free_cmd(sh->node->cmd);
		if (sh->node->arg)
			free(sh->node->arg);
		sh->node->cmd = cmd_factory();
		sh->node->arg = NULL;
		if (sh->node->line_is)
		{
			sh->node->line_is->built = false;
			sh->node->line_is->cmd = false;
			sh->node->line_is->with_pipe = false;
			sh->node->line_is->with_reds = false;
		}
		sh->node->n_cmd = 1;
	}
	if (sh->input[0] != '\0')
	{
		add_history(sh->input);
		parse_comm(sh, envp);
		printf("linea completa --> %d %d \n", sh->node->line_is->cmd,
			sh->node->line_is->with_reds);
		exec_parsed_command(sh, envp);
	}
}

void	shell_loop(t_sh *sh, char **envp)
{
	while (1)
	{
		if (sh->prompt)
			free(sh->prompt);
		sh->prompt = ft_prompt();
		sh->input = readline(sh->prompt);
		if (!sh->input)
		{
			free(sh->input);
			write(1, "exit\n", 5);
			break ;
		}
		if (sh->input)
		{
			process_input(sh, envp);
			free(sh->input);
		}
	}
	clear_history();
}
