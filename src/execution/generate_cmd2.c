/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_cmd2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 20:00:12 by gateixei          #+#    #+#             */
/*   Updated: 2023/07/31 20:00:54 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ptrlen(char ***mtz)
{
	int	i;

	i = 0;
	while (mtz && mtz[i] != NULL)
		i++;
	return (i);
}

char	***my_realloc(char ***cmds)
{
	int		i;
	char	***new_cmds;

	i = 0;
	new_cmds = malloc(sizeof(char *) * (2 + ft_ptrlen(cmds)));
	while (cmds && cmds[i] != NULL)
	{
		new_cmds[i] = cmds[i];
		i++;
	}
	if (cmds != NULL)
		free(cmds);
	return (new_cmds);
}

void	free_token(int i)
{
	free(data()->tokens[i]);
	while (data()->tokens[i + 1] != NULL)
	{
		data()->tokens[i] = data()->tokens[i + 1];
		i++;
	}
	data()->tokens[i] = NULL;
}
