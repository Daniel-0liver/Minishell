/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:38:13 by dateixei          #+#    #+#             */
/*   Updated: 2023/06/20 02:11:50 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Main function of the parse unit
void	parse_init(void)
{
	// get_tokens();
	cmd_to_exec();
}

char	*my_getenv(char *str)
{
	int		str_len;
	int		i;
	char	*var;

	if (str == NULL || *str == '\0')
		return (NULL);
	str_len = ft_strlen(str);
	while (*data()->env_p)
	{
		var = *data()->env_p;
		i = 0;
		while (var[i] != '=' && var[i] != '\0')
			i++;
		if (var[i] == '=' && i == str_len && ft_strncmp(str, var, i) == 0)
			return (&var[i + 1]);
		data()->env_p++;
	}
	return (NULL);
}
