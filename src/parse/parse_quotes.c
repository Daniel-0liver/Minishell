/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:51:58 by dateixei          #+#    #+#             */
/*   Updated: 2023/06/14 17:15:21 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	check_quotes(char *str)
// {
// 	return (0);
// }

char	*handle_quote(char	*str, char c)
{
	str++;
	if (*str == c)
	{
		str++;
		while (*str && (*str == ' ' || *str == '\t' || *str == '\n'))
			str++;
		return (str);
	}
	while (*str && *str != c)
		str++;
	return (str);
}
