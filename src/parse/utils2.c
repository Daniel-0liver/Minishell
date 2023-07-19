/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:26:11 by dateixei          #+#    #+#             */
/*   Updated: 2023/07/19 21:23:42 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'))
		i++;
	return (i);
}

void	skip_non_whitespace_and_dolar_sign(char **str)
{
	while (**str && **str != ' ' && **str != '\n' && **str != '\t'
		&& **str != '\"' && **str != '$')
		(*str)++;
}

void	handle_env(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (str[i] && str[i] != ' ' && str[i] != '\n' && str[i] != '\t'
		&& str[i] != '\"' && str[i] != '$')
	{
		tmp = strjoin_var(tmp, str[i++]);
		if (ft_strncmp(tmp, "?", 2) == 0)
			break ;
	}
	data()->str_tmp = my_getenv(tmp);
	free(tmp);
	tmp = NULL;
}

// Function to know the numbers of some char in a string
int	nbr_char(char *str, char c)
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

void	handle_special_characters(char **str, int *count)
{
	if ((**str == '|' || **str == '<' || **str == '>'))
	{
		if ((**str == '<' || **str == '>') && (*str)[1] == **str)
			(*str) += 2;
		else
			(*str)++;
	}
	else if (**str == '$')
	{
		data()->warning = 0;
		handle_dollar_sign(*str);
		(*str)++;
		while (**str && **str != ' ' && **str != '\n' && **str != '$'
			&& **str != '\t' && **str != '|' && **str != '<' && **str != '>')
			(*str)++;
		if (data()->warning == -1)
			return ;
	}
	else
	{
		while (**str && **str != ' ' && **str != '\n'
			&& **str != '\t' && **str != '|' && **str != '<' && **str != '>')
			(*str)++;
	}
	(*count)++;
}
