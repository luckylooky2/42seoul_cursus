/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:54:20 by hangokim          #+#    #+#             */
/*   Updated: 2022/03/17 00:08:04 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;
	t_list	*previous;
	t_list	*current;

	start = 0;
	while (lst)
	{
		current = ft_lstnew(f(lst->content));
		if (current == 0)
		{
			ft_lstclear(&start, del);
			return (start);
		}
		else if (start == 0)
			start = current;
		else
			previous->next = current;
		previous = current;
		lst = lst->next;
	}
	return (start);
}
