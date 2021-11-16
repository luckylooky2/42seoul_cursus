/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:07:41 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/16 17:08:07 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft_bonus.h"

void    ft_lstadd_back(t_list **lst, t_list *new)
{
    t_list  *ptr;

    ptr = *lst;
    if (ptr == 0)
        ft_lstadd_front(lst, new);
    else
    {
        while (ptr->next)
            ptr = ptr->next;
        ptr->next = new;
    }
}
