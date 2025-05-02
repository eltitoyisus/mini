/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:04:14 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/05/01 11:56:38 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	ctrl_c(int sign)
{
	(void)sign;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_signals(void)
{
	struct sigaction	sa;

	signal(SIGQUIT, SIG_IGN);  // SABES
	sa.sa_handler = ctrl_c;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("Signal failed\n");
		exit(1);
	}
}

// int last_signal_code(char **argv, char **envp)
// {
// 	printf("a");
// 	// esta funcion es para que al hacer exit me coja el codigo de salida
// }

// // esta funcion es solo para printear el codigo de salida

// int echo_signal(char **args, char **envp) // estoy usando esta variable en exe_Echo en built_in.c
// {
// 	(void)args;
// 	(void)envp;
// 	printf("%s", last_signal_code());
// 	return (1);
// }