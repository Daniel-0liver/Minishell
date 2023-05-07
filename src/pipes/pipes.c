/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:16:32 by gateixei          #+#    #+#             */
/*   Updated: 2023/05/07 15:49:45 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_path(void)
{
	int		i;
	int		j;
	char	*rtn;
	char	*path;

	i = 0;
	while (data()->str_cmd[i] != '\0' && data()->str_cmd[i] != ' ') // Replace the currently str_cmd to cmd matriz when ready
	{
		if (data()->str_cmd[i] == '/')
			return (&data()->str_cmd[0]);
		i++;
	}
	rtn = malloc(sizeof(char) * (i + 5));
	path = "/bin/";
	j = -1;
	while (++j < 5)
		rtn[j] = path[j];
	i = 0;
	while (data()->str_cmd[i] != '\0' && data()->str_cmd[i] != ' ')
		rtn[j++] = data()->str_cmd[i++];
	rtn[j] = '\0';
	return (rtn);
}

void cmd_to_exec(void)
{
	char	*env[] = {NULL};
	char	*path_cmd;
	char	*flags; // Add flag use
	int		i;

	path_cmd = check_path(); 
	printf("Cheguei aqui - %s\n", path_cmd);
	execve(path_cmd, &data()->str_cmd, env);
	i = 0;
	while (data()->str_cmd[i] != '\0' && data()->str_cmd[i] != ' ') // Attention to this free
	{
		if (data()->str_cmd[i] == '/')
			break;
		i++;
		if (data()->str_cmd[i] == '\0' || data()->str_cmd[i] == ' ')
			free(path_cmd);
	}
}