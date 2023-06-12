/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:54:51 by gateixei          #+#    #+#             */
/*   Updated: 2023/06/12 10:53:16 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_red(void)
{
	int pid;
    int tmp_fd[2];

	// if (is_builtins(data()->cmds[data()->curr_cmd][0]))
	// {
	//     call_builtins(data()->cmds[data()->curr_cmd]);
	//     data()->curr_cmd++;
	//     return ;
	// }
    
    data()->fd[data()->curr_fd][1] = open(data()->cmds[data()->curr_cmd + 1][0], O_RDWR | O_CREAT | O_TRUNC, 0664);
		if (data()->fd[data()->curr_fd][1] < 0)
			printf("Error to create/read the redirected file named: %s\n", data()->cmds[data()->curr_cmd][0]);
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
		data()->curr_spc++;
		data()->curr_fd++;
	}
}

// Edit accordingly

void	ft_red_md(void)
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

void	ft_red_end(void)
{
	int pid;

	// if (is_builtins(data()->cmds[data()->curr_cmd][0]))
	// {
	// 	call_builtins(data()->cmds[data()->curr_cmd]);
	// 	data()->curr_cmd++;
	// 	return ;
	// }
	data()->fd[data()->curr_fd][1] = open(data()->cmds[data()->curr_cmd + 1][0], O_RDWR | O_CREAT | O_TRUNC, 0664);
		if (data()->fd[data()->curr_fd][1] < 0)
			printf("Error to create/read the redirected file named: %s\n", data()->cmds[data()->curr_cmd][0]);
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