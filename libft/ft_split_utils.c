/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rneto-fo <rneto-fo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 21:38:57 by rneto-fo          #+#    #+#             */
/*   Updated: 2025/04/27 21:55:17 by rneto-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

char	*unescape_string(const char *str)
{
	int		i;
	int		j;
	char	*cleaned;

	i = 0;
	j = 0;
	cleaned = malloc(ft_strlen(str) + 1);
	if (!cleaned)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1])
			i++;
		cleaned[j++] = str[i++];
	}
	cleaned[j] = '\0';
	return (cleaned);
}

void	update_quote(char *quote, char c)
{
	if (is_quote(c))
	{
		if (!*quote)
			*quote = c;
		else if (*quote == c)
			*quote = 0;
	}
}
