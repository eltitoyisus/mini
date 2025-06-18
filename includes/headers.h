/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:01:42 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/18 02:42:00 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADERS_H
# define HEADERS_H

# include "../libft/libft.h"
# include "main.h"
// COLORS
# define COLOR "\033[1;32m"
# define RESET "\033[0m"
#define WIDTH 20
#define HEIGHT 10
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
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
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <time.h>


#endif
