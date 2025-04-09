/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 22:18:47 by diogribe          #+#    #+#             */
/*   Updated: 2025/03/31 14:12:02 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

/* void print_content(void *content)
{
	printf("%s\n", (char *)content);
}

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

	ft_lstiter(list, print_content);
} */