/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:18:51 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/20 16:49:58 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char	ft_getchar(void)
{
	char	c;

	if (read(STDIN_FILENO, &c, 1) > 0)
		return (c);
	return ('\0');
}

void	my_srand(unsigned int new_seed, t_state *state)
{
	state->seed = new_seed;
}

int	my_rand(t_state *state)
{
	unsigned int	a;
	unsigned int	c;
	unsigned int	m;

	a = 1103515245;
	c = 12345;
	m = 2147483648;
	state->seed = (state->seed * a + c) % m;
	return ((int)(state->seed & 0x7FFFFFFF));
}

unsigned int	generate_seed(int iteration)
{
	return ((iteration * 1103515245 + 12345) & 0x7FFFFFFF);
}

char	getch(void)
{
	struct termios	newt;
	struct termios	oldt;
	char			ch;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = ft_getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return (ch);
}
