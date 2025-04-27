/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rneto-fo <rneto-fo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:04:22 by rneto-fo          #+#    #+#             */
/*   Updated: 2025/04/27 22:02:47 by rneto-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_outer_quotes(const char *str)
{
	size_t	len;
	char	*result;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len >= 2 && ((str[0] == '\'' && str[len - 1] == '\'')
			|| (str[0] == '"' && str[len - 1] == '"')))
		result = ft_substr(str, 1, len - 2);
	else
		result = ft_strdup(str);
	return (result);
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
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	return (ft_strjoin_flex(result, tmp, 1));
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

char	*expand_variables(const char *arg)
{
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
		else if (arg[i] == '$' && arg[i + 1]
			&& (ft_isalnum(arg[i + 1]) || arg[i + 1] == '_'))
			result = expand_variable(result, arg, &i);
		else
		{
			result = append_char(result, arg[i]);
			i++;
		}
	}
	return (result);
}
