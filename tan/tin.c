/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:58:18 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/20 17:12:22 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	init_game(t_snake *snake, t_position *fruit, t_state *state)
{
	unsigned int	seed;
	int				ite;

	ite = 0;
	seed = generate_seed(ite);
	my_srand(seed, state);
	snake->length = 1;
	snake->body[0].x = WIDTH / 2;
	snake->body[0].y = HEIGHT / 2;
	snake->direction = RIGHT;
	fruit->x = my_rand(state) % WIDTH;
	fruit->y = my_rand(state) % HEIGHT;
}

int	draw_snake(const t_snake *snake, int i, int x, int y)
{
	while (i < snake->length)
	{
		if (snake->body[i].x == x && snake->body[i].y == y)
		{
			printf("◉");
			return (1);
		}
		i++;
	}
	return (0);
}

void	draw_game(const t_snake *snake, const t_position *fruit)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (draw_snake(snake, 0, x, y))
			{
				x++;
				continue ;
			}
			if (fruit->x == x && fruit->y == y)
				printf("★");
			else
				printf(".");
			x++;
		}
		printf("\n");
		y++;
	}
}

void	update_snake(t_snake *snake)
{
	int	i;

	i = snake->length - 1;
	while (i > 0)
	{
		snake->body[i] = snake->body[i - 1];
		i--;
	}
	if (snake->direction == UP)
		snake->body[0].y--;
	else if (snake->direction == DOWN)
		snake->body[0].y++;
	else if (snake->direction == LEFT)
		snake->body[0].x--;
	else if (snake->direction == RIGHT)
		snake->body[0].x++;
}

int	game_main(void)
{
	t_snake		snake;
	t_position	fruit;
	t_state		state;
	int			game_over;

	game_over = 0;
	state.seed = 1;
	state.fake_time = 0;
	init_game(&snake, &fruit, &state);
	while (!game_over)
	{
		printf("\033[H\033[J");
		draw_game(&snake, &fruit);
		if (get_botton())
			moves_snake(&snake);
		update_snake(&snake);
		game_over = check_collision(&snake, &fruit, &state);
	}
	return (0);
}
