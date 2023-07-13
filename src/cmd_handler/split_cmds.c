/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:38:26 by gateixei          #+#    #+#             */
/*   Updated: 2023/07/13 21:59:54 by gateixei         ###   ########.fr       */
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

char	*get_path(char *cmd)
{
	int		i;
	DIR		*dir;
	char	*rtn;
	char	**path;
	struct	dirent *entry;
	
	i = 0;
	rtn = ft_getenv(data()->env_p, "PATH", 4);
    if (rtn == NULL)
    {
        return (NULL);
    }
	path = ft_split(rtn, ':');
	free(rtn);
	while (path[i] != NULL)
	{
		dir = opendir(path[i]);
		if (dir != NULL)
		{
			while ((entry = readdir(dir)) != NULL)
			{
				if (ft_strcpm(entry->d_name, cmd))
				{
					rtn = ft_strdup(path[i]);
					free_double_ptr(path);
					closedir(dir);
					return (rtn);
				}
			}
		}
		closedir(dir);
		i++;
	}
	free_double_ptr(path);
	return (NULL);
}

char	*check_path(char *cmds)
{
	int		i;
	int		j;
	int		k;
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
	path = get_path(cmds);
	if (path == NULL)
		return (ft_strdup(cmds));
	k = ft_strlen(path);
	rtn = malloc(sizeof(char) * (i + 2 + k));
	j = -1;
	while (++j < k)
		rtn[j] = path[j];
	rtn[j++] = '/';
	i = 0;
	while (cmds[i] != '\0' && cmds[i] != ' ')
		rtn[j++] = cmds[i++];
	rtn[j] = '\0';
	free(path);
	return (rtn);
}