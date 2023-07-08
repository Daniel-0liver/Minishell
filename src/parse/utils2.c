/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:26:11 by dateixei          #+#    #+#             */
/*   Updated: 2023/07/08 17:43:56 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_whitespace(char **str)
{
	while (**str && (**str == ' ' || **str == '\n' || **str == '\t'))
		(*str)++;
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
		tmp = strjoin_var(tmp, str[i++]);
	data()->str_tmp = my_getenv(tmp);
	free(tmp);
	tmp = NULL;
}
