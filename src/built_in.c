/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:07:10 by jramos-a          #+#    #+#             */
/*   Updated: 2025/05/02 12:15:33 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	exec_echo(char **args, char **envp)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (args[1] && ft_strncmp(args[1], "-n", 3) == 0)
	{
		newline = 0;
		i = 2;
	}
	while (args[i])
	{
		if (echo_var(args, envp))
			return (write(1, "\n", 1), 1);
		// else if (echo_signal(args, envp))
		// 	printf("!\n");
		else
		{
			write(1, args[i], ft_strlen(args[i]));
			if (args[i + 1])
				write(1, " ", 1);
		}
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (1);
}

int	exec_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
	return (1);
}

int exec_cd(char **args, t_sh *sh)
{
	char *tmp;
	char *new_prompt;
	char *cwd;

	if (!args[1])
	{
		write(1, "cd: error\n", 11);
		return (0);
	}
	if (chdir(args[1]) != 0)
		return (0);
	if (sh->prompt)
		free(sh->prompt);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (0);
	new_prompt = ft_strdup("\033[44;97m@CRIPTO$HELL\033[0m \033[38;5;82m");
	tmp = new_prompt;
	new_prompt = ft_strjoin(new_prompt, "-");
	free(tmp);
	tmp = new_prompt;
	new_prompt = ft_strjoin(new_prompt, cwd);
	free(tmp);
	free(cwd);
	tmp = new_prompt;
	new_prompt = ft_strjoin(new_prompt, " ~ \033[0;0m");
	free(tmp);
	sh->prompt = new_prompt;
	return (1);
}

int	exec_exit(void)
{
	write(1, "exit\n", 5);
	exit(0);
	return (1);
}
