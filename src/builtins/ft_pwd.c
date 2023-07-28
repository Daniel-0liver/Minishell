/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:40:09 by gateixei          #+#    #+#             */
/*   Updated: 2023/07/28 23:54:06 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(char **str)
{
	int		pid;
	char	dir[1024];

	(void) str;
	getcwd(dir, (sizeof(char) * 1024));
	pid = fork();
	if (pid == 0)
	{
		dup2(data()->fd[0][1], STDOUT_FILENO);
		printf("%s\n", dir);
		swap_fd();
		swap_fd();
		exit(0);
	}
	else
	{
		swap_fd();
		waitpid(pid, NULL, 0);
		data()->error = 0;
	}
}

void	ft_pwd_exec(char **str)
{
	char	dir[1024];

	(void) str;
	getcwd(dir, (sizeof(char) * 1024));
	printf("%s\n", dir);
	data()->error = 0;
}
