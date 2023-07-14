/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:43:43 by gateixei          #+#    #+#             */
/*   Updated: 2023/07/14 19:04:57 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long int	ft_atoli(const char *nptr)
{
	int	i;
	long long int	result;
	int	sing;
	int	size;
    
	i = 0;
	sing = 1;
	result = 0;
	size = 0;
	while (nptr[i] && (nptr[i] == '\f' || nptr[i] == ' ' || nptr[i] == '\n'
			|| nptr[i] == '\r' || nptr[i] == '\t' || nptr[i] == '\v'))
		i++;
	if (nptr[i] && (nptr[i] == '-' || nptr[i] == '+'))
	{
		if (nptr[i] == '-')
			sing *= -1;
		i++;
	}
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		result = result * 10 + (nptr[i] - '0');
		size++;
		if (size == 19)
		{
			if (sing == -1)
			{
				if (nptr[i] > '8')
					return (0);
			}
			else
				if (nptr[i] > '7')
					return (0);
		}
		if (size > 19)
			return (0);
		i++;
	}
	return (result * sing);
}

void    ft_exit(char **str)
{
	(void) str;

	data()->error = 2;
}

void    ft_exit_exec(char **str)
{
	long long int i;
	
	i = 0;
	printf("exit\n");
	if (str[1] != NULL && str[2] != NULL)
	{
		i = 1;
		builtins_error(NULL, NULL, "exit: too many arguments", i);
	}
	else if (str[1] != NULL)
	{
		i = ft_atoli(str[1]);
		if ((!ft_isdigit(str[1][0]) && str[1][0] != '-' && str[1][0] != '+') \
		|| (i == 0 && (!ft_strcpm(str[1], "0") || !ft_strcpm(str[1], "+0"))) \
		|| (i == -1 && !ft_strcpm(str[1], "-1")))
		{
			i = 2;
			builtins_error("exit: ", str[1], ": numeric argument required", i);         
		}
	}
	free_exec();
	free(data()->str_cmd);
	free_double_ptr(data()->env_p);
	exit(i);
}