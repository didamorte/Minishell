/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:00:43 by diogribe          #+#    #+#             */
/*   Updated: 2025/03/31 14:10:39 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_count(char const *s, char c)
{
	int	i;

	i = 1;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
			i++;
		while (*s && *s != c)
			s++;
	}
	return (i);
}

static void	*ft_free(char **words, int i)
{
	while (--i)
		if (words[i])
			free(words[i]);
	free(words);
	return (NULL);
}

static char	**ft_fill_words(char **words, char const *s, char c)
{
	int	i;
	int	j;

	j = 0;
	while (*s)
	{
		if (*s != c && *s)
		{
			if (!ft_strchr(s, c))
				i = ft_strlen(s);
			else
				i = ft_strchr(s, c) - s;
			words[j++] = ft_substr(s, 0, i);
			if (!words[j - 1])
				return (ft_free(words, j - 1));
			s += i;
		}
		while (*s == c && *s)
			s++;
	}
	words[j] = NULL;
	return (words);
}

char	**ft_split(char const *s, char c)
{
	char	**words;

	if (!s)
		return (NULL);
	words = (char **)malloc(ft_word_count(s, c) * sizeof(char *));
	if (!words)
		return (NULL);
	return (ft_fill_words(words, s, c));
}
/* 
int main()
{
	char	*str = "hello!";
	char	**strs = ft_split(str, ' ');
	int i = 0;
	if (strs)
	{
		while (strs && strs[i] != NULL)
		{
			printf("%s\n", strs[i]);
			free(strs[i]);
			i++;
		}
	}
	free(strs);
} */
