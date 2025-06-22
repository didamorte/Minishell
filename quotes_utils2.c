/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rneto-fo <rneto-fo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 22:01:59 by rneto-fo          #+#    #+#             */
/*   Updated: 2025/06/22 14:31:00 by rneto-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_flex(char *s1, char *s2, int flag)
{
	char	*str;
	int		len1;
	int		len2;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = malloc(len1 + len2 + 1);
	if (!str)
		return (NULL);
	i = -1;
	while (++i < len1)
		str[i] = s1[i];
	j = -1;
	while (++j < len2)
		str[i + j] = s2[j];
	str[i + j] = '\0';
	if (flag == 1 || flag == 3)
		free(s1);
	if (flag == 2 || flag == 3)
		free(s2);
	return (str);
}

char	*double_quotes(const char *str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1])
			res[j++] = str[++i];
		else if (str[i] != '"')
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

char	*single_quotes(const char *str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1])
			res[j++] = str[++i];
		else if (str[i] != '\'')
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

char	*handle_variable_expansion(char *result, t_expand_ctx *ctx)
{
	char	*exit_code;

	if (ctx->arg[*(ctx->i) + 1] == '?')
	{
		exit_code = ft_itoa(ctx->last_exit_status);
		result = ft_strjoin_flex(result, exit_code, 1);
		free(exit_code);
		*(ctx->i) += 2;
	}
	else if (ft_isalnum(ctx->arg[*(ctx->i) + 1])
		|| ctx->arg[*(ctx->i) + 1] == '_')
	{
		(*(ctx->i))++;
		result = expand_variable(result, ctx);
	}
	else
	{
		result = append_char(result, ctx->arg[(*(ctx->i))++]);
	}
	return (result);
}
