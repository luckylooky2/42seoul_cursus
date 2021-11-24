/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:07:51 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/24 10:08:01 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;
	t_list	*back;

	if ((*del) == 0 || *lst == 0)
		return ;
	ptr = *lst;
	back = ptr->next;
	while (ptr)
	{
		ft_lstdelone(ptr, (*del));
		ptr = back;
		if (ptr != 0)
			back = back->next;
	}
	*lst = 0;
}
