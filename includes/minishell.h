/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 20:53:15 by dateixei          #+#    #+#             */
/*   Updated: 2023/07/15 17:44:10 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>//  write, dup2, close
# include <fcntl.h>//  O_RDONLY, O_...
# include <stdlib.h>//  EXIT_FAILURE, malloc, free
# include <stdio.h>//  STDIN
# include <sys/types.h>//	wait
# include <sys/wait.h>//	wait
# include <errno.h>//	ERROR
# include <signal.h>//	SIG
# include <dirent.h>//	DIR
# include <limits.h>// MAX / MIN VALUES
# include <readline/readline.h>//	ReadLine
# include <readline/history.h>//	History
# include "../libft/include/libft.h"
# define TRUE 1
# define FALSE 0
# define GREEN "\033[0;32m"
# define TEMP_FILE "./.temp"

typedef struct s_data
{
	int			nbr_tokens;
	char		**tokens;
	char		*str_cmd;
	char		**env_p;
	char		***cmds;
	int			**fd;
	int			*spc;
	int			curr_cmd;
	int			curr_fd;
	int			count;
	int			warning;
	int			shlvl;
	char		**here_doc;
	char		*str_tmp;
	int			error;
}			t_data;

//Data init
t_data			*data(void);

// Parse_utils
int				get_tokens(void);
int				nbr_char(char *str, char c);
char			**alloc_tokens(char *str, int nbr_tokens);
void			handle_special_characters(char **str, int *count);

// Parse_init
void			parse_init(void);
char			*my_getenv(char *str);

// Parse_quotes
int				check_quotes(char *str);
int				nbr_outside_quotes(char *str);
int				nbr_inside_quotes(char *str, char c);
char			*check_envp(char	*str);
char			*handle_quote(char	*str, char c);

// Utils
char			*env_var(char *str);
void			handle_error_var(void);
void			handle_shlvl(char c);
char			*strjoin_var(char *s1, char s2);
char			*strjoin_here(char *s1, char *s2);
char			*strjoin_null(char const *s1, char const *s2);

// Utils 2
void			handle_env(char *str);
int				skip_whitespace(char *str);
void			skip_non_whitespace_and_dolar_sign(char **str);

//split_cmds
void			ft_spc(int size);
char			**ft_cmd(void);
int				ft_matriz_size(void);
int				ft_ptrlen(int v);
char			*get_path(char *cmd);

//split_cmds2
char			*get_path_loop(char *cmd, char **path);
char			*add_path(char *path, int i, char *cmds);
char			*check_path(char *cmd);

// cmds
void			exec_type_end(void);
void			exec_type_md(void);
void			exec_type(void);
void			check_spc(void);
void			cmd_to_exec(void);

// free
void			free_cmds(char ***cmds);
void			free_double_ptr(char **str);
void			free_fds(int **fds);

// ft_exec
void			exec_begin(void);
void			exec_md(void);
void			ft_exec(void);
void			ft_exec_pipe_md(void);
void			ft_exec_pipe_end(void);

// ft_exec_utils
void			exec_end(void);
int				ft_input_check(int tmp_cmd);
int				ft_red_input_check(int tmp_cmd);
int				ft_red_loop_checker(int tmp_cmd);

// ft_redirect
void			ft_red(void);
void			ft_red_end(void);

// ft_input
void			ft_input(void);
int				handle_here(char *exit);
void			ft_red_input(int tmp_cmd);

// cmds_utils
int				is_spc(char *cmd);
int				ft_strcpm(char *s1, char *s2);
void			generate_fds(void);
char			***get_cmds(void);
char			*ft_strdup(const char *src);

// cmds_utils2
char			*ft_getenv(char **env, char *str, int size);
void			free_all(void);
void			free_exec(void);
int				is_redirect(char *cmd);
int				is_exec(char *cmd);
int				is_exec(char *cmd);

// cmd_utils3
char			**get_exec_cmd(int i);
char			**get_red_cmd(int i);
char			**check_input(void);
char			**check_cmd_exec(void);
char			**check_red_cmd(void);

// cmd_utils4
int				is_valid_loop(void);
int				is_valid(void);
void			cmd_exec(int pid, int status);
void			alloc_env(char **env);
int				ft_cmd_loop(void);

// check_builtins
int				is_builtins(char *cmd);
void			call_builtins(char **cmd);
void			call_builtins_exec(char **cmd);

// error_msg
void			builtins_error(char *option, char *var_option, \
				char *msg, int err);

//  ft_cd
void			add_cd_to_env(char *path);
void			apply_cd(char *oldcd, char *newcd);
void			cd_to(char *str);
int				ft_check_cd(char **str);
void			ft_cd(char **str);

// ft_echo
int				is_spc_char(char *str);
void			print_echo(char **str, int flag);
void			ft_echo_beg(char **str, int flag);
void			ft_echo(char **str);
void			ft_echo_exec(char **str);

// ft_env
void			ft_env(char **str);
void			ft_env_exec(char **str);

// ft_exit
long long int	ft_atoli_checker(const char *nptr, int i, int sing);
long long int	ft_atoli(const char *nptr);
void			ft_exit(char **str);
void			ft_exit_exec(char **str);

// ft_export
void			check_env_name(char **env, char *str, int size);
int				check_export(char **str);
void			ft_export(void);

// ft_pwd
void			ft_pwd(char **str);
void			ft_pwd_exec(char **str);

// ft_unset
void			ft_unset(char **str, char *find);
void			unset_var(char **env, int skip);

#endif
