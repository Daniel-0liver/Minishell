/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:12:11 by gateixei          #+#    #+#             */
/*   Updated: 2023/08/02 17:18:16 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_flag(char *str)
{
	int	i;

	i = 0;
	if (str && str[i] == '-')
		i++;
	else
		return (0);
	while (str && str[i] != '\0')
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	print_echo(char **str, int flag)
{
	int	i;

	i = 1;
	if (flag == 1)
		i = 2;
	while (str[i] != NULL)
	{
		if (str[i + 1] == NULL && str[i][ft_strlen(str[i]) - 1] == ' ')
			str[i][ft_strlen(str[i]) - 1] = '\0';
		printf("%s", str[i]);
		i++;
	}
	if (flag != 1)
		printf("\n");
}

void	ft_echo_beg(char **str, int flag)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		if (data()->fd[0][0] < 0 || data()->fd[0][1] < 0)
			exit_child();
		dup2(data()->fd[0][1], STDOUT_FILENO);
		print_echo(str, flag);
		swap_fd();
		swap_fd();
		free_all();
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		data()->error = 0;
		if (status > 0)
			data()->error = status / 256;
	}
}

void	ft_echo(char **str)
{
	if (str[1] && is_flag(str[1]))
		ft_echo_beg(str, 1);
	else if (str[1] != NULL)
		ft_echo_beg(str, 0);
	else if (data()->cmds[data()->curr_cmd + 1] == NULL)
		printf("\n");
}
