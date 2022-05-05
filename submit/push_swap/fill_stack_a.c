/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_stack_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 21:48:24 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/03 21:53:49 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*free_if_failed(t_node **head, int cnt)
{
	int		i;
	t_node	*next;

	i = 0;
	next = (*head)->right;
	while (i < cnt)
	{
		free(*head);
		if (i == cnt - 1)
			return (NULL);
		*head = next;
		if (i != cnt - 2)
			next = next->right;
		i++;
	}
	return (NULL);
}

t_node	*create_new_node(int content)
{
	t_node	*new;

	new = (t_node *)ft_calloc(sizeof(t_node), 1);
	if (new == NULL)
		return (NULL);
	new->data = content;
	new->left = new;
	new->right = new;
	return (new);
}

t_node	*push_front(t_node *head, t_node *tail, t_node *new)
{
	if (head == NULL)
		head = new;
	else
	{
		head->left = new;
		new->right = head;
		new->left = tail;
		tail->right = new;
	}
	return (new);
}

void	make_new_index(t_node **head, int argc)
{
	int		cnt;
	t_node	*curr;
	t_node	**tmp_ary;

	cnt = 0;
	curr = *head;
	tmp_ary = (t_node **)ft_calloc(sizeof(t_node *), (argc - 1));
	if (tmp_ary == NULL)
		return ;
	while (cnt < argc - 1)
	{
		tmp_ary[cnt] = curr;
		curr = curr->right;
		cnt++;
	}
	quick_sort(tmp_ary, argc);
	cnt = 0;
	while (cnt < argc - 1)
	{
		tmp_ary[cnt]->idx = cnt;
		cnt++;
	}
	free(tmp_ary);
}

t_node	*fill_stack_a(int argc, char *argv[])
{
	int		cnt;
	t_node	*new;
	t_node	*head;
	t_node	*tail;

	cnt = 0;
	head = NULL;
	tail = NULL;
	while (++cnt < argc)
	{
		new = create_new_node(ft_atoll(argv[cnt]));
		if (new == NULL)
			return (free_if_failed(&head, cnt - 1));
		head = push_front(head, tail, new);
		if (cnt == 1)
			tail = head;
	}
	make_new_index(&head, argc);
	if (head == NULL)
		return (free_if_failed(&head, cnt - 1));
	return (head);
}
