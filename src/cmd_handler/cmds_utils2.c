/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:35:04 by gateixei          #+#    #+#             */
/*   Updated: 2023/06/19 14:17:52 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (data()->test && data()->test != NULL)
		free_double_ptr(data()->test);
}

void	free_exec(void)
{
	if (data()->cmds && data()->cmds != NULL)
		free_cmds(data()->cmds);
	if (data()->test && data()->test != NULL)
		free_double_ptr(data()->test);
}

int is_redirect(char *cmd)
{
	if (ft_strcpm(cmd, ">"))
		return (1);
	else if (ft_strcpm(cmd , ">>"))
		return (1);
	else if (ft_strcpm(cmd, "<"))
		return (1);
	else if (ft_strcpm(cmd , "<<"))
		return (1);
	return (0);
}

int is_exec(char *cmd)
{
	if (ft_strcpm(cmd, "|"))
		return (1);
	else if (ft_strcpm(cmd , "||"))
		return (1);
	else if (ft_strcpm(cmd, "&&"))
		return (1);
	else if (ft_strcpm(cmd , "*"))
		return (1);
	return (0);
}

void	alloc_env(char **env)
{
	int	j;

	j = 0;
	while (env && env[j] != NULL)
		j++;
	data()->env_p = malloc(sizeof(char *) * (j + 1));
	j = 0;
	while (env && env[j] != NULL)
	{
		data()->env_p[j] = ft_strdup(env[j]);
		j++;
	}
	data()->env_p[j] = NULL;
}