/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:16:32 by gateixei          #+#    #+#             */
/*   Updated: 2023/06/15 15:04:02 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Change all data()->test for the real string received by the parse

void    free_cmds(char ***cmds)
{
	int i;
	int j;

	i = 0;
	while (cmds && cmds[i] != NULL)
	{
		j = 0;
		while (cmds[i] && cmds[i][j] != NULL)
		{
			free(cmds[i][j]);
			cmds[i][j] = NULL;
			j++;
		}
		free(cmds[i]);
		cmds[i] = NULL;
		i++;
	}
	free(cmds);
	cmds = NULL;
}

void    free_test(void)
{
	int i;

	i = 0;
	while (data()->test && data()->test[i] != NULL)
	{
		free(data()->test[i]);
		data()->test[i] = NULL;
		i++;
	}
	free(data()->test);
	data()->test = NULL;
}

void    free_fds(int **fds)
{
	int i;

	i = 0;
	while (fds && fds[i] != NULL)
	{
		free(fds[i]);
		fds[i] = NULL;
		i++;
	}
	free(fds);
	fds = NULL;
}

void	check_spc(void)
{
	generate_fds();
	if (is_exec(data()->test[data()->spc[data()->curr_spc]]))
		ft_exec();
	else if (is_redirect(data()->test[data()->spc[data()->curr_spc]]))
	{
		ft_red();
	}
	while (data()->spc && data()->spc[data()->curr_spc] != '\0' && data()->spc[data()->curr_spc + 1] != '\0')
	{
		if (is_exec(data()->test[data()->spc[data()->curr_spc]]))
			ft_exec_pipe_md();
		else if (is_redirect(data()->test[data()->spc[data()->curr_spc]]))
			ft_red_end();
		else
			printf("Not pipe or >\n");
	}
	if (is_exec(data()->test[data()->spc[data()->curr_spc - 1]]) && data()->spc[data()->curr_spc] == '\0')
		ft_exec_pipe_end();
	else if (is_redirect(data()->test[data()->spc[data()->curr_spc]]))
		ft_red_end();
	else if (is_exec(data()->test[data()->spc[data()->curr_spc]]))
		ft_exec_pipe_end();
	else if (data()->spc[data()->curr_spc] == '\0')
		return ;
	else
		printf("2Not pipe or >\n");
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
				execve(data()->cmds[data()->curr_cmd][0], data()->cmds[data()->curr_cmd], NULL);
			else
				waitpid(pid, NULL, 0);
		}
		free_exec();
	}
}

// Check echo > vs echo ">"
// Handle spc when they're toguether with the exec