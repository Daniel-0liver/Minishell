/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:16:32 by gateixei          #+#    #+#             */
/*   Updated: 2023/07/27 13:49:20 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    call_spc(void)
{
	if (my_strcmp(cmd, "|"))
		return ;
	else if (my_strcmp(cmd, ">"))
		return ;
	else if (my_strcmp(cmd, ">>"))
		return ;
	else if (my_strcmp(cmd, "<"))
		return ;
	else if (my_strcmp(cmd, "<<"))
		return ;
}

void	execute_cmd(void)
{
	int	pid;
	int	status;
	
	pid = fork();
	if (pid == 0)
	{	
		if (data()->fd[0] < 0)
			close(data()->fd[0]);
		if (data()->fd[1] < 0)
			close(data()->fd[1]);
		dup2(data()->fd[0], STDIN_FILENO);
		dup2(data()->fd[1], STDOUT_FILENO);
		if (execve(check_path(data()->cmds[data()->curr_cmd][0]), \
		data()->cmds[data()->curr_cmd], data()->env_p) == -1)
			error_exec();
	}
	else
	{
		waitpid(pid, &status, 0);
		if (data()->fd[0] != 0)
			close(data()->fd[0]);
		if (data()->fd[1] != 1)
			close(data()->fd[1]);
		if (status > 0)
			data()->error = status / 256;
		else
			data()->error = 0;
	}
}

void	generate_fds(void)
{
	data()->fd = malloc(sizeof(int) * 2);
	pipe(data()->fd);
	data()->fd[0] = STDIN_FILENO;
	data()->fd[1] = STDOUT_FILENO;
}

void	cmd_to_exec(void)
{
	char	*test[] = {"ls", "-la", NULL};
	char	*test2[] = {"|", NULL};
	char	*test3[] = {"grep", "Make", NULL};
	data()->cmds = malloc(sizeof(char *) * 4);
	data()->cmds[0] = test;
	data()->cmds[1] = test2;
	data()->cmds[2] = test3;
	data()->cmds[3] = NULL;
	generate_fds();
	data()->curr_cmd = 0;
	while (data()->cmds && data()->cmds[data()->curr_cmd] != NULL)
	{
		if (is_builtins(data()->cmds[data()->curr_cmd][0]))
			call_builtins(data()->cmds[data()->curr_cmd]);
		else
			execute_cmd();
		data()->curr_cmd++;
	}
}
