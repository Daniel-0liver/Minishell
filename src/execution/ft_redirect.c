/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:54:51 by gateixei          #+#    #+#             */
/*   Updated: 2023/06/21 18:34:36 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_red(void)
{
	int tmp_cmd;
	int tmp_fd;

	tmp_cmd = data()->curr_cmd + 1;
	while (data()->tokens[data()->spc[tmp_cmd]] && data()->tokens[data()->spc[data()->curr_cmd]][0] == '>' && data()->tokens[data()->spc[tmp_cmd]][0] == '>')
	{
        if (is_redirect(data()->tokens[data()->spc[tmp_cmd - 1]]) == 1)
		    tmp_fd = open(data()->cmds[tmp_cmd][0], O_RDWR | O_CREAT | O_TRUNC, 0664);
        else if (is_redirect(data()->tokens[data()->spc[tmp_cmd - 1]]) == 2)
		    tmp_fd = open(data()->cmds[tmp_cmd][0], O_RDWR | O_CREAT | O_APPEND, 0664);
		if (tmp_fd < 0)
			printf("Error to create/read the redirected file named: %s\n", data()->cmds[tmp_cmd][0]);
		close(tmp_fd);
		tmp_cmd++;
	}
    if (is_redirect(data()->tokens[data()->spc[tmp_cmd - 1]]) == 1)
	    data()->fd[data()->curr_fd][1] = open(data()->cmds[tmp_cmd][0], O_RDWR | O_CREAT | O_TRUNC, 0664);
    else if (is_redirect(data()->tokens[data()->spc[tmp_cmd - 1]]) == 2)
	    data()->fd[data()->curr_fd][1] = open(data()->cmds[tmp_cmd][0], O_RDWR | O_CREAT | O_APPEND, 0664);
	if (data()->fd[data()->curr_fd][1] < 0)
			printf("Error to create/read the redirected file named: %s\n", data()->cmds[tmp_cmd][0]);
	ft_exec();
	data()->curr_cmd = tmp_cmd;
}

void	ft_red_end(void)
{
	int tmp_cmd;
	int tmp_fd;

	tmp_cmd = data()->curr_cmd + 1;
	while (data()->tokens[data()->spc[tmp_cmd]] && data()->tokens[data()->spc[data()->curr_cmd]][0] == '>' && data()->tokens[data()->spc[tmp_cmd]][0] == '>')
	{
        if (is_redirect(data()->tokens[data()->spc[tmp_cmd - 1]]) == 1)
		    tmp_fd = open(data()->cmds[tmp_cmd][0], O_RDWR | O_CREAT | O_TRUNC, 0664);
        else if (is_redirect(data()->tokens[data()->spc[tmp_cmd - 1]]) == 2)
		    tmp_fd = open(data()->cmds[tmp_cmd][0], O_RDWR | O_CREAT | O_APPEND, 0664);
		if (tmp_fd < 0)
			printf("Error to create/read the redirected file named: %s\n", data()->cmds[tmp_cmd][0]);
		close(tmp_fd);
		tmp_cmd++;
	}
    if (is_redirect(data()->tokens[data()->spc[tmp_cmd - 1]]) == 1)
	    data()->fd[data()->curr_fd + 1][1] = open(data()->cmds[tmp_cmd][0], O_RDWR | O_CREAT | O_TRUNC, 0664);
    else if (is_redirect(data()->tokens[data()->spc[tmp_cmd - 1]]) == 2)
	    data()->fd[data()->curr_fd + 1][1] = open(data()->cmds[tmp_cmd][0], O_RDWR | O_CREAT | O_APPEND, 0664);
	if (data()->fd[data()->curr_fd][1] < 0)
		printf("Error to create/read the redirected file named: %s\n", data()->cmds[tmp_cmd][0]);
	ft_exec_pipe_md();
	data()->curr_cmd = tmp_cmd;
}
