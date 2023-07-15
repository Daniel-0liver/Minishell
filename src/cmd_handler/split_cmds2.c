/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:38:26 by gateixei          #+#    #+#             */
/*   Updated: 2023/07/15 16:33:14 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_loop(char *cmd, char **path)
{
	int				i;
	DIR				*dir;
	struct dirent	*entry;

	i = 0;
	while (path[i] != NULL)
	{
		dir = opendir(path[i]);
		if (dir != NULL)
		{
			entry = readdir(dir);
			while (entry != NULL)
			{
				if (ft_strcpm(entry->d_name, cmd))
				{
					closedir(dir);
					return (ft_strdup(path[i]));
				}
				entry = readdir(dir);
			}
		}
		closedir(dir);
		i++;
	}
	return (NULL);
}

char	*add_path(char *path, int i, char *cmds)
{
	int		k;
	int		j;
	char	*rtn;

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
	return (rtn);
}

char	*check_path(char *cmds)
{
	int		i;
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
	rtn = add_path(path, i, cmds);
	free(path);
	return (rtn);
}
