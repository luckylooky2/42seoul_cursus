/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 20:34:07 by chanhyle          #+#    #+#             */
/*   Updated: 2021/12/15 11:59:37 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_multi_list	*make_new_node(t_multi_list **linked_lst, void *content, int case, int fd)
{
	t_multi_list	*new_node;
	t_multi_list	*curr;

	new_node = (t_multi_list *)malloc(sizeof(t_multi_list));
	if (new_node == NULL)
	{
		ft_lstclear(linked_lst, free);
		return (NULL);
	}
	if (case == 0)
	{
		new_node->content = content;
		new_node->next = NULL;
	}
	else if (case == 1)
	{
		new_node->buf = (char *)ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
		if (new_node->buf == NULL)
		{
			ft_lstclear(linked_lst, free);
			return (NULL);
		}
		new_node->fd_num = fd;
	}
	curr = *linked_lst;
	if (curr == NULL)
	{
		new_node->next = *linked_lst;
		*linked_lst = new_node;
	}
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new_node;
	}
	return (*linked_lst);
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

int	ft_lstsize(t_multi_list *lst)
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

void	ft_lstclear(t_multi_list **lst, void (*del)(void *))
{
	t_multi_list	*back;

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
