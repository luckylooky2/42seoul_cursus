/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:25:39 by chanhyle          #+#    #+#             */
/*   Updated: 2021/12/13 19:25:41 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

char	*copy_linked_list(t_list *char_lst, char *ret_str)
{
	int		i;

	i = 0;
	while (char_lst)
	{
		ret_str[i++] = *((char *)((char_lst)->content));
		char_lst = (char_lst)->next;
	}
	return (ret_str);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*new_str;
	size_t	i;

	i = 0;
	new_str = malloc(nmemb * size);
	if (!new_str)
		return (NULL);
	else
	{
		while (i < nmemb * size)
			((unsigned char *)new_str)[i++] = 0;
		return (new_str);
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
