/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dateixei <dateixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 21:45:57 by dateixei          #+#    #+#             */
/*   Updated: 2023/07/13 23:06:27 by dateixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to know the numbers of some char in a string
int	nbr_char(char *str, char c)
{
	int	i;

	i = 0;
	while (*str)
	{
		while (*str && *str != c)
			str++;
		str++;
		i++;
	}
	return (i);
}

// Function to count the tokens
int	count_tokens(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		str += skip_whitespace(str);
		if (*str == '\'' || *str == '\"')
		{
			if (str[1] != *str)
			{
				str = handle_quote(str, *str);
				i++;
				if (*str == '\0')
					return (i);
			}
			else
				str += 2;
		}
		else
			handle_special_characters(&str, &i);
	}
	return (i);
}

void	handle_special_characters(char **str, int *count)
{
	if ((**str == '|' || **str == '<' || **str == '>'))
	{
		if ((**str == '<' || **str == '>') && (*str)[1] == **str)
			(*str) += 2;
		else
			(*str)++;
		(*count)++;
	}
	else
	{
		while (**str && **str != ' ' && **str != '\n'
			&& **str != '\t' && **str != '|' && **str != '<' && **str != '>')
			(*str)++;
		(*count)++;
	}
}

int	handle_dollar_sign(char *str)
{
	int	i;

	i = 0;
	str++;
	handle_env(str);
	while (str[i] && str[i] != ' ' && str[i] != '\n' && str[i] != '\t'
		&& str[i] != '|' && str[i] != '<' && str[i] != '>' && str[i] != '$')
		i++;
	if (!data()->str_tmp)
		data()->warning = -1;
	return (i);
}

char	**alloc_tokens(char *str, int nbr_tokens)
{
	int		i;
	int		size;
	char	**tokens;

	i = 0;
	tokens = (char **)malloc((nbr_tokens + 1) * sizeof(char *));
	if (!tokens)
	{
		perror("Error while malloc tokens.");
		return (NULL);
	}
	while (*str)
	{
		data()->warning = 0;
		if (*str == ' ' || *str == '\n' || *str == '\t')
			str++;
		else if (*str == '\'' || *str == '\"')
		{
			if (str[1] != *str)
			{
				size = nbr_inside_quotes(str, *str);
				if (data()->warning == -1)
					tokens[i++] = env_var(str++);
				else
					tokens[i++] = ft_substr(++str, 0, size);
				str += (size + 1);
			}
			else
				str += 2;
		}
		else if ((*str == '|' || *str == '>' || *str == '<'))
		{
			if (str[1] == *str && (*str == '>' || *str == '<'))
			{
				tokens[i++] = ft_substr(str, 0, 2);
				str += 2;
			}
			else
				tokens[i++] = ft_substr(str++, 0, 1);
		}
		else if (*str == '$')
		{
			size = handle_dollar_sign(str);
			if (data()->warning != -1)
			{
				if (data()->str_tmp != NULL)
					tokens[i++] = ft_substr(data()->str_tmp, 0, ft_strlen(data()->str_tmp));
			}
			else if (nbr_tokens > 0)
				continue ;
			else
				tokens[i++] = ft_substr(" ", 0, 1);
			str += (size + 1);
		}
		else
		{
			size = nbr_outside_quotes(str);
			// if ((str[size + 1] == '\'' || str[size + 1] == '\"') && (str[size + 2] == '\'' || str[size + 2] == '\"'))
			// 	tokens[i] = ft_substr(str, 0, (size + 1));
			// else
				tokens[i++] = ft_substr(str, 0, (size + 1));
			str += (size + 1);
		}
		nbr_tokens--;
	}
	tokens[i] = NULL;
	return (tokens);
}

void	check_echo(void)
{
	int	i;

	i = 0;
	while (data()->tokens[i] != NULL)
	{
		if (ft_strncmp(data()->tokens[i], "echo", 5) == 0)
		{
			if (ft_strncmp(data()->tokens[i + 1], "-n", 3) == 0)
				i += 2;
			else
				i++;
			while (data()->tokens[i] && ft_strncmp(data()->tokens[i], "|", 2) != 0 && ft_strncmp(data()->tokens[i], ">", 2) != 0
				&& ft_strncmp(data()->tokens[i], "<", 2) != 0 && ft_strncmp(data()->tokens[i], "|", 2) != 0
				&& ft_strncmp(data()->tokens[i], "\'", 2) != 0
				&& ft_strncmp(data()->tokens[i], "\"", 2) != 0 && ft_strncmp(data()->tokens[i], ">>", 3)
				&& ft_strncmp(data()->tokens[i], "<<", 3))
			{
				if (data()->tokens[i + 1] == NULL)
				{
					i++;
					break ;
				}
				else
					data()->tokens[i] = strjoin_var(data()->tokens[i], ' ');
				i++;
			}
		}
		else
			i++;
	}
}

// Function to generate tokens from the str_cmd.
int	get_tokens(void)
{
	int	i;

	i = 0;
	while (data()->str_cmd[i] && (data()->str_cmd[i] == ' ' || data()->str_cmd[i] == '\n' || data()->str_cmd[i] == '\t'))
		i++;
	if (data()->str_cmd[i] == '\0')
		return (0);
	if (check_quotes(data()->str_cmd) == 0)
	{
		perror("Error unclosed quotes");
		return (0);
	}
	data()->nbr_tokens = count_tokens(data()->str_cmd);
	data()->tokens = alloc_tokens(data()->str_cmd, data()->nbr_tokens);
	if (*data()->tokens == NULL)
		return (0);
	check_echo();
	ft_unset(data()->env_p, "?");
	return (1);
}
