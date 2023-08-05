/* ************************************************************************** */
/*		                                                                    */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:07:53 by gateixei          #+#    #+#             */
/*   Updated: 2023/07/14 23:12:14 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtins(char *cmd)
{
	if (my_strcmp(cmd, "echo"))
		return (1);
	else if (my_strcmp(cmd, "cd"))
		return (1);
	else if (my_strcmp(cmd, "pwd"))
		return (1);
	else if (my_strcmp(cmd, "export"))
		return (1);
	else if (my_strcmp(cmd, "unset"))
		return (1);
	else if (my_strcmp(cmd, "env"))
		return (1);
	else if (my_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

void	call_builtins(char **cmd)
{
	int	tmp_curr;

	tmp_curr = data()->curr_cmd + 1;
	if (data()->cmds[tmp_curr] != NULL && is_spc(data()->cmds[tmp_curr][0]))
		tmp_curr = fd_check(tmp_curr);
	if (my_strcmp(cmd[0], "echo"))
		ft_echo(cmd);
	else if (my_strcmp(cmd[0], "cd"))
		ft_cd(cmd);
	else if (my_strcmp(cmd[0], "pwd"))
		ft_pwd(cmd);
	else if (my_strcmp(cmd[0], "export"))
		ft_export();
	else if (my_strcmp(cmd[0], "unset"))
		ft_unset(data()->env_p, data()->cmds[data()->curr_cmd][1]);
	else if (my_strcmp(cmd[0], "env"))
		ft_env(data()->env_p);
	else if (my_strcmp(cmd[0], "exit"))
		ft_exit(cmd);
	data()->curr_cmd = tmp_curr;
	swap_fd();
}

void	clean_exit_child(void)
{
	free_all();
	swap_fd();
	swap_fd();
	exit(0);
}
