/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:51:18 by diogribe          #+#    #+#             */
/*   Updated: 2025/03/26 18:38:21 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_reverse(char *str)
{
	int		first;
	int		last;
	char	temp;

	if (!str || str == NULL)
		return ;
	first = 0;
	last = pf_ft_strlen(str) - 1;
	while (first < last)
	{
		temp = str[first];
		str[first] = str[last];
		str[last] = temp;
		first++;
		last--;
	}
}

int	ft_memprint(unsigned long long num, char *base)
{
	int		count;
	int		i;
	int		temp;
	char	*mem;

	if (num == 0)
		return (pf_ft_putstr_fd("(nil)", 1));
	mem = (char *)malloc(16 + 1 * sizeof(char));
	count = 0;
	i = 0;
	count += pf_ft_putstr_fd("0x", 1);
	while (i <= 16 && num > 0)
	{
		temp = num % 16;
		num /= 16;
		mem[i] = base[temp];
		i++;
	}
	mem[i] = '\0';
	ft_reverse(mem);
	count += pf_ft_putstr_fd(mem, 1);
	free(mem);
	return (count);
}
