/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:38:26 by gateixei          #+#    #+#             */
/*   Updated: 2023/05/24 18:38:48 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				printf("Thats a pipe\n");
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