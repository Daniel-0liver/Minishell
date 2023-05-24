/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:16:32 by gateixei          #+#    #+#             */
/*   Updated: 2023/05/24 19:26:19 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Changed all data()->test for the real string received by the parse

void cmd_to_exec(void) // Main Fuction
{
	char    *test2[] = {"echo", "Ola mundo!", NULL}; //erase this later
	data()->test = test2; //erase this later -> Changed all data()->test for the real string received by the parse
	char	**cmds;
	int     pid;

	pid = fork();
	if (pid == 0)
	{	
		cmds = check_cmds();
		execve(cmds[0], cmds, NULL);
	}
	waitpid(pid, NULL, 0);
	// Add free for each malloc
}
