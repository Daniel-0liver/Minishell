/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:12:11 by gateixei          #+#    #+#             */
/*   Updated: 2023/06/14 17:18:46 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo_beg(char *str, int flag)
{
	int	pid;
	
	pid = fork();
	if (pid == 0)
	{	
		close(data()->fd[data()->curr_fd][0]);
		dup2(data()->fd[data()->curr_fd][1], STDOUT_FILENO);
		if (flag == 1)
			printf("%s", str);
		else
			printf("%s\n", str);
		exit(0);
	}
	else
	{	
		close(data()->fd[data()->curr_fd][1]);
		waitpid(pid, NULL, 0);
	}
}

void    ft_echo(char **str)
{
	if (ft_strcpm(str[1], "-n"))
		ft_echo_beg(str[2], 1);
	else
		ft_echo_beg(str[1], 0);
}

void    ft_echo_exec(char **str)
{
	if (ft_strcpm(str[1], "-n"))
		printf("%s", str[2]);
	else
		printf("%s\n", str[1]);
}