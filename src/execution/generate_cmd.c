/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:38:56 by gateixei          #+#    #+#             */
/*   Updated: 2023/08/01 16:28:54 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmdlen(void)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (is_spc(data()->tokens[i]) == 1 \
	|| (is_spc(data()->tokens[i]) > 1 && data()->tokens[i + 1] == NULL))
		return (1);
	else if (is_spc(data()->tokens[i]) > 1)
		return (2);
	while (data()->tokens[i] != NULL && is_spc(data()->tokens[i]) != 1)
	{
		if (is_spc(data()->tokens[i]) > 1)
		{
			if (data()->tokens[i + 1] == NULL)
				break ;
			i = i + 2;
		}
		else
		{
			i++;
			j++;
		}
	}
	return (j);
}

char	**spc_cmd(int i, int j, int size)
{
	char	**cmd;

	cmd = malloc(sizeof(char *) * (1 + size));
	while (size-- > 0 && data()->tokens[i] != NULL)
	{
		cmd[j++] = ft_strdup(data()->tokens[i]);
		free_token(i);
	}
	cmd[j] = NULL;
	return (cmd);
}

char	**get_cmd(int i, int j, int size)
{
	char	**cmd;

	if (is_spc(data()->tokens[i]))
		return (spc_cmd(i, j, size));
	cmd = malloc(sizeof(char *) * (1 + size));
	while (data()->tokens && data()->tokens[i] != NULL \
	&& is_spc(data()->tokens[i]) != 1)
	{
		if (is_spc(data()->tokens[i]) > 1)
		{
			if (data()->tokens[i + 1] == NULL)
				break ;
			i = i + 2;
		}
		else
		{
			cmd[j++] = ft_strdup(data()->tokens[i]);
			free_token(i);
		}
	}
	cmd[j] = NULL;
	return (cmd);
}

char	***generate_cmd(void)
{
	int		i;
	char	***cmds;

	i = 0;
	cmds = NULL;
	while (data()->tokens && data()->tokens[0] != NULL)
	{
		cmds = my_realloc(cmds);
		cmds[i++] = get_cmd(0, 0, ft_cmdlen());
		cmds[i] = NULL;
	}
	free(data()->tokens);
	data()->tokens = NULL;
	return (cmds);
}
