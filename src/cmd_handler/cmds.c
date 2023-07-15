/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:16:32 by gateixei          #+#    #+#             */
/*   Updated: 2023/07/15 13:13:46 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Change all data()->tokens for the real string received by the parse

int	is_valid(void)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data()->tokens[i] != NULL)
	{
		if (i == 0 && is_exec(data()->tokens[i]) == 1)
		{
			builtins_error(NULL, NULL, \
			"bash: syntax error near unexpected token `|'", 2);
			return (1);
		}
		if (is_spc(data()->tokens[i]))
		{
			j--;
			if (data()->tokens[i + 1] != NULL && is_spc(data()->tokens[i + 1]))
				return (1);
		}
		else
			j++;
		i++;
	}
	if (j >= 0)
		return (0);
	else
		return (1);
}

void	exec_type_end(void)
{
	if (is_exec(data()->tokens[data()->spc[data()->curr_cmd - 1]]) \
	&& data()->spc[data()->curr_cmd] == -1)
		ft_exec_pipe_end();
	else if (data()->spc[data()->curr_cmd] != -1 && \
	is_redirect(data()->tokens[data()->spc[data()->curr_cmd]]) == 1)
		ft_red_end();
	else if (data()->spc[data()->curr_cmd] != -1 && \
	is_redirect(data()->tokens[data()->spc[data()->curr_cmd]]) == 2)
		ft_red_end();
}

void	exec_type_md(void)
{
	if (is_exec(data()->tokens[data()->spc[data()->curr_cmd]]) == 1)
		ft_exec_pipe_md();
	else if (is_redirect(data()->tokens[data()->spc[data()->curr_cmd]]) == 1)
		ft_red_end();
	else if (is_redirect(data()->tokens[data()->spc[data()->curr_cmd]]) == 2)
		ft_red_end();
}

void	exec_type(void)
{
	if (is_exec(data()->tokens[data()->spc[data()->curr_cmd]]) == 1)
		ft_exec();
	else if (is_redirect(data()->tokens[data()->spc[data()->curr_cmd]]) == 1)
		ft_red();
	else if (is_redirect(data()->tokens[data()->spc[data()->curr_cmd]]) == 2)
		ft_red();
	else if (is_redirect(data()->tokens[data()->spc[data()->curr_cmd]]) == 3)
		ft_input();
	else if (is_redirect(data()->tokens[data()->spc[data()->curr_cmd]]) == 4)
		ft_input();
}

void	check_spc(void)
{
	generate_fds();
	exec_type();
	while (data()->spc && data()->spc[data()->curr_cmd] != -1)
	{
		if (data()->error != 0)
			return ;
		exec_type_md();
	}
	if (data()->error != 0)
	{
		return ;
	}
	exec_type_end();
}

void cmd_to_exec(void)
{
	int		pid;
	int		status;

	status = 0;
	if (is_valid())
		return ;
	data()->cmds = get_cmds();
	data()->curr_cmd = 0;
	data()->curr_fd = 0;
	if (data()->spc && data()->spc[data()->curr_cmd] != -1)
	{
		check_spc();
		free_all();
	}
	else
	{
		if (is_builtins(data()->cmds[data()->curr_cmd][0]))
			call_builtins_exec(data()->cmds[data()->curr_cmd]);
		else
		{
			pid = fork();
			if (pid == 0)
			{	
				if (execve(data()->cmds[data()->curr_cmd][0], \
				data()->cmds[data()->curr_cmd], data()->env_p) == -1)
				{
					printf("%s: command not found\n", \
					data()->cmds[data()->curr_cmd][0]);
					exit(127);
				}
			}
			else
				waitpid(pid, &status, 0);
			if (status > 0)
				data()->error = status / 256;
			else
				data()->error = 0;
		}
		free_exec();
	}
}
