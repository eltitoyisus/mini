/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:05:16 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/18 02:48:33 by daniel-cast      ###   ########.fr       */
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
			write(1, "exit\n", 5);
			break ;
		}
		if (sh->prompt)
			free(sh->prompt);
		sh->prompt = NULL;
		if (sh->input)
		{
			if (!ft_strncmp(sh->input, "snake", 5))
			{
				game_main();
				continue;
			}
			process_input(sh, envp);
			free(sh->input);
			sh->input = NULL;
		}
	}
	rl_clear_history();
}
