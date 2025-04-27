/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rneto-fo <rneto-fo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:00:43 by diogribe          #+#    #+#             */
/*   Updated: 2025/04/27 21:54:18 by rneto-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_count(const char *s, char sep)
{
	int		count;
	bool	in_word;
	char	quote;

	count = 0;
	in_word = false;
	quote = 0;
	while (*s)
	{
		if (*s == sep && !quote)
			in_word = false;
		else
		{
			if (!in_word)
			{
				count++;
				in_word = true;
			}
			update_quote(&quote, *s);
		}
		s++;
	}
	return (count);
}

static void	*ft_free(char **words, int i)
{
	while (--i >= 0)
		free(words[i]);
	free(words);
	return (NULL);
}

static int	get_word(const char *s, char sep, int *start)
{
	int		i;
	char	quote;

	i = *start;
	quote = 0;
	while (s[i] == sep && s[i] && !quote)
		i++;
	*start = i;
	while ((s[i] != sep || quote) && s[i])
	{
		if (s[i] == '\\' && s[i + 1])
		{
			i += 2;
			continue ;
		}
		if (is_quote(s[i]))
		{
			if (!quote)
				quote = s[i];
			else if (s[i] == quote)
				quote = 0;
		}
		i++;
	}
	return (i);
}

static char	**ft_fill_words(char **words, const char *s, char sep)
{
	int		i;
	int		j;
	int		start;
	char	*raw;

	i = 0;
	j = 0;
	while (s[i])
	{
		start = i;
		i = get_word(s, sep, &start);
		if (start < i)
		{
			raw = ft_substr(s, start, i - start);
			if (!raw)
				return (ft_free(words, j));
			words[j] = unescape_string(raw);
			free(raw);
			if (!words[j])
				return (ft_free(words, j));
			j++;
		}
	}
	words[j] = NULL;
	return (words);
}

char	**ft_split(const char *s, char sep)
{
	char	**words;

	if (!s)
		return (NULL);
	words = (char **)malloc((ft_word_count(s, sep) + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	return (ft_fill_words(words, s, sep));
}
