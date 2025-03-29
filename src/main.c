/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:46:10 by jramos-a          #+#    #+#             */
/*   Updated: 2025/03/26 10:46:10 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

#include <stdio.h>
#include <stdlib.h>
// #include <readline/readline.h>

void base_error(void);

int main()
{
	char *line;

	while (1)
	{
		line = readline("AM33< ");
		if (!line)
		{
			base_error();
			break;
		}
		printf("%s\n", line);
		free(line);
	}
	return (0);
}


/*

manual de bash
https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html

automata para parseo



*/