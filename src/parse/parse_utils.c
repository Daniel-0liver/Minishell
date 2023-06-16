/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 21:45:57 by dateixei          #+#    #+#             */
/*   Updated: 2023/06/15 15:42:39 by dateixei         ###   ########.fr       */
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
		while (*str == ' ' || *str == '\n' || *str == '\t')
			str++;
		if (*str == '\0')
			return (i);
		if (*str == '\'' || *str == '\"')
		{
			if (str[1] != *str)
			{
				str = handle_quote(str, *str);
				i++;
				if (*str == '\0')
					return(i);
			}
			else if (str[2] && str[2] != ' ' && str[2] != '\n' && str[2] != '\t')
		 		i++;
			else
				str++;
		}
		else
			i++;
		while (*str && *str != ' ' && *str != '\n' && *str != '\t')
		{
			if ((*str == '|' || *str == '<' || *str == '>') && str[1] != ' ' && str[1] != '\n' && str[1] != '\t')
			{
				if ((*str == '<' || *str == '>'))
					str++;
				i++;
			}
			str++;
		}
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
