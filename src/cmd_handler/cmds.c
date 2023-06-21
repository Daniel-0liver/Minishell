/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:16:32 by gateixei          #+#    #+#             */
/*   Updated: 2023/06/21 15:42:05 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Change all data()->tokens for the real string received by the parse

void	exec_type_end(void)
{
	if (is_exec(data()->test[data()->spc[data()->curr_cmd - 1]]) && data()->spc[data()->curr_cmd] == '\0')
		ft_exec_pipe_end();
	else if (is_redirect(data()->test[data()->spc[data()->curr_cmd]]) == 1)
		ft_red_end();
	else if (is_redirect(data()->test[data()->spc[data()->curr_cmd]]) == 2)
		ft_red_end();
}

void	exec_type_md(void)
{
	if (is_exec(data()->test[data()->spc[data()->curr_cmd]]) == 1)
			ft_exec_pipe_md();
	else if (is_redirect(data()->test[data()->spc[data()->curr_cmd]]) == 1)
		ft_red_end();
	else if (is_redirect(data()->test[data()->spc[data()->curr_cmd]]) == 2)
		ft_red_end();
}

void    exec_type(void)
{
	if (is_exec(data()->test[data()->spc[data()->curr_cmd]]) == 1)
		ft_exec();
	else if (is_redirect(data()->test[data()->spc[data()->curr_cmd]]) == 1)
		ft_red();
	else if (is_redirect(data()->test[data()->spc[data()->curr_cmd]]) == 2)
		ft_red();
	else if (is_redirect(data()->test[data()->spc[data()->curr_cmd]]) == 3)
		ft_input();
}

void	check_spc(void)
{
	generate_fds();
	exec_type();
	while (data()->spc && data()->spc[data()->curr_cmd] != '\0' && data()->spc[data()->curr_cmd] != '\0')
		exec_type_md();
	exec_type_end();
}
// ls -la | grep gateixei | grep gateixei | grep Makefile > output > output2 > output3
// cat < output4 | grep Makefile > output5

void cmd_to_exec(void) // Main Fuction
{
	int		pid;

	data()->cmds = get_cmds();
	data()->curr_cmd = 0;
	data()->curr_fd = 0;
	// for (int k = 0; data()->cmds[k] != NULL; k++)
	//     for (int f = 0; data()->cmds[k][f] != NULL; f++)
	//         printf("Matriz: %d, Array: %d, String: %s\n", k, f, data()->cmds[k][f]);
	// return ;
	if (data()->spc && data()->spc[data()->curr_cmd] != '\0')
	{
		check_spc();
		free_all();
	}
	else
	{
		if (is_builtins(data()->cmds[data()->curr_cmd][0]))
			call_builtins_exec(data()->cmds[data()->curr_cmd]);
		else
		{
			pid = fork();
			if (pid == 0)
				execve(data()->cmds[data()->curr_cmd][0], data()->cmds[data()->curr_cmd], data()->env_p);
			else
				waitpid(pid, NULL, 0);
		}
		free_exec();
	}
}
