/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:16:32 by gateixei          #+#    #+#             */
/*   Updated: 2023/07/18 19:15:33 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_type_end(void)
{
	if (is_exec(data()->tokens[data()->spc[data()->curr_cmd - 1]]) \
	&& data()->spc[data()->curr_cmd] == -1)
		ft_exec_pipe_end();
	else if (data()->spc[data()->curr_cmd] != -1 && \
	is_redirect(data()->tokens[data()->spc[data()->curr_cmd]]) == 1)
		ft_red_end();
	else if (data()->spc[data()->curr_cmd] != -1 && \
	is_redirect(data()->tokens[data()->spc[data()->curr_cmd]]) == 2)
		ft_red_end();
}

void	exec_type_md(void)
{
	if (is_exec(data()->tokens[data()->spc[data()->curr_cmd]]) == 1)
		ft_exec_pipe_md();
	else if (is_redirect(data()->tokens[data()->spc[data()->curr_cmd]]) == 1)
		ft_red_end();
	else if (is_redirect(data()->tokens[data()->spc[data()->curr_cmd]]) == 2)
		ft_red_end();
}

void	exec_type(void)
{
	if (is_exec(data()->tokens[data()->spc[data()->curr_cmd]]) == 1)
		ft_exec();
	else if (is_redirect(data()->tokens[data()->spc[data()->curr_cmd]]) == 1)
		ft_red();
	else if (is_redirect(data()->tokens[data()->spc[data()->curr_cmd]]) == 2)
		ft_red();
	else if (is_redirect(data()->tokens[data()->spc[data()->curr_cmd]]) == 3)
		ft_input();
	else if (is_redirect(data()->tokens[data()->spc[data()->curr_cmd]]) == 4)
		ft_input();
}

void	check_spc(void)
{
	generate_fds();
	exec_type();
	while (data()->spc && data()->spc[data()->curr_cmd] != -1)
	{
		if (data()->error != 0)
			return ;
		exec_type_md();
	}
	if (data()->error != 0)
	{
		return ;
	}
	exec_type_end();
}

void	cmd_to_exec(void)
{
	if (is_valid())
		return ;
	data()->cmds = get_cmds();
	data()->curr_cmd = 0;
	data()->curr_fd = 0;
	// for (int i = 0; data()->cmds[i] != NULL; i++)
	// 	for (int j = 0; data()->cmds[i][j] != NULL; j++)
	// 		printf("CMDS: Matriz %i Array %i %s\n", i, j, data()->cmds[i][j]);
	// for (int k = 0; data()->spc && data()->spc[k] != -1; k++)
	// 	printf("SPC INDEX: %i\n", data()->spc[k]);
	// return ;
	if (data()->spc && data()->spc[data()->curr_cmd] != -1)
	{
		check_spc();
		free_all();
	}
	else
		cmd_exec(0, 0);
}
