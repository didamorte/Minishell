/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:55:07 by diogribe          #+#    #+#             */
/*   Updated: 2025/03/31 14:12:00 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
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

	printf("first: %s\n", (char *)node->content);
	node = ft_lstlast(list);
	printf("last: %s\n", (char *)node->content);
} */