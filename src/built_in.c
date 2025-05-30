/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:07:10 by jramos-a          #+#    #+#             */
/*   Updated: 2025/05/30 15:57:42 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void ft_itoa_into(int n, char *str)
{
    long int num;
    int i = 0;
    int sign = 0;
    int len = 0;
    
    num = n;
    if (num < 0)
    {
        sign = 1;
        num = -num;
        str[i++] = '-';
    }
    else if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }
    
    // Count digits
    long int temp = num;
    while (temp > 0)
    {
        temp /= 10;
        len++;
    }
    
    // Place digits in reverse order
    i = len + sign - 1;
    str[len + sign] = '\0';
    while (num > 0)
    {
        str[i--] = (num % 10) + '0';
        num /= 10;
    }
}

int exec_cd(char **args, t_sh *sh)
{
	char *dir;
	char *old_pwd;
	char *new_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return 1;

	if (!args[1] || ft_strncmp(args[1], "~", 2) == 0)
	{
		dir = getenv("HOME");
		if (!dir)
		{
			printf("cd: HOME not set\n");
			free(old_pwd);
			return 1;
		}
	}
	else
		dir = args[1];

	if (chdir(dir) != 0)
	{
		printf("cd: %s: No such file or directory\n", dir);
		free(old_pwd);
		return 1;
	}

	if (sh)
	{
		new_pwd = getcwd(NULL, 0);
		if (new_pwd)
		{
			if (sh->pwd)
				free(sh->pwd);
			sh->pwd = new_pwd;
		}
	}
	free(old_pwd);
	return 0;
}

int exec_pwd(void)
{
	char cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
}

int exec_exit(void)
{
	exit(0);
}

int exec_echo(char **args, char **envp)
{
	int i;
	int n_flag;
	char exit_status[12];

	(void)envp;
	i = 1;
	n_flag = 0;
	if (args[1] && ft_strncmp(args[1], "-n", 3) == 0)
	{
		n_flag = 1;
		i++;
	}
	while (args[i])
	{
		if (ft_strncmp(args[i], "$?", 2) == 0)
		{
			int status = last_signal_code(-1);
			ft_itoa_into(status, exit_status);
			printf("%s", exit_status);
		}
		else if (args[i][0] == '$')
		{
			if (!echo_var(args, i, envp))
				printf("%s", args[i]);
		}
		else
		{
			printf("%s", args[i]);
		}
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
	return 0;
}
