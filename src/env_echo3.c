/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_echo3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:22:40 by jramos-a          #+#    #+#             */
/*   Updated: 2025/06/19 18:22:40 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	handle_special_char(char **p)
{
	(*p)++;
}

void	handle_exit_status(char **p)
{
	print_exit_status();
	(*p) += 2;
}

int	get_var_name_length(char *var_name)
{
	int	var_len;

	var_len = 0;
	while (var_name[var_len] && (ft_isalnum(var_name[var_len])
			|| var_name[var_len] == '_'))
		var_len++;
	return (var_len);
}

int	find_env_var(char *var_name, int var_len, char **envp)
{
	int	j;

	j = 0;
	while (envp[j])
	{
		if (ft_strncmp(var_name, envp[j], var_len) == 0
			&& envp[j][var_len] == '=')
		{
			printf("%s", envp[j] + var_len + 1);
			return (j);
		}
		j++;
	}
	return (-1);
}

void	handle_env_var(char **p, char **envp)
{
	char	*var_name;
	int		var_len;
	char	original_char;

	var_name = *p + 1;
	var_len = get_var_name_length(var_name);
	original_char = var_name[var_len];
	var_name[var_len] = '\0';
	find_env_var(var_name, var_len, envp);
	var_name[var_len] = original_char;
	*p += var_len + 1;
}
