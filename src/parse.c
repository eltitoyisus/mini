/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:24:19 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/11 11:42:58 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	info_to_struct_2(t_parse *parse, t_sh *sh, int i)
{
	t_parse	*original_parse;
	char	**saved_tokens;
	int		token_count;
	int		j;

	original_parse = parse;
	token_count = 0;
	j = 0;
	saved_tokens = save_tokens(parse, &token_count);
	if (!saved_tokens)
		return ;
	process_parse_nodes(parse, sh, i);
	if (sh && sh->node)
		build_command_args(sh, original_parse);
	while (j < token_count)
		free(saved_tokens[j++]);
	free(saved_tokens);
}

void	bool_active(t_parse *parse)
{
	t_parse	*count;

	count = parse;
	while (count != NULL)
	{
		if (count->type_token == CMD)
			count->is_cmd = true;
		else if (parse->type_token == FLAG)
			count->is_flag = true;
		count = count->next;
	}
}

void	case_without_space(char *sp_input, char **env, t_parse *parse)
{
	int	i;
	int	w;

	(void)env;
	i = 0;
	w = 0;
	printf("Aqui entra %s\n", sp_input);
	while (sp_input[i])
	{
		printf("ss\n");
		printf("(T->) %c\n", sp_input[i]);
		if (i > 0)
		{
			printf("nexxxt\n");
			ft_lstadd_back_parse(parse);
			parse = parse->next;
		}
		handle_input_character(sp_input, &i, &w, &parse);
	}
}

void	ft_parse(t_parse *parse, t_sh *sh, char **env)
{
	t_parse	*temp;

	(void)temp;
	temp = parse;
	if (space_case(sh->input))
	{
		handle_space_case(parse, sh, env);
		return ;
	}
	process_with_spaces(parse, sh, env);
}

void	parse_comm(t_sh *sh, char **env)
{
	t_parse	*parse;

	parse = init_parse();
	printf("reservada memoria\n");
	if (!sh || !sh->input)
		return ;
	ft_parse(parse, sh, env);
	printf("sale del parseo\n");
	ft_lstclear_parse(parse);
}
