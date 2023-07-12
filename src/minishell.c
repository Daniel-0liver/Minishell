/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 20:52:54 by dateixei          #+#    #+#             */
/*   Updated: 2023/07/12 22:26:19 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*data(void)
{
	static t_data	data;

	return (&data);
}

static void	inthandler(int sig)
{
	(void) sig;
	data()->error = EOWNERDEAD;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int argc, char *argv[], char **envp)
{
	(void) argv;
	(void) argc;

	alloc_env(envp);
    data()->error = 0;
	ft_unset(data()->env_p, "SHELL");
	add_cd_to_env("SHELL=minishell");
	handle_shlvl('+');
	while (TRUE)
	{
		signal(SIGINT, inthandler);
		data()->str_cmd = readline("minishell: ");
		add_history(data()->str_cmd);
		if (ft_strncmp(data()->str_cmd, "exit", 5) == 0)
			break ;
        else if (ft_strncmp(data()->str_cmd, "$?", 3) == 0)
        {
			printf("%i\n",  data()->error);
            free(data()->str_cmd);
        }
        else
        {          
            parse_init();
            if (data()->str_cmd != NULL && *data()->str_cmd != '\0')
                free(data()->str_cmd);
            }
	}
	free(data()->str_cmd);
	free_double_ptr(data()->env_p);
	return (0);
}
