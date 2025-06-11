/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifiers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:23:12 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/05/16 15:08:47 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	id_red(t_parse *parse)
{
	if (!ft_strncmp(parse->line, "<", 1))
		return (INRED);
	else if (!ft_strncmp(parse->line, ">", 1))
		return (OURED);
	else if (!ft_strncmp(parse->line, ">>", 2))
		return (D_OURED);
	else if (!ft_strncmp(parse->line, "<<", 2))
		return (HEREDOC);
	return (-1);
}

int	id_file(t_parse *parse)
{
	if (!ft_strncmp(parse->prev->line, "<", 1) && can_op(parse->line))
		return (INFILE);
	if (!ft_strncmp(parse->prev->line, ">", 1))
		return (OUTFILE_TR);
	if (!ft_strncmp(parse->prev->line, ">>", 2))
		return (OUTFILE_APP);
	if (!ft_strncmp(parse->prev->line, "<<", 2))
		return (DELIM);
	return (-1);
}
