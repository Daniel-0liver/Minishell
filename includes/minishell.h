/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 20:53:15 by dateixei          #+#    #+#             */
/*   Updated: 2023/05/25 19:56:40 by gateixei         ###   ########.fr       */
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
# define DELIM " \n\t"
# define TRUE 1
# define FALSE 0

typedef struct s_data
{
	char		*token;
	char		*str_cmd;
	char		**cmds;
	char    	**test;
	int			curr_cmd;
	int         fd[2];
}			t_data;

//Data init
t_data	*data(void);

// Parse_utils
void	get_token(void);
char	*ft_strchr(const char *s, int c);

// Parse_init
void	parse_init(void);

//split_cmds
int		ft_matriz_size(void);
int		ft_ptrlen(int v);
char	*check_path(int v);

// cmds
char	***get_cmds(void);
void    cmd_to_exec(void);

// cmds_utils
char	*ft_strdup(const char *src);
# endif