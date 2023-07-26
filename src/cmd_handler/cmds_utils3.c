/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:35:04 by gateixei          #+#    #+#             */
/*   Updated: 2023/07/14 23:04:21 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_exec_cmd(int i)
{
	int		size;
	int		index;
	char	**cmd;

	index = 0;
	size = ft_ptrlen(i);
	cmd = malloc((size + 1) * sizeof(char *));
	cmd[index++] = check_path(data()->tokens[i]);
	i++;
	while (--size > 0)
	{
		if (is_redirect(data()->tokens[i]))
		{
			i = i + 2;
			size++;
		}
		else
		{
			cmd[index++] = ft_strdup(data()->tokens[i]);
			i++;
		}
	}
	cmd[index] = NULL;
	data()->curr_cmd++;
	return (cmd);
}

char	**get_red_cmd(int i)
{
	char	**cmd;

	cmd = malloc(2 * sizeof(char *));
	cmd[0] = ft_strdup(data()->tokens[i]);
	cmd[1] = NULL;
	data()->curr_cmd++;
	return (cmd);
}

char	**check_input(void)
{
	int	i;

	i = 0;
	while (data()->tokens[i] != NULL)
	{
		if (is_redirect(data()->tokens[i]) == 3 \
		|| is_redirect(data()->tokens[i]) == 4)
		{
			data()->spc[data()->count] = i;
			data()->count++;
		}
		i++;
		if (data()->count == data()->curr_cmd)
			return (get_red_cmd(i));
	}
	return (NULL);
}

char	**check_cmd_exec(void)
{
	int	i;

	i = 0;
	while (data()->tokens[i] != NULL)
	{
		if (is_exec(data()->tokens[i]) == 1)
		{
			data()->spc[data()->count] = i;
			data()->count++;
		}
		i++;
		if (data()->count == data()->curr_cmd)
			return (get_exec_cmd(i));
	}
	return (NULL);
}

char	**check_red_cmd(void)
{
	int	i;

	i = 0;
	while (data()->tokens[i] != NULL)
	{
		if (is_redirect(data()->tokens[i]) == 1 \
		|| is_redirect(data()->tokens[i]) == 2)
		{
			data()->spc[data()->count] = i;
			data()->count++;
		}
		i++;
		if (data()->count == data()->curr_cmd)
			return (get_red_cmd(i));
	}
	return (NULL);
}
