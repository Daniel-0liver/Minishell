/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:12:11 by gateixei          #+#    #+#             */
/*   Updated: 2023/07/27 19:02:49 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo(char **str, int flag)
{
	int	i;

	if (flag == 1)
		i = 2;
	else
		i = 1;
	while (str[i] != NULL)
	{
		printf("%s", str[i]);
		i++;
	}
	if (flag != 1)
		printf("\n");
}

void	ft_echo_beg(char **str, int flag)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(data()->fd[0][1], STDOUT_FILENO);
		print_echo(str, flag);
		swap_fd();
		swap_fd();
		exit(0);
	}
	else
	{
		waitpid(pid, NULL, 0);
		swap_fd();
	}
}

void	ft_echo(char **str)
{
	if (str[1] && my_strcmp(str[1], "-n") && str[2] != NULL)
		ft_echo_beg(str, 1);
	else if (str[1] != NULL)
		ft_echo_beg(str, 0);
	data()->error = 0;
}
