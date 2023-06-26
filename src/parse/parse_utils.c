/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 21:45:57 by dateixei          #+#    #+#             */
/*   Updated: 2023/06/26 20:05:50 by gateixei         ###   ########.fr       */
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
		if (*str == ' ' || *str == '\n' || *str == '\t')
			str++;
		else if (*str == '\'' || *str == '\"')
		{
			if (str[1] != *str)
			{
				str = handle_quote(str, *str);
				i++;
				if (*str == '\0')
					return(i);
			}
			else
				str += 2;
		}
		else if ((*str == '|' || *str == '<' || *str == '>'))
		{
			if ((*str == '<' || *str == '>') && (str[1] == *str))
				str += 2;
			else
				str++;
			i++;
		}
		else
		{
			while (*str && *str != ' ' && *str != '\n' && *str != '\t' && *str != '|' && *str != '<' && *str != '>')
				str++;
			i++;
		}
	}
	return (i);
}

char	**alloc_tokens(char *str, int nbr_tokens)
{
	int		i;
	int		size;
	char	**tokens;

	i = 0;
	tokens = (char **)malloc((nbr_tokens + 1) * sizeof(char *));
	if (!tokens)
	{
		perror("Error while malloc tokens.");
		return (NULL);
	}
	while (*str)
	{
		if (*str == ' ' || *str == '\n' || *str == '\t')
			str++;
		else if (*str == '\'' || *str == '\"')
		{
			if (str[1] != *str)
			{
				size = nbr_inside_quotes(str, *str);
				if (data()->warning == -1)
					tokens[i++] = env_var(str++);
				else
					tokens[i++] = ft_substr(++str, 0, size);
				str += (size + 1);
			}
			else
				str += 2;
		}
		else if ((*str == '|' || *str == '>' || *str == '<'))
		{
			if (str[1] == *str && (*str == '>' || *str == '<'))
			{
				tokens[i++] = ft_substr(str, 0, 2);
				str += 2;
			}
			else
				tokens[i++] = ft_substr(str++, 0, 1);
		}
		else
		{
			size = nbr_outside_quotes(str);
			tokens[i++] = ft_substr(str, 0, (size + 1));
			str += (size + 1);
		}
	}
	tokens[i] = NULL;
	return (tokens);
}

// Function to generate tokens from the str_cmd.
int	get_tokens(void)
{
	int	nbr_tokens;

	while (*data()->str_cmd == ' ' || *data()->str_cmd == '\n' || *data()->str_cmd == '\t')
		data()->str_cmd++;
	if (*data()->str_cmd == '\0')
		return(0);
	if (check_quotes(data()->str_cmd) == 0)
	{
		perror("Error unclosed quotes");
		return (0);
	}
	nbr_tokens = count_tokens(data()->str_cmd);
	data()->tokens = alloc_tokens(data()->str_cmd, nbr_tokens);
	if (*data()->tokens == NULL)
		return (0);
	return (1);
}
