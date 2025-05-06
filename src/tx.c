/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tx.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:48:39 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/05/03 20:16:58 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	types_2(t_piece *p)
{

}

void	define_t1(char **piece)
{

}

void	types(t_piece *p)
{

			char piece[7][4][4];
			int	i;

			i = 0;
			while (i < 7)
			{
				define_t1(piece[i]);
			}

			=
			{
			{
				{'▓', '▓', '▓', ' '},
				{'▓', ' ', ' ', ' '},
				{' ', ' ', ' ', ' '},
				{' ', ' ', ' ', ' '}
			},
			{ // O-piece
				{'▓', '▓', ' ', ' '},
				{'▓', '▓', ' ', ' '},
				{' ', ' ', ' ', ' '},
				{' ', ' ', ' ', ' '}
			},
			{ // T-piece
				{' ', '▓', ' ', ' '},
				{'▓', '▓', '▓', ' '},
				{' ', ' ', ' ', ' '},
				{' ', ' ', ' ', ' '}
			},
			{ // L-piece
				{'▓', ' ', ' ', ' '},
				{'▓', ' ', ' ', ' '},
				{'▓', '▓', ' ', ' '},
				{' ', ' ', ' ', ' '}
			},
			{ // J-piece
				{' ', ' ', '▓', ' '},
				{' ', ' ', '▓', ' '},
				{' ', '▓', '▓', ' '},
				{' ', ' ', ' ', ' '}
			},
			{ // S-piece
				{' ', '▓', '▓', ' '},
				{'▓', '▓', ' ', ' '},
				{' ', ' ', ' ', ' '},
				{' ', ' ', ' ', ' '}
			},
			{ // Z-piece
				{'▓', '▓', ' ', ' '},
				{' ', '▓', '▓', ' '},
				{' ', ' ', ' ', ' '},
				{' ', ' ', ' ', ' '}
			},
			{ // I-piece
				{'▓', '▓', '▓', '▓'},
				{' ', ' ', ' ', ' '},
				{' ', ' ', ' ', ' '},
				{' ', ' ', ' ', ' '}
			}

		};
}

t_piece	*init_piece(void)
{
	t_piece	*p;
	int	i;
	int	j;

	i = 0;
	j = 0;
	p = malloc(sizeof(t_piece));
	p->x = 10;
	p->y = 3;
	p->piece = malloc (7 * sizeof(char **));
	while (i < 7)
	{
		p->piece[i] = malloc(4 * sizeof(char *));
		while (j < 4)
		{
			p->piece[i][j] = malloc(4 * sizeof(char));
			j++;
		}
		i++;
	}
	save_types(p);
	return (p);
}

char my_getchar()
{
	char	c;

	if (read(0, &c, 1) > 0) {
	    return c;
	}
	return '\0';
}

void game_loop(t_tx *tx,int i, int j)
{
	(void)i;
	(void)j;
	t_piece	*p;

	p = init_piece();
	while (1)
	{
		// i = 0;
		// j = 0;
		// Limpiar pantalla
		write(1, "\033[H\033[J", 6);
		// Mostrar
		save_info(tx, i, j);
		// Procesar entrada de usuario
		// char c;

		// c = my_getchar();

		//USARÉ ESTO DESPUÉS

		// if (c == 'a') move_piece(&active_piece, -1, 0); 				// Izquierda
		// if (c == 'd') move_piece(&active_piece, 1, 0);  				// Derecha
		// if (c == 's') move_piece(&active_piece, 0, 1);  				// Abajo
		// if (c == 'w') rotate_piecwrite(1, &c, 1);e(&active_piece);      				// Rotar

		// Bajar pieza automáticamente

		// move_piece(&active_piece, 0, 1);


		// Simular retraso
		// write(1, &c, 1);
		usleep(500000); // 500 ms
	}
}

void	save_info(t_tx *tx, int i, int j)
{
	while (i < tx->y)
	{
		j = 0;
		while (j < tx->x)
		{
			if (i == 0 || i == (tx->y - 1))
			{
				tx->matx[i][j] = '_';
				write(1, "_", 1);
			}
			else if (j == 0 || j == (tx->x - 1))
			{
				tx->matx[i][j] = '|';
				write(1, "|", 1);
			}
			else
			{
				tx->matx[i][j] = ' ';
				write(1, " ", 1);
			}
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

void	init_mtx(char **mtx)
{
	int	i;

	i = 0;
	while (mtx[i])
	{
		mtx[i] = malloc(20 * sizeof(char));
		i++;
	}
}

void	ft_tx()
{
	t_tx	*tx;
	int		i;
	int		j;

	tx = malloc(sizeof(t_tx));
	tx->y = 25;
	tx->x = 20;
	tx->matx = malloc(25 * sizeof(char *));
	init_mtx(tx->matx);
	i = 0;
	j = 0;
	save_info(tx, i, j);
	game_loop(tx, i, j);
}
