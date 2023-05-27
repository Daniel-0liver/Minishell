/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:16:32 by gateixei          #+#    #+#             */
/*   Updated: 2023/05/27 19:40:48 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Change all data()->test for the real string received by the parse

void    ft_exec(void)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		close(data()->fd[0]);
		dup2(data()->fd[1], STDOUT_FILENO);
		execve(data()->cmds[0][0], data()->cmds[0], NULL); // Hard coded
		close(data()->fd[1]);
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(data()->fd[1]);
		dup2(data()->fd[0], STDIN_FILENO);
		execve(data()->cmds[1][0], data()->cmds[1], NULL); // Hard coded		
		close(data()->fd[0]);
	}
}

char	***get_cmds(void)
{
	int     curr, size;
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
	char    *test2[] = {"ls", "-la", "|", "grep", "Make", NULL}; //erase this later
	data()->test = test2; //erase this later -> Change all data()->test for the real string received by the parse
	int		i;
	int     j;
	int		pid;

	i = 0;
	data()->cmds = get_cmds();
		// for (int j = 0; data()->spc[j]; j++)
		// 	printf("%d\n", data()->spc[j]);
	while (data()->cmds[i] != NULL)
	{
		if (data()->spc[0])
		{
			pipe(data()->fd);
			pid = fork();
			if (pid == 0)
				ft_exec();
			waitpid(pid, NULL, 0);
			close(data()->fd[0]);
			close(data()->fd[1]);
			j++;
			i++;
		}
		else
		{   
			pid = fork();
			if (pid == 0)
				execve(data()->cmds[i][0], data()->cmds[i], NULL);
		}
		i++;
	}
	// Add free for each malloc
}
