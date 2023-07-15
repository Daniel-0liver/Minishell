/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:35:04 by gateixei          #+#    #+#             */
/*   Updated: 2023/07/15 15:15:47 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_loop(void)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data()->tokens[i] != NULL)
	{
		if (is_spc(data()->tokens[i]))
		{
			j--;
			if (data()->tokens[i + 1] != NULL && is_spc(data()->tokens[i + 1]))
			{
				builtins_error("syntax error near unexpected token `", \
				data()->tokens[i + 1], "'", 2);
				return (1);
			}
		}
		else
			j++;
		i++;
	}
	return (0);
}

int	is_valid(void)
{
	if (data()->tokens[0] != NULL && is_exec(data()->tokens[0]) == 1)
	{
		builtins_error(NULL, NULL, \
		"syntax error near unexpected token `|'", 2);
		return (1);
	}
	if (is_valid_loop())
		return (1);
	return (0);
}

void	cmd_exec(int pid, int status)
{
	if (is_builtins(data()->cmds[data()->curr_cmd][0]))
		call_builtins_exec(data()->cmds[data()->curr_cmd]);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(data()->cmds[data()->curr_cmd][0], \
			data()->cmds[data()->curr_cmd], data()->env_p) == -1)
			{
				printf("%s: command not found\n", \
				data()->cmds[data()->curr_cmd][0]);
				exit(127);
			}
		}
		else
			waitpid(pid, &status, 0);
		data()->error = 0;
		if (status > 0)
			data()->error = status / 256;
	}
	free_exec();
}
