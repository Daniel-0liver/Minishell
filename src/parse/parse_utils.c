/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 21:45:57 by dateixei          #+#    #+#             */
/*   Updated: 2023/05/14 15:58:31 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to know the numbers of tokens in the str_cmd
int	nbr_tokens(char	*str)
{
	int	i;

	i = 0;
	while (*str)
	{
		while (*str && (*str == ' ' || *str == '\t'))
			str++;
	}
}

// Function to generate tokens from the str_cmd.
void	get_tokens(void)
{
	
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
