/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:51:58 by dateixei          #+#    #+#             */
/*   Updated: 2023/06/25 16:51:12 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nbr_inside_quotes(char *str, char c)
{
	int		i;
	char	*tmp;
	
	i = 0;
	str++;
	data()->warning = 0;
	while (*str && *str != c)
	{
		if (*str == '$' && c == '\"')
		{
			tmp = check_envp(str);
			if (tmp[0] != '\0')
			{
				i += ft_strlen(tmp);
				while (*str != ' ' || *str != '\n' || *str != '\t' || *str != '\"')
					str++;
				data()->warning = -1;
			}
		}
		str++;
		i++;
	}
	return (i);
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

char	*check_envp(char	*str)
{
	printf("%s\n", str);
	return (str);
}