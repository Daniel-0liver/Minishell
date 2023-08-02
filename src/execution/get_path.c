/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 22:55:48 by gateixei          #+#    #+#             */
/*   Updated: 2023/07/27 00:12:58 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char **env, char *str, int size)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while (env && env[i] != NULL)
	{
		if (!ft_strncmp(env[i], str, size) && env[i][size] == '=')
		{
			while (env[i][++size] != '\0')
				j++;
			value = malloc(sizeof(char) * (j + 1));
			size = size - j;
			j = 0;
			while (env[i][size] != '\0')
				value[j++] = env[i][size++];
			value[j] = '\0';
			return (value);
		}
		i++;
	}
	return (NULL);
}

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
				if (my_strcmp(entry->d_name, cmd))
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
