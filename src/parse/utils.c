/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:06:25 by dateixei          #+#    #+#             */
/*   Updated: 2023/06/21 18:29:51 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strjoin_here(char *s1, char *s2)
{
	char	*s_final;
	size_t	size;
	size_t	i;
	size_t	j;

	size = ft_strlen(s1) + ft_strlen(s2);
	s_final = (char *)malloc(size + 2);
	if (!s_final)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		s_final[i] = s1[i];
		i++;
	}
	j = 0;
	while (i < size)
		s_final[i++] = s2[j++];
	s_final[i++] = '\n';
	s_final[i] = '\0';
	free(s1);
	free(s2);
	return (s_final);
}
