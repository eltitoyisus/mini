/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:47:27 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/16 17:17:02 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	handle_space_case(t_parse *parse, t_sh *sh, char **env)
{
	t_parse	*temp;

	temp = parse;
	case_without_space(sh->input, env, parse);
	parse = temp;
	info_to_struct_2(parse, sh, 0);
}

void	prepare_token(t_parse *parse, char **split_input, int i, char **env)
{
	char	*temp;

	(void)env;
	temp = ft_strdup(split_input[i]);
	if (parse->line)
		free(parse->line);
	parse->line = temp;
}

void	finalize_parsing(t_parse *parse, t_sh *sh, int count,
		char **split_input)
{
	info_to_struct_2(parse, sh, count);
	free_words(split_input);
}

void	process_with_spaces(t_parse *parse, t_sh *sh, char **env)
{
	char	**split_input;
	int		i;
	int		count;
	t_parse	*temp;

	temp = parse;
	i = 0;
	split_input = ft_split(sh->input, ' ');
	count = ft_countsubstr(sh->input, ' ');
	while (parse != NULL && i < count)
	{
		prepare_token(parse, split_input, i, env);
		if (parse->type_token == -1)
			break ;
		i++;
		if (i != 0 && i < count)
		{
			ft_lstadd_back_parse(parse);
			parse = parse->next;
		}
	}
	finalize_parsing(temp, sh, count, split_input);
}

void	process_parse_nodes(t_parse *parse, t_sh *sh, int i)
{
	t_parse	*current;
	int		j;
	char	**allocated_strings;
	int		alloc_count;

	current = parse;
	j = 0;
	allocated_strings = NULL;
	alloc_count = 0;
	(void)alloc_count;
	(void)allocated_strings;
	while (current != NULL && j < i)
	{
		if (current->type_token == CMD || current->type_token == BUILT)
			type_cmd_built_2(sh, current, j);
		else if (current->type_token == RED || current->type_token == PIPE
			|| current->type_token == FILES)
			type_red_pipe_2(sh, current, j);
		j++;
		current = current->next;
	}
}
