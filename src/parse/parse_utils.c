/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 21:45:57 by dateixei          #+#    #+#             */
/*   Updated: 2023/06/10 18:26:20 by dateixei         ###   ########.fr       */
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
		{
			str++;
			if (!*str)
				return (i);
		}
		while (*str && (*str != ' ' && *str != '\n' && *str != '\t'))
		{
			if ((*str == '>' || *str == '<' || *str == '|') && str[i] != ' ')
				i++;
			if (*str == '\"' || *str == '\'')
			{
				if (*str == str[1])
					i--;
				str = handle_quote(str, *str);
			}
			str++;
		}
		i++;
	}
	return (i);
}

// Function to generate tokens from the str_cmd.
int	get_tokens(void)
{
	int	nbr_tokens;
	
	data()->nbr_pipe_sig = nbr_char(data()->str_cmd, '|');
	nbr_tokens = count_tokens(data()->str_cmd);
	data()->tokens = (char *)malloc((nbr_tokens + 1) * sizeof(char));
	if (!data()->tokens)
	{
		printf("Error while allocating tokens\n");
		return (1);
	}
	
	return (0);
}

//The ft_strchr() function returns a pointer to the first 
// occurrence of the character c in the string s.
char	*ft_strchr(const char *s, int c)
{
	char	tmp_c;

	tmp_c = c;
	while (*s)
	{
		if (*s == tmp_c)
			return ((char *)s);
		s++;
	}
	if (*s == tmp_c)
		return ((char *)s);
	return ((void *)0);
}
