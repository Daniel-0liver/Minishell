/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:12:12 by gateixei          #+#    #+#             */
/*   Updated: 2023/07/14 23:01:57 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmds(char ***cmds)
{
	int	i;
	int	j;

	i = 0;
	while (cmds && cmds[i] != NULL)
	{
		j = 0;
		while (cmds[i] && cmds[i][j] != NULL)
		{
			free(cmds[i][j]);
			cmds[i][j] = NULL;
			j++;
		}
		free(cmds[i]);
		cmds[i] = NULL;
		i++;
	}
	free(cmds);
	cmds = NULL;
}

void	free_double_ptr(char **str)
{
	int	i;

	i = 0;
	while (str && str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

void	free_fds(int **fds)
{
	int	i;

	i = 0;
	while (fds && fds[i] != NULL)
	{
		free(fds[i]);
		fds[i] = NULL;
		i++;
	}
	free(fds);
	fds = NULL;
}
