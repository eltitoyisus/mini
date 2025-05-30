/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:07:08 by jramos-a          #+#    #+#             */
/*   Updated: 2025/05/30 16:19:05 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int is_builtin(char *command)
{
	if (!command)
		return 0;
	int result = (ft_strncmp(command, "cd", 3) == 0 ||
				ft_strncmp(command, "echo", 5) == 0 ||
				ft_strncmp(command, "pwd", 4) == 0 ||
				ft_strncmp(command, "exit", 5) == 0 ||
				ft_strncmp(command, "env", 4) == 0 ||
				ft_strncmp(command, "export", 7) == 0 ||
				ft_strncmp(command, "unset", 6) == 0);
	printf("Command '%s' is %sa builtin\n", command, result ? "" : "not ");
	return result;
}

int exec_builtin(char **args, char **envp, t_sh *sh)
{
	printf("Executing built-in: %s\n", args[0]);
	for (int i = 0; args[i]; i++)
		printf("Arg %d: [%s]\n", i, args[i]);
	if (!args || !args[0])
		return 0;
	if (ft_strncmp(args[0], "echo", 5) == 0)
		return exec_echo(args, envp);
	else if (ft_strncmp(args[0], "pwd", 4) == 0)
		return exec_pwd();
	else if (ft_strncmp(args[0], "exit", 5) == 0)
		return exec_exit();
	else if (ft_strncmp(args[0], "cd", 3) == 0)
		return exec_cd(args, sh);
	else if (ft_strncmp(args[0], "env", 4) == 0)
		return exec_env(envp);
	else if (ft_strncmp(args[0], "export", 7) == 0)
		return env_export(args, envp);
	else if (ft_strncmp(args[0], "unset", 6) == 0)
		return env_unset(args, envp);

	return 0;
}

int exec_builtin_with_redirs(char **args, char **envp, t_sh *sh, t_reds *redirs)
{
    int result;
    int stdin_backup = -1;
    int stdout_backup = -1;
    int stdin_fd = -1;
    int stdout_fd = -1;
    t_reds *current;

    if (redirs)
    {
        current = redirs;
        while (current)
        {
            if (current->type == INRED || current->type == HEREDOC) {
                stdin_fd = current->fd;
                if (stdin_fd == -1) {
                    printf("Error: invalid stdin redirection fd\n");
                    return 1;
                }
            }
            else if (current->type == OURED || current->type == D_OURED) {
                stdout_fd = current->fd;
                if (stdout_fd == -1) {
                    printf("Error: invalid stdout redirection fd\n");
                    return 1;
                }
            }
            current = current->next;
        }
        
        if (stdin_fd != -1)
            stdin_backup = dup(STDIN_FILENO);
        if (stdout_fd != -1)
            stdout_backup = dup(STDOUT_FILENO);
        
        if (stdin_fd != -1 && stdin_backup != -1)
            dup2(stdin_fd, STDIN_FILENO);
        if (stdout_fd != -1 && stdout_backup != -1)
            dup2(stdout_fd, STDOUT_FILENO);
    }
    
    result = exec_builtin(args, envp, sh);
    
    if (stdin_fd != -1 && stdin_backup != -1)
    {
        dup2(stdin_backup, STDIN_FILENO);
        close(stdin_backup);
    }
    if (stdout_fd != -1 && stdout_backup != -1)
    {
        dup2(stdout_backup, STDOUT_FILENO);
        close(stdout_backup);
    }
    
    return (result);
}
