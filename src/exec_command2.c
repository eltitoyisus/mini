/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:13:39 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/21 11:28:29 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	init_command_variables(t_command_vars *vars)
{
	vars->stdin_backup = -1;
	vars->has_heredoc = 0;
	vars->needs_cleanup = 0;
	vars->redirs = NULL;
	vars->clean_args = NULL;
}

int	backup_stdin(int *stdin_backup)
{
	if (isatty(STDIN_FILENO))
	{
		*stdin_backup = dup(STDIN_FILENO);
		if (*stdin_backup < 0)
		{
			perror("dup");
			return (1);
		}
	}
	return (0);
}

void	check_command_features(t_sh *sh, int *has_pipe, int *has_redirs,
		int *has_heredoc)
{
	int	i;

	*has_pipe = 0;
	*has_redirs = 0;
	i = 0;
	if (sh->node->cmd->split_cmd)
	{
		while (sh->node->cmd->split_cmd[i])
		{
			if (ft_strncmp(sh->node->cmd->split_cmd[i], "|", 2) == 0)
				*has_pipe = 1;
			else if (ft_strncmp(sh->node->cmd->split_cmd[i], ">", 2) == 0
				|| ft_strncmp(sh->node->cmd->split_cmd[i], ">>", 3) == 0
				|| ft_strncmp(sh->node->cmd->split_cmd[i], "<", 2) == 0
				|| ft_strncmp(sh->node->cmd->split_cmd[i], "<<", 3) == 0)
			{
				*has_redirs = 1;
				if (ft_strncmp(sh->node->cmd->split_cmd[i], "<<", 3) == 0)
					*has_heredoc = 1;
			}
			i++;
		}
	}
}

int	create_default_cat(t_sh *sh, int has_redirs, int stdin_backup,
		int *needs_cleanup)
{
	char	**cat_args;

	if (has_redirs && (!sh->node->cmd->split_cmd
			|| !sh->node->cmd->split_cmd[0]))
	{
		printf("Creating default cat command for heredoc\n");
		cat_args = malloc(sizeof(char *) * 2);
		if (!cat_args)
		{
			if (stdin_backup != -1)
				close(stdin_backup);
			return (1);
		}
		cat_args[0] = ft_strdup("cat");
		cat_args[1] = NULL;
		sh->node->cmd->split_cmd = cat_args;
		*needs_cleanup = 1;
	}
	return (0);
}

int	check_command_exists(t_sh *sh, int stdin_backup, int needs_cleanup)
{
	(void)needs_cleanup;
	if (!sh->node->cmd->split_cmd || !sh->node->cmd->split_cmd[0])
	{
		printf("No command to execute\n");
		if (stdin_backup != -1)
			close(stdin_backup);
		return (1);
	}
	return (0);
}
