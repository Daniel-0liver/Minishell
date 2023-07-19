/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:35:28 by gateixei          #+#    #+#             */
/*   Updated: 2023/07/19 21:52:11 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtins_error(char *option, char *var_option, char *msg, int err)
{
	errno = err;
	data()->error = err;
	ft_putstr_fd("Minishell: ", 2);
	if (option != NULL)
		ft_putstr_fd(option, 2);
	if (var_option != NULL)
		ft_putstr_fd(var_option, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

void	error_exec(void)
{
	int		i;

	i = 0;
	while (data()->cmds[data()->curr_cmd][0][i] != '\0')
	{
		if (data()->cmds[data()->curr_cmd][0][i] == '/')
			{
				if (chdir(data()->cmds[data()->curr_cmd][0]) < 0)
				{
					if (!(access(data()->cmds[data()->curr_cmd][0], R_OK) == 0) && errno == EACCES)
					{
						builtins_error(NULL, data()->cmds[data()->curr_cmd][0], ": Permission denied", 1);
						free_all();
						exit(126);	
					}
					else
						builtins_error("cd: ", data()->cmds[data()->curr_cmd][0], ": No such file or directory", 127);
					free_all();
					exit(127);
				}
				else
				{
					builtins_error("cd: ", data()->cmds[data()->curr_cmd][0], ": Is a directory", 126);
					free_all();
					exit(126);
				}
			}
		i++;
	}
	builtins_error(NULL, data()->cmds[data()->curr_cmd][0],\
	": command not found", 127);
	free_all();
	exit(127);
}
