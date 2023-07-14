/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:35:28 by gateixei          #+#    #+#             */
/*   Updated: 2023/07/14 23:12:07 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtins_error(char *option, char *var_option, char *msg, int err)
{
	errno = err;
	data()->error = err;
	ft_putstr_fd("Minishell: ", 2);
	if (option != NULL)
		ft_putstr_fd(option, 2);
	if (var_option != NULL)
		ft_putstr_fd(var_option, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}
