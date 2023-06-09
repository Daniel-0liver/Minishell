/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:16:32 by gateixei          #+#    #+#             */
/*   Updated: 2023/06/09 16:28:15 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Change all data()->test for the real string received by the parse

int is_spc(char *cmd) // Not using yet >>  Need to separate when is on the same string with the exec
{
	if (ft_strcpm(cmd, "|"))
		return (1);
	else if (ft_strcpm(cmd , "||"))
		return (1);
	else if (ft_strcpm(cmd, ">"))
		return (1);
	else if (ft_strcpm(cmd , ">>"))
		return (1);
	else if (ft_strcpm(cmd, "<"))
		return (1);
	else if (ft_strcpm(cmd , "<<"))
		return (1);
	else if (ft_strcpm(cmd, "&&"))
		return (1);
	else if (ft_strcpm(cmd , "*"))
		return (1);
	return (0);
}

void	check_spc(void)
{
	generate_fds();
	ft_exec();
	while (data()->spc && data()->spc[data()->curr_spc + 1] != '\0')
	{
		if (data()->test[data()->spc[data()->curr_spc]][0] == '|')
			ft_exec_pipe_md();
		else if (data()->test[data()->spc[data()->curr_spc]][0] == '>')
			printf("Work in progress!\n");
		else
			printf("Not pipe or >\n");
	}
	if (data()->test[data()->spc[data()->curr_spc]][0] == '|')
		ft_exec_pipe_end();
	else if (data()->test[data()->spc[data()->curr_spc]][0] == '>')
		printf("2Work in progress!\n");
	else
		printf("2Not pipe or >\n");
}

void cmd_to_exec(void) // Main Fuction
{
	char    *test2[] = {"echo", "-n", "Ola", "|", "ls", NULL}; //erase this later
	data()->test = test2; //erase this later -> Change all data()->test for the real string received by the parse
	int		i;
	int     j;
	int		pid;

	i = 0;
	j = 0;
	data()->cmds = get_cmds();
	data()->curr_cmd = 0;
	data()->curr_spc = 0;
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