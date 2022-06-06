/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 13:44:43 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/06 19:54:34 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	make_new_node(t_list **char_lst, void *content)
{
	t_list	*new_node;
	t_list	*curr;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (new_node == NULL)
	{
		ft_lstclear(char_lst, free);
		return ;
	}
	new_node->content = content;
	new_node->next = NULL;
	curr = *char_lst;
	if (curr == NULL)
	{
		new_node->next = *char_lst;
		*char_lst = new_node;
	}
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new_node;
	}
}
