/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 11:27:12 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/17 11:27:19 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft_bonus.h"

int	ft_lstsize(t_list *lst)
{
	int		cnt;
	t_list	*ptr;

	cnt = 0;
	ptr = lst;
	while (ptr)
	{
		ptr = ptr->next;
		cnt++;
	}
	return (cnt);
}
