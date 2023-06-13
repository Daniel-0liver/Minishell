/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:38:26 by gateixei          #+#    #+#             */
/*   Updated: 2023/06/12 17:46:12 by gateixei         ###   ########.fr       */
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
	while (data()->test[i] != NULL)
	{
		if(is_spc(data()->test[i]))
			spc[mtz++] = i;
		i++;
	}
	spc[mtz] = '\0';
	data()->spc = spc;
}

char	**ft_cmd(void)
{
	int 		i;
	int			size;
	int			tmp_curr;
	char		**cmd;
	
	i = 0;
	if(is_spc(data()->test[data()->curr_cmd]))
		data()->curr_cmd++;
	size = ft_ptrlen(data()->curr_cmd);
	cmd = malloc((size + 1) * sizeof(char *));
	cmd[i] = check_path(data()->test[data()->curr_cmd]);
	data()->curr_cmd++;
	i++;
	tmp_curr = data()->curr_cmd;
	while (--size > 0)
	{
		if (is_redirect(data()->test[tmp_curr]))
		{
			tmp_curr = tmp_curr + 2;
			size++;
		}
		else
		{
			cmd[i] = ft_strdup(data()->test[tmp_curr]);
			tmp_curr++;
			i++;
		}
	}
	while (data()->test[data()->curr_cmd] != NULL && !is_spc(data()->test[data()->curr_cmd]))
		data()->curr_cmd++;
	cmd[i] = NULL;
	return (cmd);
}

int	ft_matriz_size(void)
{
	int	i;
	int	mtz;

	i = 0;
	mtz = 1;
	while (data()->test[i] != NULL)
	{
		if(is_spc(data()->test[i]))
			mtz++;
		i++;
	}
	return (mtz);
}

int	ft_ptrlen(int v)
{
	int i;

	i = 0;
	if (v > 0 && is_redirect(data()->test[v - 1]))
		return (1);
	while (data()->test[v] != NULL)
	{
		if(is_exec(data()->test[v]))
			return (i);
		else if (is_redirect(data()->test[v]))
		{
			v++;
			if (data()->test[v] == NULL)
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
	if (data()->curr_cmd > 0 && is_redirect(data()->test[data()->curr_cmd - 1]))
		return (ft_strdup(cmds));
	while (cmds[i] != '\0' && cmds[i] != ' ')
	{
		if (cmds[i] == '/')
			return (ft_strdup(cmds));
		i++;
	}
	rtn = malloc(sizeof(char) * (i + 5));
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