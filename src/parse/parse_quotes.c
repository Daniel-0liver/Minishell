/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:51:58 by dateixei          #+#    #+#             */
/*   Updated: 2023/05/21 17:18:49 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *str)
{
	
}

int	check_single_quote(char	*str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == '\'')
			i++;
		str++;
	}
	return (i);
}

int	check_double_quote(char	*str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == '\"')
			i++;
		str++;
	}
	return (i);
}
