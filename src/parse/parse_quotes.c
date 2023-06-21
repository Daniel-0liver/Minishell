/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:51:58 by dateixei          #+#    #+#             */
/*   Updated: 2023/06/21 00:09:54 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nbr_inside_quotes(char *str, char c)
{
	int	nbr;
	
	nbr = 0;
	data()->warning = 0;
	str++;
	while (*str && *str != c)
	{
		str++;
		nbr++;
			if (*str == '\0')
		data()->warning = -1;
	}
	return (nbr);
}

int	nbr_outside_quotes(char *str)
{
	int	nbr;
	
	nbr = 0;
	str++;
	while (*str && *str != ' ' && *str != '\n' 
		&& *str != '\t' && *str != '|' && *str != '<' 
		&& *str != '>' && *str != '\'' && *str != '\"')
	{
		str++;
		nbr++;
	}
	return (nbr);
}

char	*handle_quote(char	*str, char c)
{
	str++;
	while (*str && *str != c)
		str++;
	str++;
	return (str);
}

int	check_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (str[i] == '\0')
				return (0);
		}
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
			if (str[i] == '\0')
				return (0);
		}
		i++;
	}
	return (1);
}