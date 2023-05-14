/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:16:32 by gateixei          #+#    #+#             */
/*   Updated: 2023/05/14 17:17:02 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ptrlen(void)
{
	int	i;

	i = 0;
	while (data()->test[i] != NULL)
		i++;
	return (i);
}

char	*ft_strdup(const char *src)
{
	char	*new;
	int		i;
	int		size;

	size = 0;
	while (src[size])
		++size;
	if (!(new = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = 0;
	while (src[i])
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	**check_cmds(void)
{
	int		i;
	int		j;
	int		curr;
	int		pid;
	char	**cmds;

	i = 0;
	curr = 0;
	pid = 0;
	cmds = malloc(sizeof(char *) * ft_ptrlen());
	while (data()->test[i] != NULL)
	{
		if (data()->test[i][0] == '|')
		{
			if (data()->test[i][1] == '|')
				printf("Thats a OR sign\n");
			else
			{
				pid = fork();
				if (pid == 0)
				{
					printf("Thats a pipe\n");
					execve(cmds[0], cmds, NULL);
				}
			}
		}
		else if (data()->test[i][0] == '<')
		{
			if (data()->test[i][1] == '<')
				printf("smaller than sign");
			else
				printf("Thats an input\n");
		}
		else if (data()->test[i][0] == '>')
		{
			if (data()->test[i][1] == '>')
				printf("Bigger than sign");
			else
				printf("Thats an output\n");
		}
		else if (data()->test[i][0] == '$')
			printf("Thats a dollar sign\n");
		else if (data()->test[i][0] == '&' && data()->test[i][1] == '&')
			printf("Thats a AND sign\n");
		else if (data()->test[i][0] == '-')
			cmds[curr++] = ft_strdup(data()->test[i]);
		else
			cmds[curr++] = check_path(i);
		i++;
	}
	cmds[curr] = NULL;
	return (cmds);
}

char	*check_path(int v)
{
	int		i;
	int		j; 
	char	*rtn;
	char	*path;

	i = 0;
	while (data()->test[v][i] != '\0' && data()->test[v][i] != ' ') // Replace the currently test[0] to cmd matriz when ready
	{
		if (data()->test[v][i] == '/')
			return (&data()->test[v][0]);
		i++;
	}
	rtn = malloc(sizeof(char) * (i + 5));
	path = "/bin/"; // Change this to PATH variable
	j = -1;
	while (++j < 5)
		rtn[j] = path[j];
	i = 0;
	while (data()->test[v][i] != '\0' && data()->test[v][i] != ' ')
		rtn[j++] = data()->test[v][i++];
	rtn[j] = '\0';
	return (rtn);
}

int	check_free(void)
{
	int		i;
	
	i = 0;
	while (data()->test[0][i] != '\0' && data()->test[0][i] != ' ') // Attention to this free
	{
		if (data()->test[0][i] == '/')
			return 0;
		i++;
		if (data()->test[0][i] == '\0' || data()->test[0][i] == ' ')
			return 1;
	}
	return 1;
}

// Changed all data()->test for the real string received by the parse

void cmd_to_exec(void)
{
	char    *test2[] = {"ls", "-l", "|", NULL}; //erase this later
	data()->test = test2; //erase this later -> Changed all data()->test for the real string received by the parse
	// char	*env[] = {NULL};
	// char	*path_cmd;
	char	**cmds;
	int     pid;

	pid = fork();
	if (pid == 0)
	{	
		cmds = check_cmds();
		execve(cmds[0], cmds, NULL);
	}
	waitpid(pid, NULL, 0);
	// if (check_free())
	// 	free(path_cmd);
}
