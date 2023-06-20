/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:16:32 by gateixei          #+#    #+#             */
/*   Updated: 2023/06/20 19:41:31 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Change all data()->test for the real string received by the parse

void	exec_type_end(void)
{
	if (data()->spc[data()->curr_spc] == '\0')
	{
		if (is_exec(data()->test[data()->spc[data()->curr_spc - 1]]) == 1)
			ft_exec_pipe_end();
		else	
			return ;
	}
	else if (is_redirect(data()->test[data()->spc[data()->curr_spc]]) == 1)
		ft_red_end();
	else if (is_exec(data()->test[data()->spc[data()->curr_spc]]) == 1)
		ft_exec_pipe_end();
	else
		printf("2Not pipe or >\n");
}

void	exec_type_md(void)
{
	if (is_exec(data()->test[data()->spc[data()->curr_spc]]) == 1)
		ft_exec_pipe_md();
	else if (is_redirect(data()->test[data()->spc[data()->curr_spc]]) == 1)
		ft_red_end();
	else
		printf("Not pipe or >\n");
}

void    exec_type(void)
{
	if (is_exec(data()->test[data()->spc[data()->curr_spc]]) == 1)
		ft_exec();
	else if (is_redirect(data()->test[data()->spc[data()->curr_spc]]) == 1)
		ft_red();
	else if (is_redirect(data()->test[data()->spc[data()->curr_spc]]) == 3)
		ft_input();
}

void	check_spc(void)
{
	generate_fds();
	exec_type();
	while (data()->spc && data()->spc[data()->curr_spc] != '\0' && data()->spc[data()->curr_spc] != '\0')
		exec_type_md();
	exec_type_end();
}

void cmd_to_exec(void) // Main Fuction
{  
	data()->test = ft_split(data()->str_cmd, ' '); //erase this later -> Change all data()->test for the real string received by the parse
	int		pid;

	data()->cmds = get_cmds();
	data()->curr_cmd = 0;
	data()->curr_spc = 0;
	data()->curr_fd = 0;
	// for (int k = 0; data()->cmds[k] != NULL; k++)
	//     for (int f = 0; data()->cmds[k][f] != NULL; f++)
	//         printf("Matriz: %d, Array: %d, String: %s\n", k, f, data()->cmds[k][f]);
	// return ;
	if (data()->spc && data()->spc[data()->curr_spc] != '\0')
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

// Check echo > vs echo ">"
// Handle spc when they're toguether with the exec