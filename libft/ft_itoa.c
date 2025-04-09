/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:26:42 by diogribe          #+#    #+#             */
/*   Updated: 2025/03/31 14:12:18 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numcount(int nb)
{
	int	c;

	c = 0;
	if (nb <= 0)
		c++;
	while (nb)
	{
		nb /= 10;
		c++;
	}
	return (c);
}

static void	ft_revnbr(int n, int len, int i, char *str)
{
	while (i < len)
	{
		str[len - 1] = n % 10 + '0';
		n /= 10;
		len--;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		i;

	len = ft_numcount(n);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	if (n == -2147483648)
	{
		str[i++] = '-';
		str[i++] = '2';
		n = 147483648;
	}
	if (n < 0)
	{
		str[i++] = '-';
		n *= -1;
	}
	ft_revnbr(n, len, i, str);
	str[len] = '\0';
	return (str);
}

/* int main()
{
	char	*str = ft_itoa(12345678);
	printf("%s", str);
} */