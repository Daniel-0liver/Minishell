/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 16:48:10 by dateixei          #+#    #+#             */
/*   Updated: 2023/08/05 13:37:49 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_single_spc_quote(char *str)
{
	char	*spc;

	spc = ft_substr("\"", 0, 2);
	if ((str[1] == '>' || str[1] == '<') && (str[2] == str[1]))
	{
		spc = strjoin_var(spc, str[1]);
		return (strjoin_var(spc, str[2]));
	}
	else
		return (strjoin_var(spc, str[1]));
}

int	token_is_space(char *str, int *i)
{
	int	j;

	j = skip_whitespace(str);
	(*i)++;
	return (j);
}
