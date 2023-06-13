/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:38:35 by gateixei          #+#    #+#             */
/*   Updated: 2023/06/13 16:16:07 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_parent(char *dir)
{
	int		i;
	int		j;
	int		size;
	char	*new_path;

	i = 0;
	j = 0;
	size = 0;
	while (dir[i] != '\0')
	{
		if (dir[i] == '/')
			j++;
		i++;
	}
	i = 0;
	while(i < j)
	{
		if (dir[size] == '/')
			i++;
		size++;
	}
	new_path = malloc(sizeof(char) * size);
	i = -1;
	while (++i < (size - 1))
		new_path[i] = dir[i];
	printf("%s\n", new_path); // Go to this, need to test and improve after merge with parse
}

void	cd_to(char *str)
{
	char dir[1024];
    
    getcwd(dir, (sizeof(char) * 1024));
	if (ft_strcpm(str, ".."))
		get_parent(dir);
	else if (ft_strcpm(str, "."))
		return ;
	else if (ft_strcpm(str, "~"))
		printf("cd: HOME\n");
	else
		printf("cd: Go to Path: %s\n", str);
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

	size = ft_check_cd(str);
	if (size > 2)
		printf("cd: too many arguments\n");
	else if (size == 1)
		printf("cd: HOME\n");
	else
		cd_to(str[1]);
}