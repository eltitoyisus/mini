/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:10:46 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/05/27 11:17:39 by dacastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	exec(t_sh *sh)
{
	if (sh->node->line_is->built == true)
		exec_builtin();
	else if (sh->node->line_is->cmd == true && sh->node->line_is->with_pipe == true)
		exec_cmd_pipe();
	else if (sh->node->line_is->cmd == true && sh->node->line_is->with_reds == true)
		exec_comm();
	else
		printf("command not found!");
}
