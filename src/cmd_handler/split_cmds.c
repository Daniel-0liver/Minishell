/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:38:26 by gateixei          #+#    #+#             */
/*   Updated: 2023/06/10 18:12:01 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_spc(int size)
{
    int i;
    int mtz;
    int *spc;

    i = 0;
    mtz = 0;
    spc = malloc(sizeof(int) * (size));
	while (data()->test[i] != NULL)
	{
		// Add here String Compare for commands that send string (CD, ECHO...)
		if(data()->test[i][0] == '<' || data()->test[i][0] == '>'
		|| data()->test[i][0] == '|' || data()->test[i][0] == '&')
			spc[mtz++] = i;
		i++;
	}
    spc[mtz] = '\0';
    data()->spc = spc;
}

char	**ft_cmd(void)
{
	int 		i;
	int			size;
	char		**cmd;
	
	i = 0;
	if(is_spc(data()->test[data()->curr_cmd]))
		data()->curr_cmd++;
	size = ft_ptrlen(data()->curr_cmd);
	cmd = malloc((size + 1) * sizeof(char *));
	cmd[i] = check_path(data()->test[data()->curr_cmd]);
	data()->curr_cmd++;
	i++;
	while (--size > 0)
	{
		cmd[i] = ft_strdup(data()->test[data()->curr_cmd]);
		data()->curr_cmd++;
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}

int	ft_matriz_size(void)
{
	int	i;
	int	mtz;

	i = 0;
	mtz = 1;
	while (data()->test[i] != NULL)
	{
		// Add here String Compare for commands that send string (CD, ECHO...)
		if(is_spc(data()->test[i]))
			mtz++; // Save this index to later run pipes and commands
		i++;
	}
	return (mtz);
}

int	ft_ptrlen(int v)
{
	int i;

	i = 0;
	while (data()->test[v] != NULL)
	{
		// Add here String Compare for commands that send string (CD, ECHO...)
		if(is_spc(data()->test[v]))
			return (i);
		i++;
		v++;
	}
	return (i);
}

char	*check_path(char *cmds) // Change this to PATH variable
{
	int		i;
	int		j;
	char	*rtn;
	char	*path;

	i = 0;
    if (is_builtins(cmds))
        return (ft_strdup(cmds));
    if (data()->curr_cmd > 0 && (data()->test[data()->curr_cmd - 1][0] == '>' || data()->test[data()->curr_cmd - 1][0] == '<'))
        return (ft_strdup(cmds));
	while (cmds[i] != '\0' && cmds[i] != ' ')
	{
		if (cmds[i] == '/')
			return (ft_strdup(cmds));
		i++;
	}
	rtn = malloc(sizeof(char) * (i + 5));
	path = "/bin/";
	j = -1;
	while (++j < 5)
		rtn[j] = path[j];
	i = 0;
	while (cmds[i] != '\0' && cmds[i] != ' ')
		rtn[j++] = cmds[i++];
	rtn[j] = '\0';
	return (rtn);
}