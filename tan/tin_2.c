/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tin_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:02:17 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/06/18 09:58:41 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	checkCollision(snake *snake, position *fruit, t_state *state)
{
	int	i;

	i = 1;
	if (snake->body[0].x < 0 || snake->body[0].x >= WIDTH ||
		snake->body[0].y < 0 || snake->body[0].y >= HEIGHT) {
		return (printf("¡YOU LOST, parcero!\n"), 1);
	}
	while (i < snake->length)
	{
		if (snake->body[0].x == snake->body[i].x &&
			snake->body[0].y == snake->body[i].y) {
			return (printf("¡YOU LOST, parcero!\n"), 1);
		}
		i++;
	}
	if (snake->body[0].x == fruit->x && snake->body[0].y == fruit->y) {
		snake->length++;  // Incrementar la longitud de la serpiente
		fruit->x = my_rand(state) % WIDTH;  // Reubicar la fruta
		fruit->y = my_rand(state) % HEIGHT;
	}
	return (usleep(200000), 0);
}

// Detecta si hay una tecla presionada

int get_botton()
{
	struct termios oldt, newt;
	int bytesWaiting;

	// Guarda la configuración actual del terminal
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	// Desactiva el modo de espera de entrada
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	// Verifica si hay datos en el buffer de entrada
	ioctl(STDIN_FILENO, FIONREAD, &bytesWaiting);
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return bytesWaiting > 0;
}
