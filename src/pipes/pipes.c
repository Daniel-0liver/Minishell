/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:16:32 by gateixei          #+#    #+#             */
/*   Updated: 2023/05/09 23:25:40 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_cmds(void)
{
	int	i;

	i = 0;
	while (data()->test[i] != NULL)
	{
		if (data()->test[i][0] == '|')
			printf("Thats a pipe\n");
		else if (data()->test[i][0] == '<')
			printf("Thats an input\n");
		else if (data()->test[i][0] == '>')
			printf("Thats an output\n");
		else if (data()->test[i][0] == '$')
			printf("Thats a dollar sign\n");
		i++;
	}
}

char	*check_path(void)
{
	int		i;
	int		j;
	char	*rtn;
	char	*path;

	i = 0;
	while (data()->test[0][i] != '\0' && data()->test[0][i] != ' ') // Replace the currently test[0] to cmd matriz when ready
	{
		if (data()->test[0][i] == '/')
			return (&data()->test[0][0]);
		i++;
	}
	rtn = malloc(sizeof(char) * (i + 5));
	path = "/bin/";
	j = -1;
	while (++j < 5)
		rtn[j] = path[j];
	i = 0;
	while (data()->test[0][i] != '\0' && data()->test[0][i] != ' ')
		rtn[j++] = data()->test[0][i++];
	rtn[j] = '\0';
	return (rtn);
}

void cmd_to_exec(void)
{
	char    *test2[] = {"ls", "-la", ">", NULL}; //erase this later
	data()->test = test2; //erase this later
	char	*env[] = {NULL};
	char	*path_cmd;
	int		i;
	int     pid;

	path_cmd = check_path();  //Chck this use when 
	check_cmds();
	pid = fork();
	if (pid == 0)
		execve(path_cmd, data()->test, env);
	waitpid(pid, NULL, 0);
	i = 0;
	while (data()->test[0][i] != '\0' && data()->test[0][i] != ' ') // Attention to this free
	{
		if (data()->test[0][i] == '/')
			break;
		i++;
		if (data()->test[0][i] == '\0' || data()->test[0][i] == ' ')
			free(path_cmd);
	}
}