/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:16:32 by gateixei          #+#    #+#             */
/*   Updated: 2023/05/29 19:07:25 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Change all data()->test for the real string received by the parse

void	check_spc(void)
{
	int	pid;

	pipe(data()->fd);
	pid = fork();
	if (pid == 0)
	{
		ft_exec();
		while (data()->spc && data()->spc[data()->curr_spc + 1] != '\0')
		{
			if (data()->test[data()->spc[data()->curr_spc]][0] == '|')
			{
				ft_exec_pipe_md();
				printf("Got here\n");
			}
			else if (data()->test[data()->spc[data()->curr_spc]][0] == '>')
				printf("Work in progress!\n");
			else
				printf("Not pipe or >\n");
			data()->curr_cmd++;
			data()->curr_spc++;
		}
		if (data()->test[data()->spc[data()->curr_spc]][0] == '|')
		{
			ft_exec_pipe_end();
		}
		else if (data()->test[data()->spc[data()->curr_spc]][0] == '>')
			printf("2Work in progress!\n");
		else
			printf("2Not pipe or >\n");
	}
	close(data()->fd[0]);
	close(data()->fd[1]);
	waitpid(pid, NULL, 0);
}

char	***get_cmds(void)
{
	int     curr;
	int		size;
	char	***cmds;

	curr = 0;
	data()->curr_cmd = 0;
	size = ft_matriz_size();
	if (size > 1)
		ft_spc(size);
	cmds = malloc((size + 1) * sizeof(char *));
	while (size-- > 0)
		cmds[curr++] = ft_cmd();
	cmds[curr] = NULL;
	return (cmds);
}


void cmd_to_exec(void) // Main Fuction
{
	char    *test2[] = {"ls", "-la", "|", "grep", "gateixei", "|", "grep", "Make", NULL}; //erase this later
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
	// 	for (int f = 0; data()->cmds[k][f] != NULL; f++)
	// 		printf("Matriz: %d, Array: %d, String: %s\n", k, f, data()->cmds[k][f]);
	// while (data()->cmds[data()->curr_cmd] != NULL)
	// {
		if (data()->spc && data()->spc[data()->curr_spc] != '\0')
			check_spc();
		else
		{
			pid = fork();
			if (pid == 0)
			{
				execve(data()->cmds[data()->curr_cmd][0], data()->cmds[data()->curr_cmd], NULL);
				waitpid(pid, NULL, 0);
			}
		}
	// 	data()->curr_cmd++;
	// }
	// Add free for each malloc
}
