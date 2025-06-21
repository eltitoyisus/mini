/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_no_space2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:41:30 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/21 18:00:09 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	process_command_without_spaces(char *cmd_segment, t_parse **parse,
		char **env)
{
	(*parse)->line = cmd_segment;
	(*parse)->type_token = n_token((*parse)->line, env, NULL, 0);
}

void	process_command_segment(char *sp_input, int *i, int *w, t_parse **parse)
{
	char	*cmd_segment;

	*w = *i;
	while (sp_input[*w] != '|' && sp_input[*w] != '<' && sp_input[*w] != '>'
		&& sp_input[*w])
		(*w)++;
	cmd_segment = ft_substr(sp_input, *i, *w - *i);
	if (ft_strchr(cmd_segment, ' '))
		process_command_with_spaces(cmd_segment, parse, NULL);
	else
		process_command_without_spaces(cmd_segment, parse, NULL);
	*i = *w;
}

void	handle_input_character(char *sp_input, int *i, int *w, t_parse **parse)
{
	if ((sp_input[*i] == '<' && sp_input[*i + 1] == '<') || (sp_input[*i] == '>'
			&& sp_input[*i + 1] == '>'))
		process_double_redirection(sp_input, i, *parse);
	else if ((sp_input[*i] == '<' && sp_input[*i + 1] != '<')
		|| (sp_input[*i] == '>' && sp_input[*i + 1] != '>'))
		process_single_redirection(sp_input, i, *parse);
	else if (sp_input[*i] == '|')
		process_pipe_token(sp_input, i, *parse);
	else
		process_command_segment(sp_input, i, w, parse);
	if (sp_input[*i] && sp_input[*i] != '|' && sp_input[*i] != '<'
		&& sp_input[*i] != '>')
	{
		(*parse)->type_token = n_token((*parse)->line, NULL, NULL, 0);
	}
}

void	ft_controls(t_parse *parse)
{
	bool_active(parse);
}
