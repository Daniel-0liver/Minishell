/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:35:04 by gateixei          #+#    #+#             */
/*   Updated: 2023/06/12 14:50:26 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
