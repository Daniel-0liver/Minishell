/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:38:35 by gateixei          #+#    #+#             */
/*   Updated: 2023/06/15 12:28:52 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_parent(void)
{
	int		i;
	int		j;
	char	*new_path;
    char dir[1024];
    
	i = 0;
	j = 0;
    getcwd(dir, (sizeof(char) * 1024));
	while (dir[i] != '\0')
		i++;
	while (dir[i] != '/')
        i--;
    if (i <= 1)
    {
        return ;
    }
	new_path = malloc(sizeof(char) * (i + 1));
	while (j < i)
    {
		new_path[j] = dir[j];
        j++;
    }
    new_path[j] = '\0';
	printf("%s\n", new_path); // Go to this, need to test and improve after merge with parse
    free(new_path);
    new_path = NULL;
}

void	cd_to(char *str)
{
	if (ft_strcpm(str, ".."))
		get_parent();
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