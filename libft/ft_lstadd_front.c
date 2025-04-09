/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 20:30:48 by diogribe          #+#    #+#             */
/*   Updated: 2025/03/31 14:12:13 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!(lst || new))
		return ;
	new->next = *lst;
	*lst = new;
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

	t_list	*pos = list;
	while (pos)
	{
		printf("%s\n", (char *)pos->content);
		pos = pos->next;
	}
} */