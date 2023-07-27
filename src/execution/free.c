/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:12:12 by gateixei          #+#    #+#             */
/*   Updated: 2023/07/27 19:07:33 by gateixei         ###   ########.fr       */
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
