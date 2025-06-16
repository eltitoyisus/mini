/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:46:52 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/16 17:16:41 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	handle_double_redirection(char *sp_input, int *i, t_parse *parse)
{
	parse->line = ft_substr(sp_input, *i, 2);
	while (sp_input[*i] == '<' || sp_input[*i] == '>')
		(*i)++;
}

void	handle_single_redirection(char *sp_input, int *i, t_parse *parse)
{
	parse->line = ft_substr(sp_input, *i, 1);
	(*i)++;
}

void	handle_pipe(char *sp_input, int *i, t_parse *parse)
{
	(void)sp_input;
	parse->type_token = PIPE;
	parse->line = ft_strdup("|");
	ft_lstadd_back_parse(parse);
	(*i)++;
}

void	handle_command_segment(char *cmd_segment, char **env, t_parse **parse)
{
	char	**cmd_parts;
	int		j;

	cmd_parts = ft_split(cmd_segment, ' ');
	if (cmd_parts && cmd_parts[0])
	{
		(*parse)->line = ft_strdup(cmd_parts[0]);
		(*parse)->type_token = n_token((*parse)->line, env, NULL, 0);
		j = 1;
		while (cmd_parts[j])
		{
			ft_lstadd_back_parse(*parse);
			*parse = (*parse)->next;
			(*parse)->line = ft_strdup(cmd_parts[j]);
			(*parse)->type_token = n_token((*parse)->line, env, NULL, 0);
			j++;
		}
		j = 0;
		while (cmd_parts[j])
			free(cmd_parts[j++]);
		free(cmd_parts);
	}
	free(cmd_segment);
}

void	handle_other_cases(char *sp_input, int *i, t_parse **parse, char **env)
{
	int		w;
	char	*cmd_segment;

	w = *i;
	while (sp_input[w] != '|' && sp_input[w] != '<' && sp_input[w] != '>'
		&& sp_input[w])
		w++;
	cmd_segment = ft_substr(sp_input, *i, w - *i);
	if (ft_strchr(cmd_segment, ' '))
		handle_command_segment(cmd_segment, env, parse);
	else
	{
		(*parse)->line = cmd_segment;
		(*parse)->type_token = n_token((*parse)->line, env, NULL, 0);
	}
	*i = w;
}
