/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rneto-fo <rneto-fo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:04:22 by rneto-fo          #+#    #+#             */
/*   Updated: 2025/06/22 13:44:37 by rneto-fo         ###   ########.fr       */
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

char	*append_char(char *result, char c)
{
	char	*new_str;

	new_str = ft_strjoin_flex(result, (char [2]){c, 0}, 1);
	if (!new_str)
		exit(EXIT_FAILURE);
	return (new_str);
}

char	*expand_variable(char *result, t_expand_ctx *ctx)
{
	int		start;
	char	*var;
	char	*value;

	start = *(ctx->i);
	while (ctx->arg[*(ctx->i)] && (ft_isalnum(ctx->arg[*(ctx->i)])
			|| ctx->arg[*(ctx->i)] == '_'))
		(*(ctx->i))++;
	var = ft_substr(ctx->arg, start, *(ctx->i) - start);
	value = get_env_value(var, ctx->envp);
	if (value)
		result = ft_strjoin_flex(result, value, 1);
	else
		result = ft_strjoin_flex(result, "", 1);
	free(var);
	return (result);
}

char	*expand_variables(const char *arg, int last_exit_status, char **envp)
{
	char			*result;
	int				i;
	t_expand_ctx	ctx;

	result = ft_calloc(1, 1);
	i = 0;
	ctx.arg = arg;
	ctx.i = &i;
	ctx.last_exit_status = last_exit_status;
	ctx.envp = envp;
	while (arg[i])
	{
		if (arg[i] == '\\' && arg[i + 1])
		{
			result = append_char(result, arg[i + 1]);
			i += 2;
		}
		else if (arg[i] == '$')
		{
			result = handle_variable_expansion(result, &ctx);
		}
		else
			result = append_char(result, arg[i++]);
	}
	return (result);
}
