/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 13:23:12 by dateixei          #+#    #+#             */
/*   Updated: 2023/07/15 17:34:33 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_dollar_sign(char *str)
{
	int	i;

	i = 0;
	str++;
	handle_env(str);
	while (str[i] && str[i] != ' ' && str[i] != '\n' && str[i] != '\t'
		&& str[i] != '|' && str[i] != '<' && str[i] != '>' && str[i] != '$')
	{
		i++;
		if (str[i - 1] == '?')
			break ;
	}
	if (!data()->str_tmp)
		data()->warning = -1;
	return (i);
}

int	check_special_char(int i)
{
	if (data()->tokens[i] && ft_strncmp(data()->tokens[i], "|", 2)
		!= 0 && ft_strncmp(data()->tokens[i], ">", 2) != 0
		&& ft_strncmp(data()->tokens[i], "<", 2) != 0
		&& ft_strncmp(data()->tokens[i], "|", 2) != 0
		&& ft_strncmp(data()->tokens[i], "\'", 2) != 0
		&& ft_strncmp(data()->tokens[i], "\"", 2) != 0
		&& ft_strncmp(data()->tokens[i], ">>", 3)
		&& ft_strncmp(data()->tokens[i], "<<", 3))
		return (0);
	else
		return (1);
}

void	check_echo(void)
{
	int	i;

	i = 0;
	while (data()->tokens[i] != NULL)
	{
		if ((ft_strncmp(data()->tokens[i], "echo", 5) == 0)
			&& data()->tokens[i + 1] != NULL)
		{
			if (ft_strncmp(data()->tokens[i + 1], "-n", 3) == 0)
				i += 2;
			else
				i++;
			while (check_special_char(i) == 0)
			{
				if (data()->tokens[i + 1] == NULL)
					break ;
				else
					(data()->tokens[i]) = strjoin_var(data()->tokens[i], ' ');
				i++;
			}
		}
		i++;
	}
}

void	handle_shlvl(char c)
{
	int		shlvl;
	char	*str;
	char	*nbr;
	char	*env;

	env = my_getenv("SHLVL");
	shlvl = ft_atoi(env);
	if (c == '-')
		shlvl--;
	else if (c == '+')
		shlvl++;
	nbr = ft_itoa(shlvl);
	str = ft_strjoin("SHLVL=", nbr);
	ft_unset(data()->env_p, "SHLVL");
	add_cd_to_env(str);
	free(nbr);
	free(str);
	free(env);
}

int	token_is_space(char *str, int *i)
{
	if (str[1] != ' ' && str[1] != '\n' && str[1] != '\t')
		(*i)++;
	return (1);
}
