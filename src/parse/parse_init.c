/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:38:13 by dateixei          #+#    #+#             */
/*   Updated: 2023/07/12 22:38:42 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Main function of the parse unit
void	parse_init(void)
{
	// int	i;

	if (get_tokens() == 0)
		return ;
	// i = 0;
	// while (data()->tokens[i])
	// 	printf("%s\n", data()->tokens[i++]);
	if (data()->tokens)
		cmd_to_exec();
}

char	*my_getenv(char *str)
{
	int		size;
	int		i;
	int		j;
	char	*tmp;

	if (str == NULL || *str == '\0')
		return (NULL);
	size = ft_strlen(str);
	j = 0;
	while (data()->env_p[j])
	{
		tmp = data()->env_p[j];
		i = 0;
		while (tmp[i] != '=' && tmp[i] != '\0')
			i++;
		if (tmp[i] == '=' && i == size && ft_strncmp(str, tmp, i) == 0)
			return (&tmp[i + 1]);
		j++;
	}
	return (NULL);
}
