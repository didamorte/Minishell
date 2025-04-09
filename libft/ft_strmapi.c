/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:01:39 by diogribe          #+#    #+#             */
/*   Updated: 2025/03/31 14:10:14 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*tmp;

	len = ft_strlen(s);
	tmp = (char *)malloc((len + 1) * sizeof(char));
	i = 0;
	if (!tmp)
		return (NULL);
	while (i < len)
	{
		tmp[i] = (*f)(i, s[i]);
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

/* char to_lowercase(unsigned int i, char c) {
	return (ft_tolower(c) + (i % 2));
}

int main()
{
	char	str[] = "OlA MuNdO";
	printf("%s", ft_strmapi(str, to_lowercase));
} */