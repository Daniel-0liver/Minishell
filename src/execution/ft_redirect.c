/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:54:51 by gateixei          #+#    #+#             */
/*   Updated: 2023/07/26 22:16:37 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void	ft_red(void)
{
	int	tmp_cmd;

	tmp_cmd = ft_red_loop_checker(data()->curr_cmd + 1);
	if (!(access(data()->cmds[tmp_cmd][0], W_OK) == 0))
	{
		if (errno == EACCES)
		{
			redirection_error(tmp_cmd);
			return ;
		}
	}
	if (is_redirect(data()->tokens[data()->spc[tmp_cmd - 1]]) == 1)
		(data()->fd[data()->curr_fd][1]) = open(data()->cmds[tmp_cmd][0], \
		O_RDWR | O_CREAT | O_TRUNC, 0664);
	else if (is_redirect(data()->tokens[data()->spc[tmp_cmd - 1]]) == 2)
		(data()->fd[data()->curr_fd][1]) = open(data()->cmds[tmp_cmd][0], \
		O_RDWR | O_CREAT | O_APPEND, 0664);
	if (data()->fd[data()->curr_fd][1] < 0)
		printf("Error to create/read the redirected file named: %s\n", \
		data()->cmds[tmp_cmd][0]);
	ft_exec();
	data()->curr_cmd = tmp_cmd;
}

void	ft_red_end(void)
{
	int	tmp_cmd;

	tmp_cmd = ft_red_loop_checker(data()->curr_cmd + 1);
	if (!(access(data()->cmds[tmp_cmd][0], W_OK) == 0))
	{
		if (errno == EACCES)
		{
			redirection_error(tmp_cmd);
			return ;
		}
	}
	if (is_redirect(data()->tokens[data()->spc[tmp_cmd - 1]]) == 1)
		(data()->fd[data()->curr_fd + 1][1]) = open(data()->cmds[tmp_cmd][0], \
		O_RDWR | O_CREAT | O_TRUNC, 0664);
	else if (is_redirect(data()->tokens[data()->spc[tmp_cmd - 1]]) == 2)
		(data()->fd[data()->curr_fd + 1][1]) = open(data()->cmds[tmp_cmd][0], \
		O_RDWR | O_CREAT | O_APPEND, 0664);
	if (data()->fd[data()->curr_fd][1] < 0)
		printf("Error to create/read the redirected file named: %s\n", \
		data()->cmds[tmp_cmd][0]);
	ft_exec_pipe_md();
	data()->curr_cmd = tmp_cmd;
}

*/