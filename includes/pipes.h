/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:25:05 by jramos-a          #+#    #+#             */
/*   Updated: 2025/03/26 11:25:05 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

#include "../includes/main.h"

void do_pipe(int *fd, int *fd2);
void do_here_doc(char *str);
void do_redir(char *file, int flags);
void do_signals(void);


#endif