/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_cmd2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 20:00:12 by gateixei          #+#    #+#             */
/*   Updated: 2023/08/03 10:52:48 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_mtzlen(char ***mtz)
{
	int	i;

	i = 0;
	while (mtz && mtz[i] != NULL)
		i++;
	return (i);
}

char	***my_realloc(char ***cmds)
{
	int		i;
	char	***new_cmds;

	i = 0;
	new_cmds = malloc(sizeof(char *) * (2 + ft_mtzlen(cmds)));
	while (cmds && cmds[i] != NULL)
	{
		new_cmds[i] = cmds[i];
		i++;
	}
	if (cmds != NULL)
		free(cmds);
	return (new_cmds);
}

void	free_token(int i)
{
	free(data()->tokens[i]);
	while (data()->tokens[i + 1] != NULL)
	{
		data()->tokens[i] = data()->tokens[i + 1];
		i++;
	}
	data()->tokens[i] = NULL;
}

int	is_valid_cmd(int i)
{
	if (data()->cmds && is_spc(data()->cmds[0][0]) == 1)
		error_msg(NULL, NULL, "syntax error near unexpected token `|'", 2);
	while (data()->cmds && data()->cmds[++i] != NULL)
	{
		if (is_spc(data()->cmds[i][0]) > 1 && data()->cmds[i][1] \
		!= NULL && is_spc(data()->cmds[i][1]))
		{
			error_msg("syntax error near unexpected token `", \
			data()->cmds[i][1], "'", 2);
			return (1);
		}
		if (is_spc(data()->cmds[i][0]) > 1 && data()->cmds[i][1] == NULL)
		{
			error_msg("syntax error near unexpected token `newline'", \
			NULL, NULL, 2);
			return (1);
		}
		if (data()->cmds[i + 1] == NULL && is_spc(data()->cmds[i][0]) == 1)
		{
			error_msg(NULL, NULL, "syntax error near unexpected token `|'", 2);
			return (1);
		}
	}
	return (0);
}
