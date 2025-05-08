/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifiers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:23:12 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/05/09 00:23:06 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	id_red(char **input_s, int i)
{
	if (!ft_strncmp(input_s[i], "<", 1))
		return (INRED);
	else if (!ft_strncmp(input_s[i], ">", 1))
		return (OURED);
	else if (!ft_strncmp(input_s[2], ">>", 2))
		return (D_OURED);
	else if (!ft_strncmp(input_s[i], "<<", 2))
		return (HEREDOC);

}


int	id_file(char **input_s, int i)
{
	if (!ft_strncmp(input_s[i - 1], "<", 1) && can_op(input_s[i]))
		return (INFILE);
	if (!ft_strncmp(input_s[i - 1], ">", 1))
		return (OUTFILE_TR);
	if (!ft_strncmp(input_s[i - 1], ">>", 2))
		return (OUTFILE_APP);
	if (!ft_strncmp(input_s[i - 1], "<<", 2))
		return (DELIM);
}
