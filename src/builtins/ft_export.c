/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:41:20 by gateixei          #+#    #+#             */
/*   Updated: 2023/06/19 14:19:16 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_export(char **env)
{
	int	j;
	char	**new_str;

	j = 0;
	while (env && env[j] != NULL)
		j++;
	new_str = malloc(sizeof(char *) * (j + 2));
	j = 0;
	while (env && env[j] != NULL)
	{
		new_str[j] = ft_strdup(env[j]);
		j++;
	}
	new_str[j++] = ft_strdup(data()->cmds[data()->curr_cmd][1]);
	new_str[j] = NULL;
    free_double_ptr(data()->env_p);
    data()->env_p = new_str;
}
