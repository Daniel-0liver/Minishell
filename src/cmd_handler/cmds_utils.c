/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:13:36 by gateixei          #+#    #+#             */
/*   Updated: 2023/06/21 15:40:54 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_spc(char *cmd)
{
	if (ft_strcpm(cmd, "|"))
		return (1);
	else if (ft_strcpm(cmd , "||"))
		return (1);
	else if (ft_strcpm(cmd, ">"))
		return (1);
	else if (ft_strcpm(cmd , ">>"))
		return (1);
	else if (ft_strcpm(cmd, "<"))
		return (1);
	else if (ft_strcpm(cmd , "<<"))
		return (1);
	else if (ft_strcpm(cmd, "&&"))
		return (1);
	else if (ft_strcpm(cmd , "*"))
		return (1);
	return (0);
}

int	ft_strcpm(char *s1, char *s2)
{
	int	i;
	
	i = 0;
	while (s1 && s2 && s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i] != s2[i])
		return (0);
	return (1);
}

void	generate_fds(void)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data()->spc && data()->spc[i] != '\0')
		i++;
	data()->fd = malloc(sizeof (int *) * (i + 1));
	while (j < i)
	{
		data()->fd[j] = malloc(sizeof(int) * 3);
		pipe(data()->fd[j]);
		data()->fd[j][2] = '\0';
		j++;
	}
	data()->fd[j] = NULL;
}

char	***get_cmds(void)
{
	int     curr;
	int		size;
	char	***cmds;

	curr = 0;
	data()->curr_cmd = 0;
	size = ft_matriz_size();
	if (size > 1)
		ft_spc(size);
	cmds = malloc((size + 1) * sizeof(char *));
	while (size-- > 0)
		cmds[curr++] = ft_cmd();
	cmds[curr] = NULL;
	return (cmds);
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