/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:36:35 by dateixei          #+#    #+#             */
/*   Updated: 2023/07/15 15:56:26 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_tokens(int nbr_tokens)
{
	char	**tokens;

	tokens = (char **)calloc((nbr_tokens + 1), sizeof(char *));
	tokens[nbr_tokens] = NULL;
	if (!tokens)
	{
		perror("Error while malloc tokens.");
		return (NULL);
	}
	return (tokens);
}

int	token_inside_quote(char	*str, char **token)
{
	int		size;
	char	*spc;

	if (str[1] != *str)
	{
		size = nbr_inside_quotes(str, *str);
		if ((*str == '\"' && str[2] == '\"') && (str[1] == '>'
				|| str[1] == '<' || str[1] == '|'))
		{
			spc = ft_substr("\"", 0, 2);
			(*token) = strjoin_var(spc, str[1]);
		}
		else if (data()->warning == -1)
			(*token) = strjoin_null((*token), env_var(str++));
		else
			(*token) = strjoin_null((*token),
					ft_substr(++str, 0, size));
		return (size + 2);
	}
	else
		return (2);
}

int	token_special_char(char *str, char **token)
{
	if (str[1] == *str && (*str == '>' || *str == '<'))
	{
		(*token) = strjoin_null((*token), ft_substr(str, 0, 2));
		return (2);
	}
	else
	{
		(*token) = strjoin_null((*token), ft_substr(str++, 0, 1));
		return (1);
	}
}

int	token_space_dolar_sig(char *str, char **token, int nbr_tokens)
{
	int	size;

	size = handle_dollar_sign(str);
	if (data()->warning != -1)
	{
		if (data()->str_tmp != NULL)
			(*token) = strjoin_null((*token), ft_substr(data
						()->str_tmp, 0, ft_strlen(data()->str_tmp)));
	}
	else if (nbr_tokens > 0)
		return (0);
	else
		(*token) = strjoin_null((*token), ft_substr(" ", 0, 1));
	return (size + 1);
}

int	token_other_chars(char *str, char **token)
{
	int	size;

	size = nbr_outside_quotes(str);
	(*token) = strjoin_null((*token), ft_substr(str, 0, (size + 1)));
	return (size + 1);
}
