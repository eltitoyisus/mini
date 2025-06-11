/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:40:59 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/09 18:40:59 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	has_redirection(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_strncmp(args[i], ">", 2) == 0 || ft_strncmp(args[i], ">>",
				3) == 0 || ft_strncmp(args[i], "<", 2) == 0
			|| ft_strncmp(args[i], "<<", 3) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	handle_redir_error(char **args)
{
	free_args(args);
	printf("Invalid redirection syntax\n");
	return (1);
}

int	get_redir_type(char *redir_str)
{
	if (ft_strncmp(redir_str, ">>", 3) == 0)
		return (D_OURED);
	if (ft_strncmp(redir_str, ">", 2) == 0)
		return (OURED);
	if (ft_strncmp(redir_str, "<<", 3) == 0)
		return (HEREDOC);
	if (ft_strncmp(redir_str, "<", 2) == 0)
		return (INRED);
	return (-1);
}

int	is_redir_with_target(char **args, int i)
{
	return ((ft_strncmp(args[i], ">", 2) == 0 || ft_strncmp(args[i], ">>",
				3) == 0 || ft_strncmp(args[i], "<", 2) == 0
			|| ft_strncmp(args[i], "<<", 3) == 0) && args[i + 1]);
}

t_reds	*create_redir_node(char **args, int i)
{
	t_reds	*new;

	new = malloc(sizeof(t_reds));
	if (!new)
		return (NULL);
	new->type = get_redir_type(args[i]);
	new->file = ft_strdup(args[i + 1]);
	new->delim = NULL;
	new->next = NULL;
	new->fd = -1;
	return (new);
}
