/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 20:53:15 by dateixei          #+#    #+#             */
/*   Updated: 2023/06/12 11:40:26 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>    //  write, dup2, close
# include <fcntl.h>     //  O_RDONLY, O_...
# include <stdlib.h>    //  EXIT_FAILURE, malloc, free
# include <stdio.h>     //  STDIN
# include <sys/types.h> //	wait
# include <sys/wait.h>	//	wait
# include <errno.h>		//	ERROR
# include <signal.h>	//	SIG
# include <readline/readline.h>	//	ReadLine
# include <readline/history.h>	//	History
# define TRUE 0
# define FALSE 1

typedef struct s_data
{
	int			nbr_pipe_sig;
	int			nbr_tokes;
	char		**tokens;
	char		*str_cmd;
	char		***cmds;
}			t_data;

//Data init
t_data	*data(void);

// Parse_utils
int		get_tokens(void);
int		nbr_char(char	*str, char	c);
char	*ft_strchr(const char *s, int c);

// Parse_init
void	parse_init(void);

// Parse_quotes
int		check_quotes(char *str);
char	*handle_quote(char	*str, char c);

# endif
