/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:43:01 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/09 18:43:01 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

t_reds	*create_redirection_node(char **cmd_array, int i)
{
	t_reds	*new;

	new = malloc(sizeof(t_reds));
	if (!new)
		return (NULL);
	new->type = get_redir_type(cmd_array[i]);
	new->file = ft_strdup(cmd_array[i + 1]);
	new->delim = NULL;
	new->next = NULL;
	new->fd = -1;
	return (new);
}

int	is_redirection_op(char **cmd_array, int i)
{
	return ((ft_strncmp(cmd_array[i], ">", 2) == 0 || ft_strncmp(cmd_array[i],
				">>", 3) == 0 || ft_strncmp(cmd_array[i], "<", 2) == 0
			|| ft_strncmp(cmd_array[i], "<<", 3) == 0) && cmd_array[i + 1]);
}

int	count_clean_args(t_cmd *cmd)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (cmd->split_cmd[i])
	{
		if (is_redirection_op(cmd->split_cmd, i))
			i += 2;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

char	**clean_cmd_args(t_cmd *cmd)
{
	char	**new_args;
	int		i;
	int		j;

	if (!cmd || !cmd->split_cmd)
		return (NULL);
	new_args = malloc(sizeof(char *) * (count_clean_args(cmd) + 1));
	if (!new_args)
		return (NULL);
	i = 0;
	j = 0;
	while (cmd->split_cmd[i])
	{
		if (is_redirection_op(cmd->split_cmd, i))
			i += 2;
		else
			new_args[j++] = ft_strdup(cmd->split_cmd[i++]);
	}
	new_args[j] = NULL;
	return (new_args);
}
