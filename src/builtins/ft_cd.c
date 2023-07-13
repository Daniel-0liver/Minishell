/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:38:35 by gateixei          #+#    #+#             */
/*   Updated: 2023/07/13 18:04:01 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_cd_to_env(char *path)
{
	int		j;
	char	**new_str;

	j = 0;
	while (data()->env_p && data()->env_p[j] != NULL)
		j++;
	new_str = malloc(sizeof(char *) * (j + 2));
	j = 0;
	while (data()->env_p && data()->env_p[j] != NULL)
	{
		new_str[j] = ft_strdup(data()->env_p[j]);
		j++;
	}
	new_str[j++] = ft_strdup(path);
	new_str[j] = NULL;
	free_double_ptr(data()->env_p);
	data()->env_p = new_str;
}

void	apply_cd(char *oldcd, char *newcd)
{
	char *path;
    char dir[1024];
    
	if (chdir(newcd) < 0)
	{
		printf("Minishell: cd: %s: No such file or directory\n", newcd);
        data()->error = 1;
		return ;
	}
	path = ft_strjoin("OLDPWD=", oldcd);
	check_export(&path);
	add_cd_to_env(path);
	free(path);
    getcwd(dir, (sizeof(char) * 1024));
	path = ft_strjoin("PWD=", dir);
	check_export(&path);
	add_cd_to_env(path);
	free(path);
	path = NULL;
    data()->error = 0;
}

void	cd_to(char *str)
{
	char	*path;
	char 	dir[1024];
	
	path = NULL;
	getcwd(dir, (sizeof(char) * 1024));
	if (!str || str == NULL || ft_strcpm(str, "~"))
	{
		path = ft_getenv(data()->env_p, "HOME", 4);
		apply_cd(dir, path);
	}
	else if (ft_strcpm(str, "-"))
	{
		path = ft_getenv(data()->env_p, "OLDPWD", 6);
		printf("%s\n", path);
		apply_cd(dir, path);
	}
	else
		apply_cd(dir, str);
	if (path != NULL)
	{
		free(path);
		path = NULL;	
	}
}

int	ft_check_cd(char **str)
{
	int	i;

	i = 0;
	while (str && str[i] != NULL)
		i++;
	return (i);
}

void    ft_cd(char **str)
{
	int	size;
	char 	dir[1024];
	
	getcwd(dir, (sizeof(char) * 1024));
	size = ft_check_cd(str);
	if (size > 2)
    {
        data()->error = 1;
		printf("cd: too many arguments\n");
    }
	else
		cd_to(str[1]);
}