/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:32:19 by gateixei          #+#    #+#             */
/*   Updated: 2023/06/13 22:48:17 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_input(void) // Need to work on this
{
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

void	ft_input_end(void)
{
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
	data()->fd[data()->curr_fd + 1][1] = open(data()->cmds[tmp_cmd][0], O_RDWR | O_CREAT | O_TRUNC, 0664);
		if (data()->fd[data()->curr_fd][1] < 0)
			printf("Error to create/read the redirected file named: %s\n", data()->cmds[tmp_cmd][0]);
	ft_exec_pipe_md();
	data()->curr_cmd = tmp_cmd;
	data()->curr_spc = tmp_spc;
	data()->curr_fd++;
}