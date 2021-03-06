/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 20:36:07 by chanhyle          #+#    #+#             */
/*   Updated: 2021/12/01 00:56:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "1_get_next_line.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_lst;

	new_lst = (t_list *)malloc(sizeof(t_list));
	if (new_lst == NULL)
		return (NULL);
	new_lst->content = content;
	new_lst->next = NULL;
	return (new_lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*curr;

	curr = *lst;
	if (curr == NULL)
	{
		new->next = *lst;
		*lst = new;
	}
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new;
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

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if ((*del) == NULL || lst == NULL)
		return ;
	(*del)(lst->content);
	free(lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*back;

	if ((*del) == NULL || *lst == NULL)
		return ;
	back = (*lst)->next;
	while (*lst)
	{
		ft_lstdelone(*lst, (*del));
		*lst = back;
		if (*lst != NULL)
			back = back->next;
	}
	*lst = NULL;
}
