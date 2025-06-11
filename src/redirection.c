/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:11:23 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/11 15:49:20 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	has_redirection_in_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd || !cmd->split_cmd)
		return (0);
	i = 0;
	while (cmd->split_cmd[i])
	{
		if (ft_strncmp(cmd->split_cmd[i], ">", 2) == 0
			|| ft_strncmp(cmd->split_cmd[i], ">>", 3) == 0
			|| ft_strncmp(cmd->split_cmd[i], "<", 2) == 0
			|| ft_strncmp(cmd->split_cmd[i], "<<", 3) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	**prepare_cmd_args(char **args)
{
	int		i;
	int		j;
	char	**cmd_args;

	cmd_args = malloc(sizeof(char *) * (count_cmd_args(args) + 1));
	if (!cmd_args)
		return (NULL);
	i = 0;
	j = 0;
	while (args[i])
	{
		if (is_redirection_with_arg(args, i))
			i += 2;
		else
			cmd_args[j++] = ft_strdup(args[i++]);
	}
	cmd_args[j] = NULL;
	return (cmd_args);
}

int	do_redir(char *command, char **envp)
{
	char	**args;
	t_reds	*redirs;
	int		result;
	char	**cmd_args;

	args = ft_split(command, ' ');
	if (!args)
		return (1);
	redirs = parse_redirection(args);
	if (!redirs)
		return (handle_redir_error(args));
	if (open_all_redirs(redirs) < 0)
		return (free_args(args), free_redirs(redirs), 1);
	cmd_args = prepare_cmd_args(args);
	if (!cmd_args)
		return (free_args(args), free_redirs(redirs), 1);
	result = exec_redirs(cmd_args, envp, redirs);
	free_args(cmd_args);
	free_args(args);
	free_redirs(redirs);
	return (result);
}

int	handle_redirs(char *command, char **envp)
{
	char	**args;
	int		result;

	args = ft_split(command, ' ');
	if (!args)
		return (1);
	if (has_redirection(args))
	{
		free_args(args);
		result = do_redir(command, envp);
	}
	else
	{
		free_args(args);
		result = 0;
	}
	return (result);
}
