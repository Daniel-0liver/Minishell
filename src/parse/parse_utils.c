/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 21:45:57 by dateixei          #+#    #+#             */
/*   Updated: 2023/06/14 17:14:44 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to know the numbers of some char in a string
int	nbr_char(char	*str, char	c)
{
	int	i;

	i = 0;
	while (*str)
	{
		while (*str && *str != c)
			str++;
		str++;
		i++;
	}
	return (i);
}

// Function to count the tokens
int	count_tokens(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		while (*str && (*str == ' ' || *str == '\t' || *str == '\n'))
			str++;
		while (*str && (*str != ' ' && *str != '\t' && *str != '\n'))
		{
			if (*str == '\'' || *str == '\"')
			{
					str = handle_quote(str, *str);
				if (*str == '\0')
					return (i);
				else 
					i++;
			}
			str++;
		}
		i++;
	}
	return (i);
}

// Function to generate tokens from the str_cmd.
void	get_tokens(void)
{
	// int	nbr_tokens;
	// data()->nbr_pipe_sig = nbr_char(data()->str_cmd, '|');
	// nbr_tokens = count_tokens(data()->str_cmd);
	return ;
}
