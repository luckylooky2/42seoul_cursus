/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 13:44:43 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/08 15:52:22 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

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

int	ft_lstsize(t_list *lst)
{
	int	cnt;

	cnt = 0;
	while (lst)
	{
		lst = lst->next;
		cnt++;
	}
	return (cnt);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*back;

	if ((*del) == NULL || *lst == NULL)
		return ;
	back = (*lst)->next;
	while (*lst)
	{
		(*del)((*lst)->content);
		free(*lst);
		*lst = back;
		if (*lst != NULL)
			back = back->next;
	}
	*lst = NULL;
}
