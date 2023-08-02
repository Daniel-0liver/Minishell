/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:18:53 by gateixei          #+#    #+#             */
/*   Updated: 2023/07/31 15:04:41 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	inthandler_doc(int sig)
{
	(void) sig;
	data()->error = EOWNERDEAD;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	handle_here(char *exit)
{
	int		fd;
	char	*str;
	char	*output;

	fd = 0;
	output = NULL;
	str = readline("> ");
	while (my_strcmp(str, exit) == 0)
	{
		signal(SIGINT, inthandler_doc);
		signal(SIGQUIT, SIG_IGN);
		output = strjoin_here(output, str);
		str = readline("> ");
		if (str == NULL)
			break ;
	}
	free(str);
	fd = open(TEMP_FILE, O_WRONLY | O_CREAT | O_ASYNC | O_TRUNC, 0644);
	ft_putstr_fd(output, fd);
	fd = open(TEMP_FILE, O_RDONLY | O_ASYNC);
	free(output);
	return (fd);
}

void	fd_heredoc(int tmp_curr)
{
	data()->fd[0][0] = handle_here(data()->cmds[tmp_curr][1]);
	unlink(TEMP_FILE);
}
