/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:35:04 by gateixei          #+#    #+#             */
/*   Updated: 2023/07/20 17:07:24 by gateixei         ###   ########.fr       */
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
	if (data()->tokens[0] != NULL && data()->tokens[0][0] == '#')
		return (1);
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
				error_exec();
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

void	alloc_env(char **env)
{
	int	j;

	j = 0;
	while (env && env[j] != NULL)
		j++;
	data()->env_p = malloc(sizeof(char *) * (j + 1));
	j = 0;
	while (env && env[j] != NULL)
	{
		data()->env_p[j] = ft_strdup(env[j]);
		j++;
	}
	data()->env_p[j] = NULL;
}

int	ft_cmd_loop(void)
{
	int	i;

	i = 0;
	while (data()->tokens[i] != NULL && data()->count < 0)
	{
		if (!is_spc(data()->tokens[i]) \
		&& (i == 0 || (i > 0 && !is_spc(data()->tokens[i - 1]))))
		{
			data()->count++;
			if (data()->count == data()->curr_cmd)
				return (i);
			else
			{
				while (data()->tokens[i] != NULL && !is_spc(data()->tokens[i]))
					i++;
				i--;
			}
		}
		i++;
	}
	return (-1);
}
