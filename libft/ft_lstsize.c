/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 01:00:39 by diogribe          #+#    #+#             */
/*   Updated: 2025/03/31 14:11:53 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

/* int main()
{
	t_list	*list = NULL;
	t_list	*node;

	node = ft_lstnew((void *)"12345");
	ft_lstadd_front(&list, node);

	node = ft_lstnew((void *)"1234");
	ft_lstadd_front(&list, node);

	node = ft_lstnew((void *)"123");
	ft_lstadd_front(&list, node);

	printf("%d", ft_lstsize(list));
} */