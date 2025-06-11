/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_no_space.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:05:38 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/11 10:05:38 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	process_double_redirection(char *sp_input, int *i, t_parse *parse)
{
	parse->line = ft_substr(sp_input, *i, 2);
	while (sp_input[*i] == '<' || sp_input[*i] == '>')
		(*i)++;
}

void	process_single_redirection(char *sp_input, int *i, t_parse *parse)
{
	printf("odi\n");
	parse->line = ft_substr(sp_input, *i, 1);
	printf("yes\n");
	(*i)++;
}

void	process_pipe_token(char *sp_input, int *i, t_parse *parse)
{
	parse->line = ft_substr(sp_input, *i, 1);
	(*i)++;
}

void	handle_command_parts(char **cmd_parts, t_parse **parse, char **env)
{
	int	j;

	j = 1;
	while (cmd_parts[j])
	{
		ft_lstadd_back_parse(*parse);
		*parse = (*parse)->next;
		(*parse)->line = ft_strdup(cmd_parts[j]);
		(*parse)->type_token = n_token((*parse)->line, env, NULL, 0);
		printf("sale condicion parseline -> %s \n", (*parse)->line);
		j++;
	}
	j = 0;
	while (cmd_parts[j])
		free(cmd_parts[j++]);
	free(cmd_parts);
}

void	process_command_with_spaces(char *cmd_segment, t_parse **parse,
		char **env)
{
	char	**cmd_parts;

	cmd_parts = ft_split(cmd_segment, ' ');
	if (cmd_parts && cmd_parts[0])
	{
		(*parse)->line = ft_strdup(cmd_parts[0]);
		(*parse)->type_token = n_token((*parse)->line, env, NULL, 0);
		printf("sale condicion parseline -> %s \n", (*parse)->line);
		handle_command_parts(cmd_parts, parse, env);
	}
	free(cmd_segment);
}
