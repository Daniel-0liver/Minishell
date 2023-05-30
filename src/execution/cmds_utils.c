/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:13:36 by gateixei          #+#    #+#             */
/*   Updated: 2023/05/30 20:06:29 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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