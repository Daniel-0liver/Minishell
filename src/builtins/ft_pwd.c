/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:40:09 by gateixei          #+#    #+#             */
/*   Updated: 2023/06/13 15:22:12 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_pwd(char **str)
{
	int	pid;
    char dir[1024];
    
    getcwd(dir, (sizeof(char) * 1024));
	pid = fork();
	if (pid == 0)
	{	
		close(data()->fd[data()->curr_fd][0]);
		dup2(data()->fd[data()->curr_fd][1], STDOUT_FILENO);
        printf("%s\n", dir);
		exit(0);
	}
	else
	{	
		close(data()->fd[data()->curr_fd][1]);
		waitpid(pid, NULL, 0);
	}
}

void    ft_pwd_exec(char **str)
{
    char dir[1024];
    
    getcwd(dir, (sizeof(char) * 1024));
    printf("%s\n", dir);
}