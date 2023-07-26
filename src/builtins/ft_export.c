/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:41:20 by gateixei          #+#    #+#             */
/*   Updated: 2023/07/17 11:51:26 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_declare_exec(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str && str[i] != NULL)
	{
		j = 0;
		write(1, "declare -x ", 11);
		while (str[i][j] != '=')
			write(1, &str[i][j++], 1);
		write(1, &str[i][j++], 1);
		write(1, "\"", 1);
		while (str[i][j] != '\0')
			write(1, &str[i][j++], 1);
		write(1, "\"\n", 2);
		i++;
	}
	data()->error = 0;
}

void	export_declare(void)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		close(data()->fd[data()->curr_fd][0]);
		dup2(data()->fd[data()->curr_fd][1], STDOUT_FILENO);
		export_declare_exec(data()->env_p);
		exit(0);
	}
	else
	{
		close(data()->fd[data()->curr_fd][1]);
		waitpid(pid, NULL, 0);
	}
}

void	check_env_name(char **env, char *str, int size)
{
	int	i;

	i = 0;
	while (env && env[i] != NULL)
	{
		if (!ft_strncmp(env[i], str, size) && env[i][size] == '=')
		{
			unset_var(env, i);
			return ;
		}
		i++;
	}
}

int	check_export(char **str, int i, int j)
{
	while (str && str[j] != NULL)
	{
		i = 0;
		while (str[j] && str[j][i] != '\0')
		{
			if ((i == 0 && (str[j][i] == '=' \
			|| ft_isdigit(str[j][i]))) || str[j][i] == '-')
			{
				builtins_error("export: `", str[j], \
				"': not a valid identifier", 1);
				return (0);
			}
			else if (str[j][i] == '=')
			{
				check_env_name(data()->env_p, str[j], i);
				return (j);
			}
			i++;
		}
		j++;
	}
	return (0);
}

void	ft_export(void)
{
	int		j;
	int		new;
	char	**new_str;

	new = check_export(data()->cmds[data()->curr_cmd], 0, 0);
	if (new < 1 || (data()->spc && data()->spc[data()->curr_cmd] != -1))
		return ;
	j = 0;
	while (data()->env_p && data()->env_p[j] != NULL)
		j++;
	new_str = malloc(sizeof(char *) * (j + 2));
	j = 0;
	while (data()->env_p && data()->env_p[j] != NULL)
	{
		new_str[j] = ft_strdup(data()->env_p[j]);
		j++;
	}
	new_str[j++] = ft_strdup(data()->cmds[data()->curr_cmd][new]);
	new_str[j] = NULL;
	free_double_ptr(data()->env_p);
	data()->env_p = new_str;
	data()->error = 0;
}
