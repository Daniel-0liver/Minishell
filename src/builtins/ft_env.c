/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:43:08 by gateixei          #+#    #+#             */
/*   Updated: 2023/06/14 14:41:06 by gateixei         ###   ########.fr       */
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
        while (data()->env_p && data()->env_p[i] != NULL)
            printf("%s\n", data()->env_p[i++]);
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
    while (data()->env_p && data()->env_p[i] != NULL)
        printf("%s\n", data()->env_p[i++]);
}
