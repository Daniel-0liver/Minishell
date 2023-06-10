/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:12:11 by gateixei          #+#    #+#             */
/*   Updated: 2023/06/10 13:56:22 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_echo(char **str)
{
	int	i;
	
	if (ft_strcpm(str[1], "-n"))
		while(str[2] && str[2][i] != '\0')
			write(1, &str[2][i++], 1);
	else
	{
		while(str[1] && str[1][i] != '\0')
			write(1, &str[1][i++], 1);
		write(1, "\n", 1);
	}
}