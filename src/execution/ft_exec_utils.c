/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 00:35:46 by gateixei          #+#    #+#             */
/*   Updated: 2023/07/15 00:52:57 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_end(void)
{
	dup2(data()->fd[data()->curr_fd][0], STDIN_FILENO);
	if (execve(data()->cmds[data()->curr_cmd][0], \
	data()->cmds[data()->curr_cmd], data()->env_p) == -1)
	{
		printf("%s: command not found\n", data()->cmds[data()->curr_cmd][0]);
		free_all();
		exit(127);
	}
}
