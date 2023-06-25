/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:32:19 by gateixei          #+#    #+#             */
/*   Updated: 2023/06/21 15:43:18 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_input(void)
{
	int tmp_cmd;
	int tmp_fd;

	tmp_cmd = data()->curr_cmd + 1;
	while (data()->test[data()->spc[data()->curr_cmd]][0] == '<' && data()->test[data()->spc[tmp_cmd]][0] == '<')
	{
		tmp_fd = open(data()->cmds[tmp_cmd][0], O_RDONLY);
		if (tmp_fd < 0)
			printf("Error to create/read the redirected file named: %s\n", data()->cmds[tmp_cmd][0]);
		close(tmp_fd);
		tmp_cmd++;
	}
	data()->fd[data()->curr_fd][0] = open(data()->cmds[tmp_cmd][0], O_RDONLY);
		if (data()->fd[data()->curr_fd][0] < 0)
			printf("Error to create/read the redirected file named: %s\n", data()->cmds[tmp_cmd][0]);
	if (data()->spc && data()->spc[data()->curr_cmd] != '\0' && data()->spc[data()->curr_cmd + 1] != '\0')
	{
		ft_exec_pipe_md();
		tmp_cmd++;
	}
	else
		ft_exec_pipe_end();
	data()->curr_cmd = tmp_cmd;
}
