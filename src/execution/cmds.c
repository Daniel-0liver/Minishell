/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:16:32 by gateixei          #+#    #+#             */
/*   Updated: 2023/05/25 20:01:21 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Change all data()->test for the real string received by the parse

char	**ft_cmd(void)
{
	int 		i;
	int			size;
	char		**cmd;
	static int	curr = 0;
	
	i = 0;
	if(data()->test[data()->curr_cmd][0] == '<' || data()->test[data()->curr_cmd][0] == '>'
	|| data()->test[data()->curr_cmd][0] == '|' || data()->test[data()->curr_cmd][0] == '&')
		data()->curr_cmd++;
	size = ft_ptrlen(data()->curr_cmd);
	cmd = malloc((size + 1) * sizeof(char *));
	while (size-- > 0)
	{
		cmd[i] = ft_strdup(data()->test[data()->curr_cmd]);
		printf("INSIDE FT_CMD: %s\n", cmd[i]);
		data()->curr_cmd++;
		i++;
	}
	cmd[i] = NULL;
	printf("Passou aqui!!\n");
	return (cmd);
}

char	***get_cmds(void)
{
	int     curr, size;
	char	***cmds;

	curr = 0;
	data()->curr_cmd = 0;
	size = ft_matriz_size();
	cmds = malloc((size + 1) * sizeof(char *));
	while (size-- > 0)
		cmds[curr++] = ft_cmd();
	cmds[curr] = NULL;
	return (cmds);
}


void cmd_to_exec(void) // Main Fuction
{
	char    *test2[] = {"echo", "Ola mundo!", ">", "output", NULL}; //erase this later
	data()->test = test2; //erase this later -> Change all data()->test for the real string received by the parse
	char	***cmds;

	cmds = get_cmds();
	for (int i = 0; cmds[i] != NULL; i++)
		for (int j = 0; cmds[i][j] != NULL; j++)
			printf("Matriz: %d, Array: %d, String: %s\n", i, j, cmds[i][j]);

	// Add free for each malloc
}
