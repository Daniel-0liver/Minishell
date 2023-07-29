/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 22:15:35 by dateixei          #+#    #+#             */
/*   Updated: 2023/07/29 23:04:08 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_array_size(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_matrix_size(char ***str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void free_matrix(char ***cmd)
{
	int	i;
	int	j;
	
	i = 0;
	while (cmd[i]) 
	{
		j = 0;
		while (cmd[i][j])
		{
			free(cmd[i][j]);
			j++;
		}
		free(cmd[i]);
		cmd[i] = NULL;
		i++;
	}
	free(cmd);
	cmd = NULL;
}

char	**join_array(char **str1, char *str2)
{
	int		i;
	char	**str_out;

	i = 0;
	str_out = (char **)malloc((ft_array_size(str1) + 2) * sizeof(char *));
	while (str1[i])
	{
		str_out[i] = ft_strdup(str1[i]);
		i++; 
	}
	str_out[i++] = ft_strdup(str2);
	str_out[i] = NULL;
	return (str_out);
}

char	***join_matrix(char ***cmd, char **str)
{
	int		i;
	int 	j;
	int		cmd_size;
	char	***cmd_out;

	cmd_size = ft_matrix_size(cmd) + 2;
	cmd_out = (char ***)malloc(cmd_size * sizeof(char **));
	i = 0;
	j = 0;
	while (cmd[i])
	{
		j = 0;
		cmd_out[i] = (char **)malloc((ft_array_size(cmd[i]) + 1) * sizeof(char *));
		while (cmd[i][j])
		{
			cmd_out[i][j] = ft_strdup(cmd[i][j]);
			j++;
		}
		cmd_out[i][j] = NULL;
		i++;
	}
	j = 0;
	cmd_out[i] = (char **)malloc((ft_array_size(str) + 1) * sizeof(char *));
	while (str[j])
	{
		cmd_out[i][j] = ft_strdup(str[j]);
		j++;
	}
	cmd_out[i][j] = NULL;
	cmd_out[++i] = NULL;
	if (cmd != NULL)
		free_matrix(cmd);
	return (cmd_out);
}

void	handle_input_output_signals(char **str, int *i)
{
	char	**str_tmp;

	str_tmp = malloc(sizeof(char *));
	str_tmp[0] = NULL;
	if (str[*i + 1] == NULL)
	{
		(*i)++;
	}
	else
	{
		str_tmp = join_array(str_tmp, str[*i]);
		str_tmp = join_array(str_tmp, str[*i + 1]);
		data()->cmds = join_matrix(data()->cmds, str_tmp);
		free_double_ptr(str_tmp);
		(*i) += 2;
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
	char	**str_tmp;

	i = 0;
	data()->cmds = malloc(sizeof(char **));
	data()->cmds[0] = NULL;
	while (str[i])
	{
		str_tmp = malloc(sizeof(char *));
		str_tmp[0] = NULL;
		if (ft_strncmp(str[i], ">", 2) == 0 
			|| ft_strncmp(str[i], "<", 2) == 0
			|| ft_strncmp(str[i], ">>", 3) == 0
			|| ft_strncmp(str[i], "<<", 3) == 0)
			handle_input_output_signals(str, &i);
		else if (ft_strncmp(str[i], "|", 2) == 0)
		{
			str_tmp = join_array(str_tmp, str[i]);
			data()->cmds = join_matrix(data()->cmds, str_tmp);
			i++;
		}
		else
		{
			while (str[i]
			&& ft_strncmp(str[i], ">", 2) != 0 
			&& ft_strncmp(str[i], "<", 2) != 0
			&& ft_strncmp(str[i], ">>", 3) != 0
			&& ft_strncmp(str[i], "<<", 3) != 0
			&& ft_strncmp(str[i], "|", 2) != 0)
			{
				str_tmp = join_array(str_tmp, str[i]);
				i++;
			}
			data()->cmds = join_matrix(data()->cmds, str_tmp);
		}
	}
}
// ls > file -a -b | grep Makefile < filename
// ls > file -a -b >file2 -c -d
// ({ls}{-la}{-a}{-b}[-c][-d])
// {>}{file}{null}
// {>}{file2}{null}
// {null}

// > FILE
// cat file 
// ls -l -a