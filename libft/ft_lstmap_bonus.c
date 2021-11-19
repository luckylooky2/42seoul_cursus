/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:42:52 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/17 16:42:55 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft_bonus.h"

#include <stdio.h>

static int	ft_lst_count(t_list *ptr)
{
	int	cnt;

	cnt = 0;
	while (ptr)
	{
		cnt++;
		ptr = ptr->next;
	}
	return (cnt);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ptr;
	int		cnt;
	int		i;

	i = 0;
	cnt = ft_lst_count(lst);
	ptr = (t_list *)malloc(sizeof(t_list) * cnt);
	if (ptr == 0)
		return (0);
	while (lst)
	{
		if ((*f) != 0)
			(ptr + i)->content = (*f)(lst->content);
		if ((*del) != 0)
			(*del)((ptr + i)->content);
		if (i != cnt - 1)
			(ptr + i)->next = (ptr + (i + 1));
		else
			(ptr + i)->next = 0;
		i++;
		lst = lst->next;
	}
	return (ptr);
}


void	*lstmap_f(void *content)
{
	(void)content;
	return ("OK !");
}

#include <stdio.h>
#include <string.h>
int main()
{
	t_list	*l = ft_lstnew(strdup(" 1 2 3 "));
	t_list	*ret;

	// l->next = ft_lstnew(strdup("ss"));
	// l->next->next = ft_lstnew(strdup("-_-"));
	ret = ft_lstmap(0, lstmap_f, 0);

	// if (!strcmp(ret->content, "OK !") && !strcmp(ret->next->content, "OK !") && !strcmp(ret->next->next->content, "OK !") && !strcmp(l->content, " 1 2 3 ") && !strcmp(l->next->content, "ss") && !strcmp(l->next->next->content, "-_-"))
	// 	printf("good");
	// else
	// 	printf("bad");
}
