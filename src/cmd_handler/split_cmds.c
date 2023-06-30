/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:38:26 by gateixei          #+#    #+#             */
/*   Updated: 2023/06/30 11:59:06 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_spc(int size)
{
	int i;
	int mtz;
	int *spc;

	i = 0;
	mtz = 0;
	spc = malloc(sizeof(int) * (size));
	while (data()->tokens[i] != NULL)
	{
		if(is_spc(data()->tokens[i]))
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
	int 	i;
	char	**cmd;
	
	i = 0;
	data()->count = -1;
	while (data()->tokens[i] != NULL && data()->count < 0)
	{	
		if (!is_spc(data()->tokens[i]) && (i == 0 || (i > 0 && !is_spc(data()->tokens[i - 1]))))
		{
			data()->count++;
			if (data()->count == data()->curr_cmd)
				return (get_exec_cmd(i));
			else
			{
				while (data()->tokens[i] != NULL && !is_spc(data()->tokens[i]))
					i++;
				i--;
			}
		}
		i++;
	}
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
		if(is_spc(data()->tokens[i]))
			mtz++;
		i++;
	}
	return (mtz);
}

int	ft_ptrlen(int v)
{
	int i;

	i = 0;
	if (v > 0 && is_redirect(data()->tokens[v - 1]))
		return (1);
	while (data()->tokens[v] != NULL)
	{
		if(is_exec(data()->tokens[v]))
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

char	*check_path(char *cmds) // Change this to PATH variable
{
	int		i;
	int		j;
	char	*rtn;
	char	*path;

	i = 0;
	if (is_builtins(cmds))
		return (ft_strdup(cmds));
	while (cmds[i] != '\0')
	{
		if (cmds[i] == '/')
			return (ft_strdup(cmds));
		i++;
	}
	rtn = malloc(sizeof(char) * (i + 6));
	path = "/bin/";
	j = -1;
	while (++j < 5)
		rtn[j] = path[j];
	i = 0;
	while (cmds[i] != '\0' && cmds[i] != ' ')
		rtn[j++] = cmds[i++];
	rtn[j] = '\0';
	return (rtn);
}