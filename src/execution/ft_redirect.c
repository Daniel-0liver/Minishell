/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:54:51 by gateixei          #+#    #+#             */
/*   Updated: 2023/06/12 11:45:35 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_red(void)
{
	int pid;
	int tmp_cmd;
	int tmp_spc;
	int tmp_fd;

	tmp_cmd = data()->curr_cmd + 1;
	tmp_spc = data()->curr_spc + 1;
	while (data()->test[data()->spc[data()->curr_spc]][0] == '>' && data()->test[data()->spc[tmp_spc]][0] == '>')
	{
		tmp_fd = open(data()->cmds[tmp_cmd][0], O_RDWR | O_CREAT | O_TRUNC, 0664);
		if (tmp_fd < 0)
			printf("Error to create/read the redirected file named: %s\n", data()->cmds[tmp_cmd][0]);
		close(tmp_fd);
		tmp_cmd++;
		tmp_spc++;
	}
	data()->fd[data()->curr_fd][1] = open(data()->cmds[tmp_cmd][0], O_RDWR | O_CREAT | O_TRUNC, 0664);
		if (data()->fd[data()->curr_fd][1] < 0)
			printf("Error to create/read the redirected file named: %s\n", data()->cmds[tmp_cmd][0]);
	ft_exec();
	data()->curr_cmd = tmp_cmd;
	data()->curr_spc = tmp_spc;
	data()->curr_fd++;
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