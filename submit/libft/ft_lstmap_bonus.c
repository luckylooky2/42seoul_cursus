/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:42:52 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/17 16:42:55 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft_bonus.h"

static int	ft_lst_count(t_list *ptr)
{
	int	cnt;

	cnt = 0;
	while (ptr)
	{
		cnt++;
		ptr = ptr->next;
	}
	return (cnt);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ptr;
	int		cnt;
	int		i;

	i = 0;
	cnt = ft_lst_count(lst);
	ptr = (t_list *)malloc(sizeof(t_list) * cnt);
	if (ptr == 0)
		return (0);
	while (lst)
	{
		if ((*f) != 0)
			(ptr + i)->content = (*f)(lst->content);
		if ((*del) != 0)
			(*del)((ptr + i)->content);
		if (i != cnt - 1)
			(ptr + i)->next = (ptr + (i + 1));
		else
			(ptr + i)->next = 0;
		i++;
		lst = lst->next;
	}
	return (ptr);
}
