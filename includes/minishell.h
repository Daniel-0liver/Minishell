/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 20:53:15 by dateixei          #+#    #+#             */
/*   Updated: 2023/05/30 20:06:45 by gateixei         ###   ########.fr       */
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
	char    	**test;
	char        ***cmds;
	int         **fd;
	int			*spc;
	int			curr_cmd;
	int			curr_spc;
}			t_data;

//Data init
t_data	*data(void);

// Parse_utils
void	get_token(void);
char	*ft_strchr(const char *s, int c);

// Parse_init
void	parse_init(void);

//split_cmds
void	ft_spc(int size);
char	**ft_cmd(void);
int		ft_matriz_size(void);
int		ft_ptrlen(int v);
char	*check_path(char *cmd);

// cmds
void	check_spc(void);
char	***get_cmds(void);
void    cmd_to_exec(void);

// ft_exec
void	ft_exec(void);
void    ft_exec_pipe_md(void);
void	ft_exec_pipe_end(void);

// cmds_utils
void	generate_fds(void);
char	*ft_strdup(const char *src);
# endif