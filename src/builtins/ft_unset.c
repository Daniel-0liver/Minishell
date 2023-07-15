/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:42:13 by gateixei          #+#    #+#             */
/*   Updated: 2023/07/15 17:44:43 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_var(char **env, int skip)
{
	int		i;
	int		j;
	char	**new_str;

	i = 0;
	while (env && env[i] != NULL)
		i++;
	new_str = malloc(sizeof(char *) * i);
	i = 0;
	j = 0;
	while (env && env[i] != NULL)
	{
		if (i == skip)
			i++;
		else
		{
			new_str[j] = ft_strdup(env[i]);
			j++;
			i++;
		}
	}
	new_str[j] = NULL;
	free_double_ptr(data()->env_p);
	data()->env_p = new_str;
}

void	ft_unset(char **str, char *find)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_strncmp(str[i], find, ft_strlen(find)) \
		&& str[i][ft_strlen(find)] == '=')
		{
			unset_var(str, i);
			return ;
		}
		i++;
	}
}
