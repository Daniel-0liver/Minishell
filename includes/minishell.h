/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 20:53:15 by dateixei          #+#    #+#             */
/*   Updated: 2023/06/21 16:14:25 by dateixei         ###   ########.fr       */
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
# include "../libft/include/libft.h"
# define TRUE 1
# define FALSE 0
# define GREEN "\033[0;32m"

typedef struct s_data
{
	int			nbr_tokes;
	char		**tokens;
	char		*str_cmd;
	char		**env_p;
	char		***cmds;
	int			**fd;
	int			*spc;
	int			curr_cmd;
	int			curr_fd;
	int			warning;
	char		**here_doc;
}			t_data;

//Data init
t_data	*data(void);

// Parse_utils
int		get_tokens(void);
int		nbr_char(char *str, char c);
char	**alloc_tokens(char *str, int nbr_tokens);

// Parse_init
void	parse_init(void);
char	*my_getenv(char *str);

// Parse_quotes
int		check_quotes(char *str);
int		nbr_outside_quotes(char *str);
int		nbr_inside_quotes(char *str, char c);
char	*check_envp(char	*str);
char	*handle_quote(char	*str, char c);

//split_cmds
void	ft_spc(int size);
char	**ft_cmd(void);
int		ft_matriz_size(void);
int		ft_ptrlen(int v);
char	*check_path(char *cmd);

// cmds
void	free_cmds(char ***cmds);
void	free_fds(int **fds);
void	exec_type_end(void);
void	exec_type_md(void);
void    exec_type(void);
void	check_spc(void);
void	cmd_to_exec(void);

// free
void    free_cmds(char ***cmds);
void    free_double_ptr(char **str);
void    free_fds(int **fds);

// ft_exec
void	ft_exec(void);
void	ft_exec_pipe_md(void);
void	ft_exec_pipe_end(void);

// ft_redirect
void	ft_red(void);
void	ft_red_end(void);

// ft_input
void	ft_input(void);
void	ft_input_end(void);

// cmds_utils
int		is_spc(char *cmd);
int		ft_strcpm(char *s1, char *s2);
void	generate_fds(void);
char	***get_cmds(void);
char	*ft_strdup(const char *src);

// cmds_utils2
char	*ft_getenv(char **env, char *str, int size);
void	free_all(void);
void	free_exec(void);
int		is_redirect(char *cmd);
int		is_exec(char *cmd);
int 	is_exec(char *cmd);
void	alloc_env(char **env);

// check_builtins
int		is_builtins(char *cmd);
void	call_builtins(char **cmd);
void	call_builtins_exec(char **cmd);

//  ft_cd
void	add_cd_to_env(char *path);
void	apply_cd(char *oldcd, char *newcd);
void	cd_to(char *str);
int		ft_check_cd(char **str);
void	ft_cd(char **str);

// ft_echo
void	ft_echo_beg(char *str, int flag);
void	ft_echo(char **str);
void	ft_echo_exec(char **str);

// ft_env
void	ft_env(char **str);
void	ft_env_exec(char **str);

// ft_exit
void	ft_exit(char **str);

// ft_export
void	check_env_name(char **env, char *str, int size);
int		check_export(char **str);
void    ft_export(void);

// ft_pwd
void	ft_pwd(char **str);
void	ft_pwd_exec(char **str);

// ft_unset
void	ft_unset(char **str);
void	unset_var(char **env, int skip);
void    ft_unset(char **str);

#endif
