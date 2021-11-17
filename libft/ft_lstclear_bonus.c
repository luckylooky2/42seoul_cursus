/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 12:01:15 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/17 12:01:17 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft_bonus.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;
	t_list	*back;

	ptr = *lst;
	back = ptr->next;
	while (ptr)
	{
		(*del)(ptr->content);
		free(ptr);
		ptr = back;
		if (ptr != 0)
			back = back->next;
	}
	*lst = 0;
}
