/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:33:48 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/09 19:33:48 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

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

void	print_echo_arg(char *arg, char **envp)
{
	if (ft_strncmp(arg, "$?", 2) == 0)
		print_exit_status();
	else if (arg[0] == '$')
	{
		if (!echo_var(&arg, 0, envp))
			printf("%s", arg);
	}
	else
		printf("%s", arg);
}

int	exec_echo(char **args, char **envp)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = parse_echo_flags(args, &i);
	while (args[i])
	{
		print_echo_arg(args[i], envp);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (0);
}
