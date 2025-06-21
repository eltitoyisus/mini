/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tin_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:02:17 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/20 20:11:15 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	check_collision(t_snake *snake, t_position *fruit, t_state *state)
{
	int	i;

	i = 1;
	if (snake->body[0].x < 0 || snake->body[0].x >= WIDTH
		|| snake->body[0].y < 0 || snake->body[0].y >= HEIGHT)
		return (printf("¡YOU LOST, parcero!\n"), 1);
	while (i < snake->length)
	{
		if (snake->body[0].x == snake->body[i].x
			&& snake->body[0].y == snake->body[i].y)
			return (printf("¡YOU LOST, parcero!\n"), 1);
		i++;
	}
	if (snake->body[0].x == fruit->x && snake->body[0].y == fruit->y)
	{
		snake->length++;
		fruit->x = my_rand(state) % WIDTH;
		fruit->y = my_rand(state) % HEIGHT;
	}
	return (usleep(200000), 0);
}

int	get_botton(void)
{
	struct termios	newt;
	struct termios	oldt;
	int				bytes_waiting;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ioctl(STDIN_FILENO, FIONREAD, &bytes_waiting);
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return (bytes_waiting > 0);
}

void	moves_snake(t_snake *snake)
{
	char	key;

	key = getch();
	if (key == 'w')
		snake->direction = UP;
	else if (key == 's')
		snake->direction = DOWN;
	else if (key == 'a')
		snake->direction = LEFT;
	else if (key == 'd')
		snake->direction = RIGHT;
}

int	is_game(t_sh *sh)
{
	if (!ft_strncmp(sh->input, "snake", 5))
	{
		game_main();
		return (1);
	}
	else
		return (0);
}
