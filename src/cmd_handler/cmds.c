/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:16:32 by gateixei          #+#    #+#             */
/*   Updated: 2023/06/12 11:39:17 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Change all data()->test for the real string received by the parse

void	check_spc(void)
{
	generate_fds();
	if (data()->test[data()->spc[data()->curr_spc]][0] == '|')
	    ft_exec();
    else if (data()->test[data()->spc[data()->curr_spc]][0] == '>')
        ft_red();
	while (data()->spc && data()->spc[data()->curr_spc] != '\0' && data()->spc[data()->curr_spc + 1] != '\0')
	{
		if (data()->test[data()->spc[data()->curr_spc]][0] == '|')
			ft_exec_pipe_md();
		else if (data()->test[data()->spc[data()->curr_spc]][0] == '>')
			printf("Work in progress!\n");
		else
			printf("Not pipe or >\n");
	}
	if (data()->spc[data()->curr_spc] == '\0')
        return ;
	else if (data()->test[data()->spc[data()->curr_spc]][0] == '|')
		ft_exec_pipe_end();
	else if (data()->test[data()->spc[data()->curr_spc]][0] == '>')
		ft_red_end();
    else
		printf("2Not pipe or >\n");
}

void cmd_to_exec(void) // Main Fuction
{
	char    *test2[] = {"ls", ">", "output", ">", "output2", ">", "output3", NULL}; //erase this later
	data()->test = test2; //erase this later -> Change all data()->test for the real string received by the parse
	int		i;
	int     j;
	int		pid;

	i = 0;
	j = 0;
	data()->cmds = get_cmds();
	data()->curr_cmd = 0;
	data()->curr_spc = 0;
	data()->curr_fd = 0;
	// for (int k = 0; data()->cmds[k] != NULL; k++)
	//     for (int f = 0; data()->cmds[k][f] != NULL; f++)
	//         printf("Matriz: %d, Array: %d, String: %s\n", k, f, data()->cmds[k][f]);
	// return ;
	if (data()->spc && data()->spc[data()->curr_spc] != '\0')
		check_spc();
	else
	{
		if (is_builtins(data()->cmds[data()->curr_cmd][0]))
			call_builtins(data()->cmds[data()->curr_cmd]);
		else
		{
			pid = fork();
			if (pid == 0)
				execve(data()->cmds[data()->curr_cmd][0], data()->cmds[data()->curr_cmd], NULL);
			else
				waitpid(pid, NULL, 0);
		}
	}
	// Add free for each malloc
}

// Check echo > vs echo ">"
// Handle spc when they're toguether with the exec