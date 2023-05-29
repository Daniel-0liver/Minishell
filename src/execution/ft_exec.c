/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:10:00 by gateixei          #+#    #+#             */
/*   Updated: 2023/05/29 19:01:09 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(void)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		close(data()->fd[0]);
		dup2(data()->fd[1], STDOUT_FILENO);
		execve(data()->cmds[data()->curr_cmd][0], data()->cmds[data()->curr_cmd], NULL);
		close(data()->fd[1]);
	}
	else
	{
		waitpid(pid, NULL, 0);
		data()->curr_cmd++;
	}
}

void	ft_exec_pipe_md(void)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(data()->fd[0], STDIN_FILENO);
		dup2(data()->fd[1], STDOUT_FILENO);
		execve(data()->cmds[data()->curr_cmd][0], data()->cmds[data()->curr_cmd], NULL);
		close(data()->fd[0]);
		close(data()->fd[1]);
	}
	else
		waitpid(pid, NULL, 0);
}

void	ft_exec_pipe_end(void)
{
		close(data()->fd[1]);
		dup2(data()->fd[0], STDIN_FILENO);
		execve(data()->cmds[data()->curr_cmd][0], data()->cmds[data()->curr_cmd], NULL);
		close(data()->fd[0]);
}