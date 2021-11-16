/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:27:02 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/16 17:27:04 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft_bonus.h"

t_list  *ft_lstlast(t_list *lst)
{
    t_list  *ptr;

    ptr = lst;
    while (ptr->next)
        ptr = ptr->next;
    return (ptr);
}
