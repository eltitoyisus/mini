/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:07:10 by jramos-a          #+#    #+#             */
/*   Updated: 2025/05/23 08:55:44 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	exec_echo(char **args, char **envp)
{
	int		i;
	int		newline;
	int		fd;
	char	buffer[4096];
	ssize_t	bytes_read;

	i = 1;
	newline = 1;
	if (args[1] && ft_strncmp(args[1], "-n", 3) == 0)
	{
		newline = 0;
		i = 2;
	}
	while (args[i])
	{
		if (ft_strncmp(args[i], "<", 2) == 0 && args[i + 1])
		{
			// Read from file
			fd = open(args[i + 1], O_RDONLY);
			if (fd < 0)
			{
				write(2, "echo: ", 6);
				write(2, args[i + 1], ft_strlen(args[i + 1]));
				write(2, ": No such file or directory\n", 28);
				return (0);
			}
			while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
			{
				buffer[bytes_read] = '\0';
				write(1, buffer, bytes_read);
			}
			close(fd);
			i += 2;
			continue ;
		}
		else if (args[i][0] == '$')
		{
			if (echo_var(args, i, envp) == 0)
				write(1, args[i], ft_strlen(args[i]));
		}
		else
		{
			write(1, args[i], ft_strlen(args[i]));
		}
		if (args[i + 1] && ft_strncmp(args[i + 1], "<", 2) != 0)
			write(1, " ", 1);
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

int	exec_cd(char **args, t_sh *sh)
{
	if (!args[1])
	{
		write(1, "cd: error\n", 11);
		return (0);
	}
	if (chdir(args[1]) != 0)
		return (0);
	sh->prompt = "\033[44;97m@MINISHELL\033[0m \033[38;5;82m";
	sh->prompt = ft_strjoin(sh->prompt, "-");
	sh->prompt = ft_strjoin(sh->prompt, getcwd(NULL, 0));
	sh->prompt = ft_strjoin(sh->prompt, " ~ \033[0;0m");
	return (1);
}

int	exec_exit(void)
{
	write(1, "exit\n", 5);
	exit(0); // change for SIGQUIT
	return (1);
}
