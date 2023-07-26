/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:38:26 by gateixei          #+#    #+#             */
/*   Updated: 2023/07/15 16:33:43 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_spc(int size)
{
	int	i;
	int	mtz;
	int	*spc;

	i = 0;
	mtz = 0;
	spc = malloc(sizeof(int) * (size));
	while (data()->tokens[i] != NULL)
	{
		if (is_spc(data()->tokens[i]))
		{
			if (mtz == size)
			{
				spc[mtz] = -1;
				data()->spc = spc;
				return ;
			}
			spc[mtz++] = i;
		}
		i++;
	}
	spc[mtz] = -1;
	data()->spc = spc;
}

char	**ft_cmd(void)
{
	char	**cmd;
	int		i;

	data()->count = -1;
	i = ft_cmd_loop();
	if (i >= 0)
		return (get_exec_cmd(i));
	cmd = check_input();
	if (cmd != NULL)
		return (cmd);
	cmd = check_cmd_exec();
	if (cmd != NULL)
		return (cmd);
	cmd = check_red_cmd();
	if (cmd != NULL)
		return (cmd);
	return (NULL);
}

int	ft_matriz_size(void)
{
	int	i;
	int	mtz;

	i = 0;
	mtz = 1;
	while (data()->tokens[i] != NULL)
	{
		if (is_spc(data()->tokens[i]))
			mtz++;
		i++;
	}
	return (mtz);
}

int	ft_ptrlen(int v)
{
	int	i;

	i = 0;
	if (v > 0 && is_redirect(data()->tokens[v - 1]))
		return (1);
	while (data()->tokens[v] != NULL)
	{
		if (is_exec(data()->tokens[v]))
			return (i);
		else if (is_redirect(data()->tokens[v]))
		{
			v++;
			if (data()->tokens[v] == NULL)
				return (i);
			i--;
		}
		i++;
		v++;
	}
	return (i);
}

char	*get_path(char *cmd)
{
	char			*split;
	char			*rtn;
	char			**path;

	split = ft_getenv(data()->env_p, "PATH", 4);
	if (split == NULL)
	{
		return (NULL);
	}
	path = ft_split(split, ':');
	free(split);
	rtn = get_path_loop(cmd, path);
	free_double_ptr(path);
	return (rtn);
}
