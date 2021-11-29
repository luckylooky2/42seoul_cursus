/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 20:36:07 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/29 17:04:35 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_lst;
	char	*new_str;

	new_lst = (t_list *)malloc(sizeof(t_list));
	if (new_lst == NULL)
		return (NULL);
	new_str = (char *)malloc(sizeof(char));
	if (new_str == NULL)
		return (NULL);
	*new_str = *((char *)(content));
	new_lst->content = (void *)new_str;
	new_lst->next = NULL;
	return (new_lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*curr;
	int		i;

	i = 0;
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

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if ((*del) == NULL || lst == NULL)
		return ;
	(*del)(lst->content);
	free(lst);
}
