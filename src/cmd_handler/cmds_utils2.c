/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:35:04 by gateixei          #+#    #+#             */
/*   Updated: 2023/06/15 12:55:39 by gateixei         ###   ########.fr       */
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
		free_test();
}

void	free_exec(void)
{
	if (data()->cmds && data()->cmds != NULL)
		free_cmds(data()->cmds);
	if (data()->test && data()->test != NULL)
		free_test();
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
