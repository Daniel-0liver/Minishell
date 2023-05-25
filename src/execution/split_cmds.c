/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:38:26 by gateixei          #+#    #+#             */
/*   Updated: 2023/05/25 20:00:11 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_matriz_size(void)
{
	int	i;
	int	mtz;

	i = 0;
	mtz = 1;
	while (data()->test[i] != NULL)
	{
		// Add here String Compare for commands that send string (CD, ECHO...)
		if(data()->test[i][0] == '<' || data()->test[i][0] == '>'
		|| data()->test[i][0] == '|' || data()->test[i][0] == '&')
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
		if(data()->test[v][0] == '<' || data()->test[v][0] == '>'
		|| data()->test[v][0] == '|' || data()->test[v][0] == '&')
            return (i);
		i++;
        v++;
    }
	return (i);
}

char	*check_path(int v) // Change this to PATH variable
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
	path = "/bin/";
	j = -1;
	while (++j < 5)
		rtn[j] = path[j];
	i = 0;
	while (data()->test[v][i] != '\0' && data()->test[v][i] != ' ')
		rtn[j++] = data()->test[v][i++];
	rtn[j] = '\0';
	return (rtn);
}