/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 00:35:46 by gateixei          #+#    #+#             */
/*   Updated: 2023/07/18 19:09:26 by gateixei         ###   ########.fr       */
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

int	ft_input_check(int tmp_cmd)
{
	int	tmp_fd;

	while (data()->spc[tmp_cmd] != -1 \
	&& data()->tokens[data()->spc[data()->curr_cmd]][0] == '<' \
	&& data()->tokens[data()->spc[tmp_cmd]][0] == '<')
	{
		if (is_redirect(data()->tokens[data()->spc[tmp_cmd - 1]]) == 3)
			tmp_fd = open(data()->cmds[tmp_cmd][0], O_RDONLY);
		else
			tmp_fd = handle_here(data()->cmds[tmp_cmd][0]);
		if (tmp_fd < 0)
		{
			builtins_error(NULL, data()->cmds[tmp_cmd][0], \
			": No such file or directory", 1);
			return (tmp_cmd);
		}
		close(tmp_fd);
		tmp_cmd++;
	}
	if (is_redirect(data()->tokens[data()->spc[tmp_cmd - 1]]) == 3)
		(data()->fd[data()->curr_fd][0]) = \
		open(data()->cmds[tmp_cmd][0], O_RDONLY);
	else
		data()->fd[data()->curr_fd][0] = handle_here(data()->cmds[tmp_cmd][0]);
	if (data()->fd[data()->curr_fd][0] < 0)
		builtins_error(NULL, data()->cmds[tmp_cmd][0],\
		": No such file or directory", 1);
	return (tmp_cmd);
}

int	ft_red_input_check(int tmp_cmd)
{
	int	tmp_fd;

	while (data()->spc[tmp_cmd] != -1 && data()->tokens[data()->spc[tmp_cmd]] \
	&& data()->tokens[data()->spc[tmp_cmd]][0] == '>')
	{
		if (is_redirect(data()->tokens[data()->spc[tmp_cmd - 1]]) == 1)
			tmp_fd = open(data()->cmds[tmp_cmd][0], \
			O_RDWR | O_CREAT | O_TRUNC, 0664);
		else if (is_redirect(data()->tokens[data()->spc[tmp_cmd - 1]]) == 2)
			tmp_fd = open(data()->cmds[tmp_cmd][0], \
			O_RDWR | O_CREAT | O_APPEND, 0664);
		if (tmp_fd < 0)
			printf("Error to create/read the redirected file named: %s\n", \
			data()->cmds[tmp_cmd][0]);
		close(tmp_fd);
		tmp_cmd++;
	}
	return (tmp_cmd);
}

int	ft_red_loop_checker(int tmp_cmd)
{
	int	tmp_fd;

	while (data()->spc[tmp_cmd] != -1 && data()->tokens[data()->spc[tmp_cmd]] \
	&& data()->tokens[data()->spc[data()->curr_cmd]][0] == '>' \
	&& data()->tokens[data()->spc[tmp_cmd]][0] == '>')
	{
		if (is_redirect(data()->tokens[data()->spc[tmp_cmd - 1]]) == 1)
			tmp_fd = open(data()->cmds[tmp_cmd][0], \
			O_RDWR | O_CREAT | O_TRUNC, 0664);
		else if (is_redirect(data()->tokens[data()->spc[tmp_cmd - 1]]) == 2)
			tmp_fd = open(data()->cmds[tmp_cmd][0], \
			O_RDWR | O_CREAT | O_APPEND, 0664);
		if (tmp_fd < 0)
			printf("Error to create/read the redirected file named: %s\n", \
			data()->cmds[tmp_cmd][0]);
		close(tmp_fd);
		tmp_cmd++;
	}
	return (tmp_cmd);
}
