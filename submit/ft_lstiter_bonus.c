/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:10:12 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/17 15:10:18 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft_bonus.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		if ((*f) != 0)
			(*f)(lst->content);
		lst = lst->next;
	}
}
