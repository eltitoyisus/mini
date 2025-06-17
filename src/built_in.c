/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:07:10 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/17 11:18:02 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	exec_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
}

int	exec_exit(t_sh *sh, char **args)
{
	int	exit_status;

	exit_status = 0;
	if (args[1])
	{
		if (ft_isdigit(args[1][0]) || (args[1][0] == '-'
				&& ft_isdigit(args[1][1])))
		{
			exit_status = ft_atoi(args[1]);
		}
		else
		{
			write(2, "exit: numeric argument required\n", 31);
			exit_status = 255;
		}
	}
	rl_clear_history();
	free_shell(sh);
	exit(exit_status);
}
