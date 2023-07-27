/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:12:12 by gateixei          #+#    #+#             */
/*   Updated: 2023/07/26 22:15:20 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_triple_ptr(char ***str)
{
	int	i;
	int	j;

	i = 0;
	while (str && str[i] != NULL)
	{
		j = 0;
		while (str && str[i][j] != NULL)
		{
			free(str[i][j]);
			j++;
		}
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

void	free_all(void)
{
	// if (data()->fd && data()->fd != NULL)
	// 	free_fds(data()->fd);
	// if (data()->cmds && data()->cmds != NULL)
	// 	free_cmds(data()->cmds);
	if (data()->spc && data()->spc != NULL)
	{
		free(data()->spc);
		data()->spc = NULL;
	}
	if (data()->tokens && data()->tokens != NULL)
		free_double_ptr(data()->tokens);
}

void	free_exec(void)
{
	// if (data()->cmds && data()->cmds != NULL)
	// 	free_cmds(data()->cmds);
	if (data()->tokens && data()->tokens != NULL)
		free_double_ptr(data()->tokens);
}
