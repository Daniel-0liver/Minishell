/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:51:58 by dateixei          #+#    #+#             */
/*   Updated: 2023/05/14 16:51:12 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == '\'')
		{
			i = check_single_quote(str);
			if (i % 2 != 0)
				return (FALSE);
		}
		else if(*str == '\"')
		{
			i = check_double_quote(str);
			if (i % 2 != 0)
				return (FALSE);
			else
				return (TRUE);
		}
		str++;
	}
	return (TRUE);
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