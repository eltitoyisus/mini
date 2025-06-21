/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_echo4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:24:31 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/19 18:24:31 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char	*process_quotes_content(char *input, int len, int is_single_quoted)
{
	char	*result;

	result = init_quotes_result(len);
	if (!result)
		return (NULL);
	return (process_quotes_loop(result, input, is_single_quoted));
}

char	*handle_echo_quotes(char *input)
{
	int	len;
	int	is_single_quoted;
	int	is_double_quoted;

	if (!input)
		return (NULL);
	len = ft_strlen(input);
	if (!check_quotes_type(input, len, &is_single_quoted, &is_double_quoted))
		return (NULL);
	return (process_quotes_content(input, len, is_single_quoted));
}

void	process_echo_argument(t_parse *parse)
{
	char	*processed;

	if (parse->prev && parse->prev->type_token == BUILT
		&& !ft_strncmp(parse->prev->line, "echo", 4))
	{
		processed = handle_echo_quotes(parse->line);
		if (processed)
		{
			free(parse->line);
			parse->line = processed;
		}
	}
}

int	parse_echo_flags(char **args, int *i)
{
	int	n_flag;

	n_flag = 0;
	if (args[1] && ft_strncmp(args[1], "-n", 3) == 0)
	{
		n_flag = 1;
		(*i)++;
	}
	return (n_flag);
}

void	print_exit_status(void)
{
	char	exit_status[12];
	int		status;

	status = last_signal_code(-1);
	ft_itoa_into(status, exit_status);
	printf("%s", exit_status);
}
