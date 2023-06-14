/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:38:13 by dateixei          #+#    #+#             */
/*   Updated: 2023/06/14 16:37:05 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

// Main function of the parse unit
void	parse_init(void)
{
	get_tokens();
	printf("%s\n", data()->str_cmd);
	get_tokens();
    cmd_to_exec();
}
