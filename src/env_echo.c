/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:33:48 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/21 17:26:15 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	handle_echo_quote_markers(char **p, int *in_single_quotes)
{
	if (**p == '\001')
	{
		*in_single_quotes = 1;
		(*p)++;
	}
	else if (**p == '\002')
	{
		*in_single_quotes = 0;
		(*p)++;
	}
	else if (**p == '\'')
	{
		*in_single_quotes = !(*in_single_quotes);
		(*p)++;
	}
}

int	handle_echo_special_vars(char **p, int in_single_quotes, char **envp)
{
	if (**p == '$' && *(*p + 1) == '?' && !in_single_quotes)
	{
		handle_exit_status(p);
		return (1);
	}
	else if (**p == '$' && !in_single_quotes)
	{
		handle_env_var(p, envp);
		return (1);
	}
	return (0);
}

void	process_echo_chars(char *p, char **envp)
{
	int	in_single_quotes;

	in_single_quotes = 0;
	while (*p)
	{
		handle_echo_quote_markers(&p, &in_single_quotes);
		if (handle_echo_special_vars(&p, in_single_quotes, envp))
			continue ;
		if (*p)
			printf("%c", *p++);
	}
}

void	print_echo_arg(char *arg, char **envp)
{
	char	*processed_arg;

	processed_arg = handle_echo_quotes(arg);
	if (!processed_arg)
		processed_arg = ft_strdup(arg);
	process_echo_chars(processed_arg, envp);
	free(processed_arg);
}

int	exec_echo(t_sh *sh)
{
	int		i;
	int		n_flag;
	char	**args;

	if (!sh || !sh->node || !sh->node->cmd || !sh->node->cmd->split_cmd)
		return (1);
	args = sh->node->cmd->split_cmd;
	i = 1;
	n_flag = parse_echo_flags(args, &i);
	while (args[i])
	{
		print_echo_arg(args[i], sh->env);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (0);
}
