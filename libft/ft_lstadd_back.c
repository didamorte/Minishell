/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 20:00:55 by diogribe          #+#    #+#             */
/*   Updated: 2025/03/31 14:12:15 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!(lst || new))
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}
/* 
int main()
{
	t_list	*list = NULL;
	t_list	*node;

	node = ft_lstnew((void *)"12345");
	ft_lstadd_back(&list, node);

	node = ft_lstnew((void *)"1234");
	ft_lstadd_back(&list, node);

	node = ft_lstnew((void *)"123");
	ft_lstadd_back(&list, node);

	t_list	*pos = list;
	while (pos)
	{
		printf("%s\n", (char *)pos->content);
		pos = pos->next;
	}
} */