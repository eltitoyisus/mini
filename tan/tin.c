/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:58:18 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/18 09:58:41 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void init_Game(snake *snake, position *fruit, t_state *state)
{
	unsigned int	seed;
	unsigned int	ite;

	ite = 1;
	seed = generate_seed(ite++);
	my_srand(seed, state); // Semilla para números aleatorios
	snake->length = 1;
	snake->body[0].x = WIDTH / 2;
	snake->body[0].y = HEIGHT / 2;
	snake->direction = RIGHT;
	fruit->x = my_rand(state) % WIDTH;
	fruit->y = my_rand(state) % HEIGHT;
}

int	draw_snake(const snake *snake, int i, int x, int y)
{
	while (i < snake->length)
	{
		if (snake->body[i].x == x && snake->body[i].y == y)
		{
			printf("\033[0;32m◉\033[0m");
			return (1);
		}
		i++;
	}
	return (0);
}

void drawGame(const snake *snake, const position *fruit)
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
				x++; // Saltamos al siguiente `x`.
				continue;
			}
			if (fruit->x == x && fruit->y == y)
			printf("\033[0;31m★\033[0m"); // Dibuja la fruta.
			else
			printf("."); // Dibuja un espacio vacío.
			x++; // Incremento de `x`.
		}
		printf("\n");
		y++; // Incremento de `y`.
	}
}

void updateSnake(snake *snake)
{
	int	i;

	i = snake->length - 1;
	while (i > 0)
	{
		snake->body[i] = snake->body[i - 1];
		i--;
	}
	if (snake->direction == UP) snake->body[0].y--;
	else if (snake->direction == DOWN) snake->body[0].y++;
	else if (snake->direction == LEFT) snake->body[0].x--;
	else if (snake->direction == RIGHT) snake->body[0].x++;
}

int game_main()
{
	snake		snake;
	position	fruit;
	t_state	state;
	int			gameOver;

	gameOver = 0;
	state.seed = 1;
	state.fake_time = 0;
	init_Game(&snake, &fruit, &state);
	while (!gameOver)
	{
		printf("\033[H\033[J"); // Limpia la consola
		drawGame(&snake, &fruit);
		if (get_botton())
		{ // Cambiar dirección si hay entrada
			char key = getch();
			if (key == 'w') snake.direction = UP;
			else if (key == 's') snake.direction = DOWN;
			else if (key == 'a') snake.direction = LEFT;
			else if (key == 'd') snake.direction = RIGHT;
		}
		updateSnake(&snake);
		gameOver = checkCollision(&snake, &fruit, &state); // Control de velocidad (200 ms)
	}
	return (0);
}
