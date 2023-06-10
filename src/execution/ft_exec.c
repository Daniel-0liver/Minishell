/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:10:00 by gateixei          #+#    #+#             */
/*   Updated: 2023/06/10 20:20:16 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(void)
{
	int pid;

    if (is_builtins(data()->cmds[data()->curr_cmd][0]))
    {
        call_builtins(data()->cmds[data()->curr_cmd]);
        data()->curr_cmd++;
        return ;
    }
	pid = fork();
	if (pid == 0)
	{
		close(data()->fd[data()->curr_fd][0]);
		dup2(data()->fd[data()->curr_fd][1], STDOUT_FILENO);
		execve(data()->cmds[data()->curr_cmd][0], data()->cmds[data()->curr_cmd], NULL);
	}
	else
	{
		close(data()->fd[data()->curr_fd][1]);
		waitpid(pid, NULL, 0);
		data()->curr_cmd++;
	}
}

void	ft_exec_pipe_md(void)
{
	int pid;
	
    if (is_builtins(data()->cmds[data()->curr_cmd][0]))
    {
        call_builtins(data()->cmds[data()->curr_cmd]);
        data()->curr_cmd++;
        return ;
    }
	pid = fork();
	if (pid == 0)
	{
		dup2(data()->fd[data()->curr_fd][0], STDIN_FILENO);
		dup2(data()->fd[data()->curr_fd + 1][1], STDOUT_FILENO);
		execve(data()->cmds[data()->curr_cmd][0], data()->cmds[data()->curr_cmd], NULL);
	}
	else
	{
		close(data()->fd[data()->curr_fd + 1][1]);
		close(data()->fd[data()->curr_fd][0]);
		waitpid(pid, NULL, 0);
        data()->curr_cmd++;
		data()->curr_spc++;
		data()->curr_fd++;
	}
}

void	ft_exec_pipe_end(void)
{
	int pid;

    if (is_builtins(data()->cmds[data()->curr_cmd][0]))
    {
        call_builtins(data()->cmds[data()->curr_cmd]);
        data()->curr_cmd++;
        return ;
    }
	pid = fork();
	if (pid == 0)
	{
		dup2(data()->fd[data()->curr_fd][0], STDIN_FILENO);
		execve(data()->cmds[data()->curr_cmd][0], data()->cmds[data()->curr_cmd], NULL);
	}
	else
    {
		close(data()->fd[data()->curr_fd][0]);
		waitpid(pid, NULL, 0);
    }
}