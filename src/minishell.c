/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 20:52:54 by dateixei          #+#    #+#             */
/*   Updated: 2023/06/15 10:26:40 by dateixei         ###   ########.fr       */
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

    data()->env_p = envp;
	while (TRUE)
	{
		if (data()->str_cmd)
			free(data()->str_cmd);
		signal(SIGINT, inthandler);
		data()->str_cmd = readline("minihell: ");
		add_history(data()->str_cmd);
        if (ft_strcpm(data()->str_cmd, "exit"))
            break;
		parse_init();
	}
	free(data()->str_cmd);
	return (0);
}
