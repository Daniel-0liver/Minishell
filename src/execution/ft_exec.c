/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:10:00 by gateixei          #+#    #+#             */
/*   Updated: 2023/05/30 20:04:25 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(void)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		close(data()->fd[data()->curr_spc][0]);
		dup2(data()->fd[data()->curr_spc][1], STDOUT_FILENO);
		execve(data()->cmds[data()->curr_cmd][0], data()->cmds[data()->curr_cmd], NULL);
	}
	else
	{
		close(data()->fd[data()->curr_spc][1]);
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
		dup2(data()->fd[data()->curr_spc][0], STDIN_FILENO);
		dup2(data()->fd[data()->curr_spc + 1][1], STDOUT_FILENO);
		execve(data()->cmds[data()->curr_cmd][0], data()->cmds[data()->curr_cmd], NULL);
	}
	else
	{
		close(data()->fd[data()->curr_spc + 1][1]);
		close(data()->fd[data()->curr_spc][0]);
		waitpid(pid, NULL, 0);
        data()->curr_cmd++;
		data()->curr_spc++;
	}
}

void	ft_exec_pipe_end(void)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(data()->fd[data()->curr_spc][0], STDIN_FILENO);
		execve(data()->cmds[data()->curr_cmd][0], data()->cmds[data()->curr_cmd], NULL);
	}
	else
    {
		close(data()->fd[data()->curr_spc][0]);
		waitpid(pid, NULL, 0);
    }
}