/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 20:53:15 by dateixei          #+#    #+#             */
/*   Updated: 2023/08/03 10:51:32 by dateixei         ###   ########.fr       */
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
# include "parse.h"
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
	int			fd[2][2];
	int			curr_cmd;
	int			curr_fd;
	int			count;
	int			warning;
	int			shlvl;
	char		**here_doc;
	char		*str_tmp;
	int			error;
}			t_data;

// ---------- PARSE ------------

//Data init
t_data			*data(void);

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
char			*strjoin_null(char *s1, char *s2);

// Utils 2
void			handle_env(char *str);
int				skip_whitespace(char *str);
void			skip_non_whitespace_and_dolar_sign(char **str);

// Utils 3
int				handle_dollar_sign(char *str);
void			check_echo(void);
int				token_is_space(char *str, int *i);

// Utils 4
char			**init_tokens(int nbr_tokens);
int				token_inside_quote(char	*str, char **tokens);
int				token_special_char(char *str, char **token, int *i);
int				token_space_dolar_sig(char *str, char **token, int nbr_tokens);
int				token_other_chars(char *str, char **token, int *i);

// Utils 5
char			*handle_single_spc_quote(char *str);

// ---------- EXECUTION ------------

// cmds
void			swap_fd(void);
void			generate_fds(void);
void			child_exec(void);
void			execute_cmd(void);
void			cmd_to_exec(void);

// fd_checker
void			fd_input(int tmp_curr);
void			fd_red_append(int tmp_curr);
void			fd_redirect(int tmp_curr);
void			fd_pipe(void);
int				fd_check(int tmp_curr);

// fd_heredoc
int				handle_here(char *exit);
void			fd_heredoc(int tmp_curr);

// free
void			free_double_ptr(char **str);
void			free_triple_ptr(char ***str);

// get_path
char			*ft_getenv(char **env, char *str, int size);
char			*get_path_loop(char *cmd, char **path);
char			*add_path(char *path, int i, char *cmds);
char			*get_path(char *cmd);
char			*check_path(char *cmd);

// utils
int				is_spc(char *cmd);
int				my_strcmp(char *s1, char *s2);

// generate_cmd
int				ft_cmdlen(void);
char			**spc_cmd(int i, int j, int size);
char			**get_cmd(int i, int j, int size);
char			***generate_cmd(void);

// generate_cmd2
int				ft_mtzlen(char ***mtz);
char			***my_realloc(char ***cmds);
void			free_token(int i);
int				is_valid_cmd();

// ---------- BUILTINS ------------

// check_builtins
int				is_builtins(char *cmd);
void			call_builtins(char **cmd);

// error_msg
void			error_msg(char *option, char *var_option, \
				char *msg, int err);
void			check_permission(void);
void			error_exec(void);
void			free_all(void);
void			exit_child(void);

//  ft_cd
void			add_cd_to_env(char *path);
void			apply_cd(char *oldcd, char *newcd);
void			cd_to(char *str);
int				ft_check_cd(char **str);
void			ft_cd(char **str);

// ft_echo
int				is_flag(char *str);
void			print_echo(char **str, int flag);
void			ft_echo_beg(char **str, int flag);
void			ft_echo(char **str);

// ft_env
void			ft_env(char **str);
void			ft_env_exec(char **str);

// ft_exit
int				ft_exit_err(void);
long long int	ft_atoli_checker(char *nptr, int i, int sing);
long long int	ft_atoli(char *nptr);
void			ft_exit(char **str);

// ft_export
void			export_declare_exec(char **str);
void			export_declare(void);
void			check_env_name(char **env, char *str, int size);
int				check_export(char **str, int i, int j);
void			ft_export(void);

// ft_pwd
void			ft_pwd(char **str);
void			ft_pwd_exec(char **str);

// ft_unset
void			ft_unset(char **str, char *find);
void			unset_var(char **env, int skip);

#endif
