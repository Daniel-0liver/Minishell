/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:10:00 by gateixei          #+#    #+#             */
/*   Updated: 2023/06/20 23:27:29 by gateixei         ###   ########.fr       */
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
		data()->curr_spc++;
        return ;
    }
	pid = fork();
	if (pid == 0)
	{
		close(data()->fd[data()->curr_fd][0]);
		dup2(data()->fd[data()->curr_fd][1], STDOUT_FILENO);
		if (execve(data()->cmds[data()->curr_cmd][0], data()->cmds[data()->curr_cmd],  data()->env_p) == -1)
            free_all();
	}
	else
	{
		close(data()->fd[data()->curr_fd][1]);
		waitpid(pid, NULL, 0);
		data()->curr_cmd++;
		data()->curr_spc++;
	}
}

void	    ft_exec_pipe_md(void)
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
		execve(data()->cmds[data()->curr_cmd][0], data()->cmds[data()->curr_cmd], data()->env_p);
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
		execve(data()->cmds[data()->curr_cmd][0], data()->cmds[data()->curr_cmd], data()->env_p);
	}
	else
    {
		close(data()->fd[data()->curr_fd][0]);
		waitpid(pid, NULL, 0);
    }
}