/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:35:04 by gateixei          #+#    #+#             */
/*   Updated: 2023/07/15 18:04:56 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char **env, char *str, int size)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while (env && env[i] != NULL)
	{
		if (!ft_strncmp(env[i], str, size) && env[i][size] == '=')
		{
			while (env[i][++size] != '\0')
				j++;
			value = malloc(sizeof(char) * (j + 1));
			size = size - j;
			j = 0;
			while (env[i][size] != '\0')
				value[j++] = env[i][size++];
			value[j] = '\0';
			return (value);
		}
		i++;
	}
	return (NULL);
}

void	free_all(void)
{
	if (data()->fd && data()->fd != NULL)
		free_fds(data()->fd);
	if (data()->cmds && data()->cmds != NULL)
		free_cmds(data()->cmds);
	if (data()->spc && data()->spc != NULL)
	{
		free(data()->spc);
		data()->spc = NULL;
	}
	if (data()->tokens && data()->tokens != NULL)
		free_double_ptr(data()->tokens);
}

void	free_exec(void)
{
	if (data()->cmds && data()->cmds != NULL)
		free_cmds(data()->cmds);
	if (data()->tokens && data()->tokens != NULL)
		free_double_ptr(data()->tokens);
}

int	is_redirect(char *cmd)
{
	if (ft_strcpm(cmd, ">"))
		return (1);
	else if (ft_strcpm(cmd, ">>"))
		return (2);
	else if (ft_strcpm(cmd, "<"))
		return (3);
	else if (ft_strcpm(cmd, "<<"))
		return (4);
	return (0);
}

int	is_exec(char *cmd)
{
	if (ft_strcpm(cmd, "|"))
		return (1);
	return (0);
}
