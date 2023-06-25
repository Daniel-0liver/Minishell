/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:43:08 by gateixei          #+#    #+#             */
/*   Updated: 2023/06/19 14:02:55 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_env(char **str)
{
	int	pid;
    int i;

    i = 0;
	pid = fork();
	if (pid == 0)
	{	
		close(data()->fd[data()->curr_fd][0]);
		dup2(data()->fd[data()->curr_fd][1], STDOUT_FILENO);
        while (str && str[i] != NULL)
            printf("%s\n", str[i++]);
		exit(0);
	}
	else
	{	
		close(data()->fd[data()->curr_fd][1]);
		waitpid(pid, NULL, 0);
	}
}

void    ft_env_exec(char **str)
{
    int i;

    i = 0;
    while (str && str[i] != NULL)
        printf("%s\n", str[i++]);
}
