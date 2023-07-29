/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 22:15:35 by dateixei          #+#    #+#             */
/*   Updated: 2023/07/28 23:27:37 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_size(char ***str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	***join_cmd(char ***cmd, char **str)
{
	char	***cmd_tmp;

	cmd_tmp = malloc((cmd_size(data()->cmds) + 1) * sizeof(char **));
}

char	***handle_input_output_signals(char	**str, int *i)
{
	char	**str_tmp;
	char	***cmd_tmp;

	if (str[*i + 1])
	{
		*string *string
		str_tmp = ft_strjoin(str[*i], str[*i + 1]);
		cmd_tmp = join_cmd(data()->cmds, str_tmp);
		(*i) += 2;
	}
	else
	{
		
	}
}

//While token != | (pipe) check the - (flags)
// ls > output -la
// Matriz:
// {"ls", "-la"};
// {">", "output"}
void	ft_get_cmds(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data()->cmds = (char***)malloc(sizeof(char***));
	data()->cmds[0] = NULL;
	while (str[i])
	{
		if (ft_strncmp(str[i], ">", 2) == 0 
			|| ft_strncmp(str[i], "<", 2) == 0
			|| ft_strncmp(str[i], ">>", 3) == 0
			|| ft_strncmp(str[i], "<<", 3) == 0)
		data()->cmds = handle_input_output_signals(str, &i);
	}
}