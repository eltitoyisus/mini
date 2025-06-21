/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:05:16 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/21 22:14:59 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	prepare_command_node(t_sh *sh)
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
}

void	process_input(t_sh *sh, char **envp)
{
	char	*normalized_input;

	prepare_command_node(sh);
	if (sh->input[0] != '\0')
	{
		add_history(sh->input);
		normalized_input = insert_spaces_around_operators(sh->input);
		if (normalized_input)
		{
			free(sh->input);
			sh->input = normalized_input;
		}
		parse_comm(sh, envp);
		if (sh->node->cmd && sh->node->cmd->split_cmd
			&& sh->node->cmd->split_cmd[0]
			&& is_var_command(sh->node->cmd->split_cmd[0]))
			exec_var_command(sh, envp);
		else
			exec_parsed_command(sh, envp);
	}
}

void	shell_loop(t_sh *sh, char **envp)
{
	(void)envp;
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
			is_game(sh);
			process_input(sh, sh->env);
			free(sh->input);
			sh->input = NULL;
		}
	}
	rl_clear_history();
}
