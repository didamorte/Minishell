/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:04:22 by rneto-fo          #+#    #+#             */
/*   Updated: 2025/05/21 15:32:34 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && str[i + 1])
			return (single_quotes(str));
		else if (str[i] == '"' && str[i + 1])
			return (double_quotes(str));
		i++;
	}
	return (ft_strdup(str));
}

bool	check_unclosed_quotes(const char *str)
{
	char	quote_type;
	bool	in_quote;

	quote_type = 0;
	in_quote = false;
	while (*str)
	{
		if (*str == '\\' && *(str + 1))
		{
			str += 2;
			continue ;
		}
		if (!in_quote && (*str == '\'' || *str == '"'))
		{
			quote_type = *str;
			in_quote = true;
		}
		else if (in_quote && *str == quote_type)
			in_quote = false;
		str++;
	}
	return (in_quote);
}

static char	*append_char(char *result, char c)
{
	char	*new_str;

	new_str = ft_strjoin_flex(result, (char [2]){c, 0}, 1);
	if (!new_str)
		exit(EXIT_FAILURE);
	return (new_str);
}

static char	*expand_variable(char *result, const char *arg, int *i)
{
	int		start;
	char	*var;
	char	*value;

	(*i)++;
	start = *i;
	while (arg[*i] && (ft_isalnum(arg[*i]) || arg[*i] == '_'))
		(*i)++;
	var = ft_substr(arg, start, *i - start);
	value = getenv(var);
	if (value)
		result = ft_strjoin_flex(result, value, 1);
	free(var);
	return (result);
}

char	*expand_variables(const char *arg, int last_exit_status)
{
	char	*exit_code;
	char	*result;
	int		i;

	result = ft_calloc(1, 1);
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\\' && arg[i + 1])
		{
			result = append_char(result, arg[i + 1]);
			i += 2;
		}
		else if (arg[i] == '$' && arg[i + 1])
		{
			if (arg[i + 1] == '?')
			{
				exit_code = ft_itoa(last_exit_status);
				result = ft_strjoin_flex(result, exit_code, 1);
				free(exit_code);
				i += 2;
			}
			else if (ft_isalnum(arg[i + 1]) || arg[i + 1] == '_')
				result = expand_variable(result, arg, &i);
			else
				result = append_char(result, arg[i++]);
		}
		else
			result = append_char(result, arg[i++]);
	}
	return (result);
}
