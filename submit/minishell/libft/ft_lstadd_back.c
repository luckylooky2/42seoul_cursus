/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:21:18 by hangokim          #+#    #+#             */
/*   Updated: 2022/03/13 13:21:33 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (lst)
		current = *lst;
	else
		return ;
	while (current)
	{
		if (current->next)
			current = current->next;
		else
		{
			current->next = new;
			return ;
		}
	}
	*lst = new;
}
