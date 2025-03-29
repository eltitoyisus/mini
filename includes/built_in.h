/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:08:41 by jramos-a          #+#    #+#             */
/*   Updated: 2025/03/29 12:09:22 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H
# include "headers.h"
# include "main.h"

int	exec_echo(char **args);
int	exec_pwd(void);
int	exec_env(char **envp);
int	exec_exit(void);
int	is_builtin(char *command);
int	exec_builtin(char **args, char **envp);

#endif
