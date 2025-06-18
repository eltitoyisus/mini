/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:01:42 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/18 11:53:35 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADERS_H
# define HEADERS_H

# include "../libft/libft.h"
# include "main.h"
// COLORS
# define COLOR "\033[1;32m"
# define RESET "\033[0m"
# define WIDTH 20
# define HEIGHT 10
# define UP 0
# define DOWN 1
# define LEFT 2
# define RIGHT 3
// readline
# include <readline/history.h>
# include <readline/readline.h>
// other libraries
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <time.h>
# include <unistd.h>

#endif
