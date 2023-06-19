/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:41:20 by gateixei          #+#    #+#             */
/*   Updated: 2023/06/19 20:07:06 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_env_name(char **env, char *str, int size)
{
	int	i;

	i = 0;
	while (env && env[i] != NULL)
	{
		if (!ft_strncmp(env[i], str, size) && env[i][size] == '=')
		{
			unset_var(env, i);
			return ;
		}
		i++;
	}
}

int		check_export(char **str)
{
	int	i;
	int	j;
	
	i = 0;
	j = 1;
	while (str && str[j] != NULL)
	{
		i = 0;
		while (str[j] && str[j][i] != '\0')
		{			
			if (i == 0 && str[j][i] == '=')
			{
				printf("Minishell: export '%s': not a valid identifier\n", str[j]);
				return (0);
			}
			else if (str[j][i] == '=')
			{
				check_env_name(data()->env_p, str[j], i);
				return (j);
			}
			i++;
		}
		j++;
	}
	return (0);
}

void    ft_export(void)
{
	int		j;
	int		new;
	char	**new_str;

	new = check_export(data()->cmds[data()->curr_cmd]);
	if (new < 1)
		return ;
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
	new_str[j++] = ft_strdup(data()->cmds[data()->curr_cmd][new]);
	new_str[j] = NULL;
	free_double_ptr(data()->env_p);
	data()->env_p = new_str;
}
