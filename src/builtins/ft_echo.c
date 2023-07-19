/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:12:11 by gateixei          #+#    #+#             */
/*   Updated: 2023/07/19 17:35:34 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_spc_char(char *str)
{
	if (ft_strcpm(str, "\">"))
		return (1);
	else if (ft_strcpm(str, "\">>"))
		return (1);
	else if (ft_strcpm(str, "\"<"))
		return (1);
	else if (ft_strcpm(str, "\"<<"))
		return (1);
	else if (ft_strcpm(str, "\"|"))
		return (1);
	return (0);
}

void	print_echo(char **str, int flag)
{
	int	i;

	if (flag == 1)
		i = 2;
	else
		i = 1;
	while (str[i] != NULL)
	{
		if (is_spc_char(str[i]))
			printf("%s", &str[i][1]);
		else
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
		close(data()->fd[data()->curr_fd][0]);
		dup2(data()->fd[data()->curr_fd][1], STDOUT_FILENO);
		print_echo(str, flag);
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

	if (str[1] && ft_strcpm(str[1], "-n") && str[2] != NULL)
		print_echo(str, 1);
	else if (str[1] != NULL)
		print_echo(str, 0);
	data()->error = 0;
}
