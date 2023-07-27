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
/*
int	is_echo_pipes(int tmp_cmd)
{
	while (data()->spc[tmp_cmd] != -1 \
	&& (is_redirect(data()->tokens[data()->spc[tmp_cmd]]) == 3 \
	|| is_redirect(data()->tokens[data()->spc[tmp_cmd]]) == 4))
		tmp_cmd++;
	if (data()->spc[tmp_cmd] == -1)
		return (1);
	return (0);
}
*/

void	call_builtins(char **cmd)
{
	if (my_strcmp(cmd[0], "echo"))
		ft_echo(cmd);
	else if (my_strcmp(cmd[0], "cd"))
		ft_cd(cmd);
	else if (my_strcmp(cmd[0], "pwd"))
		ft_pwd(cmd);
	else if (my_strcmp(cmd[0], "export"))
	{
		if (data()->cmds[data()->curr_cmd][1] != NULL)
			ft_export();
		else
			export_declare();
	}
	else if (my_strcmp(cmd[0], "unset"))
		ft_unset(data()->env_p, data()->cmds[data()->curr_cmd][1]);
	else if (my_strcmp(cmd[0], "env"))
		ft_env(data()->env_p);
	else if (my_strcmp(cmd[0], "exit"))
		ft_exit(cmd);
}
/*
void	call_builtins_exec(char **cmd)
{
	if (my_strcmp(cmd[0], "echo"))
		ft_echo_exec(cmd);
	else if (my_strcmp(cmd[0], "cd"))
		ft_cd(cmd);
	else if (my_strcmp(cmd[0], "pwd"))
		ft_pwd_exec(cmd);
	else if (my_strcmp(cmd[0], "export"))
	{
		if (data()->cmds[data()->curr_cmd][1] != NULL)
			ft_export();
		else
			export_declare_exec(data()->env_p);
	}
	else if (my_strcmp(cmd[0], "unset"))
		ft_unset(data()->env_p, data()->cmds[data()->curr_cmd][1]);
	else if (my_strcmp(cmd[0], "env"))
		ft_env_exec(data()->env_p);
	else if (my_strcmp(cmd[0], "exit"))
		ft_exit_exec(cmd);
}

*/