/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gateixei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:07:53 by gateixei          #+#    #+#             */
/*   Updated: 2023/06/09 15:48:59 by gateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    is_builtins(char *cmd)
{
    if (ft_strcpm(cmd, "echo"))
        return (1);
    else if (ft_strcpm(cmd, "cd"))
        return (1);
    else if (ft_strcpm(cmd, "pwd"))
        return (1);
    else if (ft_strcpm(cmd, "export"))
        return (1);
    else if (ft_strcpm(cmd, "unset"))
        return (1);
    else if (ft_strcpm(cmd, "env"))
        return (1);
    else if (ft_strcpm(cmd, "exit"))
        return (1);
    return (0);
}

void    call_builtins(char **cmd)
{
    if (ft_strcpm(cmd[0], "echo"))
        ft_echo(cmd);
    else if (ft_strcpm(cmd[0], "cd"))
        ft_cd(cmd);
    else if (ft_strcpm(cmd[0], "pwd"))
        ft_pwd(cmd);
    else if (ft_strcpm(cmd[0], "export"))
        ft_export(cmd);
    else if (ft_strcpm(cmd[0], "unset"))
        ft_unset(cmd);
    else if (ft_strcpm(cmd[0], "env"))
        ft_env(cmd);
    else if (ft_strcpm(cmd[0], "exit"))
        ft_exit(cmd);
}