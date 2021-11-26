/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:09:22 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/24 10:09:33 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*curr;
	t_list	*front;

	if ((*f) == NULL || lst == NULL)
		return (NULL);
	first = ft_lstnew(lst->content);
	if (first == NULL)
		return (NULL);
	front = first;
	lst = lst->next;
	while (lst)
	{
		curr = ft_lstnew(lst->content);
		if (curr == NULL)
		{
			ft_lstclear(&first, (*del));
			return (NULL);
		}
		front->next = curr;
		front = curr;
		lst = lst->next;
	}
	return (first);
}
