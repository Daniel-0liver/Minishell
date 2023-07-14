/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:12:11 by gateixei          #+#    #+#             */
/*   Updated: 2023/07/14 23:10:53 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo_beg(char **str, int flag)
{
	int	pid;
	int	i;

	pid = fork();
	if (pid == 0)
	{	
		close(data()->fd[data()->curr_fd][0]);
		dup2(data()->fd[data()->curr_fd][1], STDOUT_FILENO);
		if (flag == 1)
		{
			i = 2;
			while (str[i] != NULL)
			{
				printf("%s", str[i]);
				i++;
			}
		}
		else
		{
			i = 1;
			while (str[i] != NULL)
			{
				printf("%s", str[i]);
				i++;
			}
			printf("\n");
		}
		exit(0);
	}
	else
	{	
		close(data()->fd[data()->curr_fd][1]);
		waitpid(pid, NULL, 0);
	}
}

void	ft_echo(char **str)
{
	if (str[1] && ft_strcpm(str[1], "-n") && str[2] != NULL)
		ft_echo_beg(str, 1);
	else if (str[1] != NULL)
		ft_echo_beg(str, 0);
	data()->error = 0;
}

void	ft_echo_exec(char **str)
{
	int	i;

	if (str[1] && ft_strcpm(str[1], "-n") && str[2] != NULL)
	{
		i = 2;
		while (str[i] != NULL)
		{
			printf("%s", str[i]);
			i++;
		}
	}
	else if (str[1] != NULL)
	{
		i = 1;
		while (str[i] != NULL)
		{
			printf("%s", str[i]);
			i++;
		}
		printf("\n");
	}
	data()->error = 0;
}
