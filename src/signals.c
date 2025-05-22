/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:04:14 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/05/22 17:34:25 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static int g_exit_status = 0;

void	ctrl_c(int sign)
{
	(void)sign;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 130;

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

int last_signal_code(int code)
{
	if (code >= 0)
		g_exit_status = code;
	return (g_exit_status);
}
