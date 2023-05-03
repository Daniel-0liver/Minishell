/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 20:52:54 by dateixei          #+#    #+#             */
/*   Updated: 2023/05/03 22:52:26 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*data(void)
{
	static t_data data;

	return (&data);
}

static void	inthandler(int sig)
{
	(void) sig;
	rl_on_new_line();
	rl_replace_line("\n", 0);
	rl_redisplay();
}

int	main(int argc, char *argv[], char **envp)
{
	(void)	argv;
	(void)	argc;
	
	test();
	// char	*str;
	// while (1)
	// {
	// 	if (str)
	// 		free(str);
	// 	signal(SIGQUIT, SIG_IGN);
	// 	signal(SIGINT, inthandler);
	// 	str = readline("gabriel is gay: ");
	// 	add_history(str);
	// 	printf("%s\n", str);
	// }
	// free(str);
	return (0);
}