/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:10:00 by gateixei          #+#    #+#             */
/*   Updated: 2023/07/19 20:34:13 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_begin(void)
{
	close(data()->fd[data()->curr_fd][0]);
	if (data()->fd[data()->curr_fd][1] < 0)
		close(data()->fd[data()->curr_fd][1]);
	dup2(data()->fd[data()->curr_fd][1], STDOUT_FILENO);
	if (execve(data()->cmds[data()->curr_cmd][0], \
	data()->cmds[data()->curr_cmd], data()->env_p) == -1)
	{
		printf("%s: command not found\n", data()->cmds[data()->curr_cmd][0]);
		free_all();
		exit(127);
	}
}

void	exec_md(void)
{
	if (data()->fd[data()->curr_fd][0] < 0)
		close(data()->fd[data()->curr_fd][0]);
	if (data()->fd[data()->curr_fd + 1][1] < 0)
		close(data()->fd[data()->curr_fd + 1][1]);
	dup2(data()->fd[data()->curr_fd][0], STDIN_FILENO);
	dup2(data()->fd[data()->curr_fd + 1][1], STDOUT_FILENO);
	if (execve(data()->cmds[data()->curr_cmd][0], \
	data()->cmds[data()->curr_cmd], data()->env_p) == -1)
	{
		printf("%s: command not found\n", data()->cmds[data()->curr_cmd][0]);
		free_all();
		exit(127);
	}
}

void	ft_exec(void)
{
	int	pid;
	int	status;

	if (is_builtins(data()->cmds[data()->curr_cmd][0]))
	{
		call_builtins(data()->cmds[data()->curr_cmd]);
		data()->curr_cmd++;
		return ;
	}
	pid = fork();
	if (pid == 0)
		exec_begin();
	else
	{
		waitpid(pid, &status, 0);
		close(data()->fd[data()->curr_fd][1]);
		if (status > 0)
			data()->error = status / 256;
		else
			data()->error = 0;
		data()->curr_cmd++;
	}
}

void	ft_exec_pipe_md(void)
{
	int	pid;
	int	status;

	if (is_builtins(data()->cmds[data()->curr_cmd][0]))
	{
		call_builtins(data()->cmds[data()->curr_cmd]);
		data()->curr_cmd++;
		return ;
	}
	pid = fork();
	if (pid == 0)
		exec_md();
	else
	{
		waitpid(pid, &status, 0);
		close(data()->fd[data()->curr_fd + 1][1]);
		close(data()->fd[data()->curr_fd][0]);
		if (status > 0)
			data()->error = status / 256;
		else
			data()->error = 0;
		data()->curr_cmd++;
		data()->curr_fd++;
	}
}

void	ft_exec_pipe_end(void)
{
	int	pid;
	int	status;

	if (is_builtins(data()->cmds[data()->curr_cmd][0]))
	{
		call_builtins(data()->cmds[data()->curr_cmd]);
		data()->curr_cmd++;
		return ;
	}
	pid = fork();
	if (pid == 0)
		exec_end();
	else
	{
		waitpid(pid, &status, 0);
		close(data()->fd[data()->curr_fd][0]);
		if (status > 0)
			data()->error = status / 256;
		else
			data()->error = 0;
	}
}
