/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 14:42:50 by chanhyle          #+#    #+#             */
/*   Updated: 2022/04/25 22:33:04 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

void *ft_calloc(size_t nmemb, size_t size)
{
	void *new_str;
	size_t i;

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

long long ft_atoll(const char *nptr) // input을 long long 자료형으로 변환
{
	int i;
	int sign;
	long long longlong;

	i = 0;
	sign = 1;
	longlong = 0;
	while ((9 <= *nptr && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while ('0' <= nptr[i] && nptr[i] <= '9')
		longlong = longlong * 10 + (nptr[i++] - '0');
	if (sign == -1)
		longlong *= -1;
	if (sign == 1 && (longlong < 0 || i > 19))
		return (-1);
	else if (sign == -1 && (longlong > 0 || i > 19))
		return (0);
	else
		return (longlong);
}

static int ft_number_of_digits(int n)
{
	int len;

	len = 1;
	if (n <= 0)
	{
		len++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char *ft_itoa(int n)
{
	char *new_str;
	int len;

	if (n == -2147483648)
	{
		new_str = ft_itoa(n + 1);
		new_str[10] = '8';
		return (new_str);
	}
	len = ft_number_of_digits(n);
	new_str = (char *)ft_calloc(len, sizeof(char));
	if (new_str == NULL)
		return (NULL);
	new_str[0] = '0';
	if (n < 0)
	{
		n *= -1;
		new_str[0] = '-';
	}
	while (n > 0)
	{
		new_str[len-- - 2] = n % 10 + '0';
		n /= 10;
	}
	return (new_str);
}

size_t ft_strlen(const char *s)
{
	size_t cnt;

	cnt = 0;
	while (s[cnt])
		cnt++;
	return (cnt);
}

void print_stack(t_node *stack, int cnt) // stack 출력
{
	int i;
	char *num_ptr;

	i = 0;
	write(1, "bottom | ", 10);
	if (stack == NULL)
		write(1, "null ", 6);
	else
	{
		while (i < cnt)
		{
			num_ptr = ft_itoa(stack->data);
			write(1, num_ptr, ft_strlen(num_ptr));
			write(1, " ", 1);
			stack = stack->right;
			i++;
		}
	}
	write(1, "| top", 6);
}

void swap_a(t_node **stack_a, int flag)
{
	t_node *tail;
	t_node *tail_left;
	t_node *tail_left_left;

	if (*stack_a == NULL || *stack_a == (*stack_a)->right)
		return;
	if (flag == 0)
		write(1, "sa\n", 3);
	tail = (*stack_a)->left;
	tail_left = tail->left;
	tail_left_left = tail->left->left;
	if (tail_left == *stack_a)
		*stack_a = (*stack_a)->left;
	else if (tail_left->left == *stack_a)
	{
		(*stack_a)->right = tail;
		(*stack_a)->left = tail_left;
		tail_left->right = *stack_a;
		tail_left->left = tail;
		tail->right = tail_left;
		tail->left = *stack_a;
	}
	else
	{
		tail->right = tail_left;
		tail->left = tail_left_left;
		tail_left->right = *stack_a;
		tail_left->left = tail;
		(*stack_a)->left = tail_left;
		tail_left_left->right = tail;
	}
}

void swap_b(t_node **stack_b, int flag)
{
	t_node *tail;
	t_node *tail_left;
	t_node *tail_left_left;

	if (*stack_b == NULL || *stack_b == (*stack_b)->right)
		return;
	if (flag == 0)
		write(1, "sb\n", 3);
	tail = (*stack_b)->left;
	tail_left = tail->left;
	tail_left_left = tail->left->left;
	if (tail_left == *stack_b)
		*stack_b = (*stack_b)->left;
	else if (tail_left->left == *stack_b)
	{
		(*stack_b)->right = tail;
		(*stack_b)->left = tail_left;
		tail_left->right = *stack_b;
		tail_left->left = tail;
		tail->right = tail_left;
		tail->left = *stack_b;
	}
	else
	{
		tail->right = tail_left;
		tail->left = tail_left_left;
		tail_left->right = *stack_b;
		tail_left->left = tail;
		(*stack_b)->left = tail_left;
		tail_left_left->right = tail;
	}
}

void swap_s(t_node **stack_a, t_node **stack_b, int flag)
{
	flag = 1;
	if (*stack_a == NULL || *stack_a == (*stack_a)->right || *stack_b == NULL || *stack_b == (*stack_b)->right)
		return;
	write(1, "ss\n", 3);
	swap_a(stack_a, flag);
	swap_b(stack_b, flag);
}

void push_a(t_node **stack_a, t_node **stack_b, int flag)
{
	t_node *a_tail;
	t_node *b_tail;
	t_node *b_tail_left;

	if (*stack_b == NULL)
		return;
	if (flag == 0)
		write(1, "pa\n", 3);
	a_tail = NULL;
	b_tail = (*stack_b)->left;
	b_tail_left = b_tail->left;
	if (*stack_a == NULL) // b->a
	{
		*stack_a = b_tail;
		b_tail = b_tail->left;
		(*stack_a)->left = *stack_a;
		(*stack_a)->right = *stack_a;
		if (*stack_b == (*stack_b)->right)
		{
			*stack_b = NULL;
			return;
		}
		b_tail->right = *stack_b;
		(*stack_b)->left = b_tail;
	}
	else
	{
		a_tail = (*stack_a)->left;
		if (a_tail == a_tail->right)
		{
			a_tail->left = b_tail;
			b_tail->right = a_tail;
			b_tail->left = a_tail;
			a_tail->right = b_tail;
			if ((*stack_b)->right == *stack_a)
			{
				*stack_b = NULL;
				return;
			}
			b_tail_left->right = *stack_b;
			(*stack_b)->left = b_tail_left;
		}
		else
		{
			a_tail->right = b_tail;
			b_tail->left = a_tail;
			b_tail->right = *stack_a;
			(*stack_a)->left = b_tail;
			if ((*stack_b)->right == *stack_a)
			{
				*stack_b = NULL;
				return;
			}
			b_tail_left->right = *stack_b;
			(*stack_b)->left = b_tail_left;
		}
	}
}

void push_b(t_node **stack_a, t_node **stack_b, int flag)
{
	t_node *a_tail;
	t_node *a_tail_left;
	t_node *b_tail;

	if (*stack_a == NULL)
		return;
	if (flag == 0)
		write(1, "pb\n", 3);
	a_tail = (*stack_a)->left;
	a_tail_left = a_tail->left;
	b_tail = NULL;
	if (*stack_b == NULL) // stack_b가 비었을 때
	{
		*stack_b = a_tail;
		a_tail = a_tail->left;
		(*stack_b)->left = *stack_b;
		(*stack_b)->right = *stack_b;
		if (*stack_a == (*stack_a)->right)
		{
			*stack_a = NULL;
			return;
		}
		a_tail->right = *stack_a;
		(*stack_a)->left = a_tail;
	}
	else // stack_b에 하나 이상 있을 때
	{
		b_tail = (*stack_b)->left;
		if (b_tail == b_tail->right) // stack_b에 하나 있을 떄
		{
			b_tail->left = a_tail;
			a_tail->right = b_tail;
			a_tail->left = b_tail;
			b_tail->right = a_tail;
			if ((*stack_a)->right == *stack_b)
			{
				*stack_a = NULL;
				return;
			}
			a_tail_left->right = *stack_a;
			(*stack_a)->left = a_tail_left;
		}
		else
		{
			b_tail->right = a_tail;
			a_tail->left = b_tail;
			a_tail->right = *stack_b;
			(*stack_b)->left = a_tail;
			if ((*stack_a)->right == *stack_b)
			{
				*stack_a = NULL;
				return;
			}
			a_tail_left->right = *stack_a;
			(*stack_a)->left = a_tail_left;
		}
	}
}

void rotate_a(t_node **stack_a, int flag)
{
	if (*stack_a == NULL)
		return;
	if (flag == 0)
		write(1, "ra\n", 3);
	*stack_a = (*stack_a)->left;
}

void rotate_b(t_node **stack_b, int flag)
{
	if (*stack_b == NULL)
		return;
	if (flag == 0)
		write(1, "rb\n", 3);
	*stack_b = (*stack_b)->left;
}

void rotate_r(t_node **stack_a, t_node **stack_b, int flag)
{
	flag = 1;
	if (*stack_a == NULL || *stack_b == NULL)
		return;
	write(1, "rr\n", 3);
	rotate_a(stack_a, flag);
	rotate_b(stack_b, flag);
}

void reverse_rotate_a(t_node **stack_a, int flag)
{
	if (*stack_a == NULL)
		return;
	if (flag == 0)
		write(1, "rra\n", 4);
	*stack_a = (*stack_a)->right;
}

void reverse_rotate_b(t_node **stack_b, int flag)
{
	if (*stack_b == NULL)
		return;
	if (flag == 0)
		write(1, "rrb\n", 4);
	*stack_b = (*stack_b)->right;
}

void reverse_rotate_r(t_node **stack_a, t_node **stack_b, int flag)
{
	flag = 1;
	if (*stack_a == NULL || *stack_b == NULL)
		return;
	write(1, "rrr\n", 4);
	reverse_rotate_a(stack_a, flag);
	reverse_rotate_b(stack_b, flag);
}

void sort_three_items(t_node **stack_a, t_node **stack_b, int num)
{
	int first;
	int second;
	int third;

	first = (*stack_a)->left->idx;
	second = (*stack_a)->left->left->idx;
	third = (*stack_a)->left->left->left->idx;
	if (num <= 2)
	{
		if (first > second)
			swap_a(stack_a, 0);
	}
	else if (first < second && third < second && first < third) // 1 3 2 4
	{
		rotate_a(stack_a, 0);
		swap_a(stack_a, 0);
		reverse_rotate_a(stack_a, 0);
	}
	else if (first < second && second > third && third < first) // 2 3 1 4
	{
		push_b(stack_a, stack_b, 0);
		swap_a(stack_a, 0);
		rotate_a(stack_a, 0);
		push_a(stack_a, stack_b, 0);
		reverse_rotate_a(stack_a, 0);
	}
	else if (first > second && second < third && third > first) // 2 1 3 4
		swap_a(stack_a, 0);
	else if (first > second && second < third && third < first) // 3 1 2 4
	{
		swap_a(stack_a, 0);
		rotate_a(stack_a, 0);
		swap_a(stack_a, 0);
		reverse_rotate_a(stack_a, 0);
	}
	else if (first > second && second > third) // 3 2 1 4
	{
		swap_a(stack_a, 0);
		push_b(stack_a, stack_b, 0);
		swap_a(stack_a, 0);
		push_a(stack_a, stack_b, 0);
		swap_a(stack_a, 0);
	}
}

void sort_reverse_three_items(t_node **stack_a, t_node **stack_b, int num)
{
	int first;
	int second;
	int third;

	first = (*stack_b)->left->idx;
	second = (*stack_b)->left->left->idx;
	third = (*stack_b)->left->left->left->idx;
	if (num == 2)
	{
		if (first < second)
			swap_b(stack_b, 0);
	}
	else if (first < second && third < second && first < third) // 1 3 2 4
	{
		swap_b(stack_b, 0);
		push_a(stack_a, stack_b, 0);
		swap_b(stack_b, 0);
	}
	else if (first < second && second > third && third < first) // 2 3 1 4
	{
		swap_b(stack_b, 0);
		push_a(stack_a, stack_b, 0);
	}
	else if (first > second && second < third && third > first) // 2 1 3 4
	{
		push_a(stack_a, stack_b, 0);
		swap_b(stack_b, 0);
		push_a(stack_a, stack_b, 0);
		swap_a(stack_a, 0);
		push_a(stack_a, stack_b, 0);
		return;
	}
	else if (first > second && second < third && third < first) // 3 1 2 4
	{
		push_a(stack_a, stack_b, 0);
		swap_b(stack_b, 0);
	}
	else if (first < second && second < third) // 1 2 3 4
	{
		rotate_b(stack_b, 0);
		swap_b(stack_b, 0);
		push_a(stack_a, stack_b, 0);
		push_a(stack_a, stack_b, 0);
		reverse_rotate_b(stack_b, 0);
		push_a(stack_a, stack_b, 0);
		return;
	}
	else
		push_a(stack_a, stack_b, 0);
	push_a(stack_a, stack_b, 0);
	push_a(stack_a, stack_b, 0);
}

void sort_only_three_items(t_node **stack_a)
{
	int first;
	int second;
	int third;

	first = (*stack_a)->left->idx;
	second = (*stack_a)->right->idx;
	third = (*stack_a)->idx;
	if (first < second && third < second && first < third) // 1 3 2
	{
		rotate_a(stack_a, 0);
		swap_a(stack_a, 0);
		reverse_rotate_a(stack_a, 0);
	}
	else if (first < second && second > third && third < first) // 2 3 1
		reverse_rotate_a(stack_a, 0);
	else if (first > second && second < third && third > first) // 2 1 3
		swap_a(stack_a, 0);
	else if (first > second && second < third && third < first) // 3 1 2
		rotate_a(stack_a, 0);
	else if (first > second && second > third) // 3 2 1
	{
		rotate_a(stack_a, 0);
		swap_a(stack_a, 0);
	}
}

void sort_only_five_items(t_node **stack_a, t_node **stack_b)
{
	int cnt;

	cnt = 0;
	while (cnt < 5)
	{
		if ((*stack_a)->left->idx < 2)
			push_b(stack_a, stack_b, 0);
		else
			rotate_a(stack_a, 0);
		cnt++;
	}
	sort_only_three_items(stack_a);
	if ((*stack_b)->idx > (*stack_b)->right->idx)
		swap_b(stack_b, 0);
	push_a(stack_a, stack_b, 0);
	push_a(stack_a, stack_b, 0);
}

int find_index(t_node **stack_b, int num, int flag)
{
	t_node *curr;
	int big;
	int small;
	int cnt;

	if (num == 0)
		return (0);
	cnt = 1;
	curr = (*stack_b)->left;
	big = curr->idx;
	small = curr->idx;
	curr = curr->left;
	while (cnt < num)
	{
		if (curr->idx > big)
			big = curr->idx;
		if (curr->idx < small)
			small = curr->idx;
		cnt++;
		curr = curr->left;
	}
	if (flag == 1)
		return (big);
	return (small);
}

int check_straight(t_node **stack, int num)
{
	t_node *prev;
	t_node *next;
	int cnt;
	int res;

	prev = (*stack)->left;
	next = (*stack)->left->left;
	cnt = 0;
	res = 0;
	while (cnt < num - 1)
	{
		if (prev->idx + 1 == next->idx)
			res++;
		prev = prev->left;
		next = next->left;
		cnt++;
	}
	if (cnt == res)
		return (1);
	return (0);
}

int check_sorted(t_node **stack, int num)
{
	t_node *prev;
	t_node *next;
	int cnt;
	int res;

	prev = (*stack)->left;
	next = (*stack)->left->left;
	cnt = 0;
	res = 0;
	while (cnt < num)
	{
		if (prev->idx + 1 == next->idx)
			res++;
		prev = prev->left;
		next = next->left;
		cnt++;
	}
	if (cnt == res)
		return (1);
	return (0);
}

void init_aux(t_aux *aux)
{
	aux->pa_cnt = 0;
	aux->pb_cnt = 0;
	aux->ra_cnt = 0;
	aux->rb_cnt = 0;
	aux->sorted_cnt = 0;
	aux->big = 0;
	aux->small = 0;
}

int set_pivot(t_node **stack_a, t_node **stack_b, int num, int flag)
{
	int max;
	int min;

	max = find_index(stack_b, num, 1);
	min = find_index(stack_b, num, 0);
	if (flag == 1)
		return (min + (max - min) * 0.75);
	else
		return (min + (max - min) * 0.5);
}

void move_b_to_a(t_node **stack_a, t_node **stack_b, int num, int argc) // stack_a -> stack_b
{
	int cnt;
	t_aux aux;

	cnt = 0;
	init_aux(&aux);
	aux.big = set_pivot(stack_a, stack_b, num, 1);
	aux.small = set_pivot(stack_a, stack_b, num, 0);
	if (num == 0)
		return;
	if (num == 1)
	{
		push_a(stack_a, stack_b, 0);
		return;
	}
	else if (num <= 3)
	{
		sort_reverse_three_items(stack_a, stack_b, num);
		return;
	}
	while (cnt < num)
	{
		if ((*stack_b)->left->idx >= aux.small)
		{
			push_a(stack_a, stack_b, 0); // 나중에 인자로 줘서 줄 절약할 것
			(aux.pa_cnt)++;
			if (check_sorted(stack_a, num) == 1) // 제대로 정렬되어 있는지 체크
				(aux.sorted_cnt)++;
			else
			{
				if ((*stack_a)->left->idx < aux.big)
				{
					rotate_a(stack_a, 0);
					(aux.ra_cnt)++;
				}
			}
		}
		else
		{
			rotate_b(stack_b, 0);
			(aux.rb_cnt)++;
		}
		cnt++;
	}
	move_a_to_b(stack_a, stack_b, aux.pa_cnt - aux.ra_cnt - aux.sorted_cnt, argc);
	aux.sorted_cnt = 0;
	cnt = -1;
	while (++cnt < aux.ra_cnt)
	{
		reverse_rotate_r(stack_a, stack_b, 0);
		if (check_sorted(stack_a, num) == 1)
			(aux.sorted_cnt)++;
	}
	while (cnt++ < aux.rb_cnt)
		reverse_rotate_b(stack_b, 0);
	move_a_to_b(stack_a, stack_b, aux.ra_cnt - aux.sorted_cnt, argc);
	move_b_to_a(stack_a, stack_b, aux.rb_cnt, argc);
}

void move_a_to_b(t_node **stack_a, t_node **stack_b, int num, int argc) // stack_a -> stack_b
{
	int cnt;
	t_aux aux;

	cnt = 0;
	init_aux(&aux);
	aux.big = (argc - num) + (num * 0.55);
	aux.small = (argc - num) + (num * 0.4);
	if (num <= 3)
	{
		sort_three_items(stack_a, stack_b, num);
		return;
	}
	while (cnt < num)
	{
		if ((*stack_a)->left->idx < aux.big)
		{
			push_b(stack_a, stack_b, 0); // 나중에 인자로 줘서 줄 절약할 것
			(aux.pb_cnt)++;
			if ((*stack_b)->left->idx >= aux.small)
			{
				rotate_b(stack_b, 0);
				(aux.rb_cnt)++;
			}
		}
		else
		{
			rotate_a(stack_a, 0);
			(aux.ra_cnt)++;
		}
		cnt++;
	}
	cnt = -1;
	while (++cnt < aux.rb_cnt)
		reverse_rotate_b(stack_b, 0);
	move_a_to_b(stack_a, stack_b, aux.ra_cnt, argc);
	move_b_to_a(stack_a, stack_b, aux.rb_cnt, argc);
	move_b_to_a(stack_a, stack_b, aux.pb_cnt - aux.rb_cnt, argc);
}

t_node *sort_stack_a(t_node *stack_a, t_node *stack_b, int num, int argc) // argc - 1 : 인자 개수만큼 들어옴
{
	if (num == 3)
		sort_only_three_items(&stack_a);
	// else if (num == 4)
	// 	sort_only_four_items(&stack_a);
	else if (num == 5)
		sort_only_five_items(&stack_a, &stack_b);
	else
		move_a_to_b(&stack_a, &stack_b, num, argc);
	return (stack_a);
}

int check_input(int argc, char *argv[]) // input 검사(중복 체크 x)
{
	int i;
	int j;

	i = 0;
	while (++i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(('0' <= argv[i][j] && argv[i][j] <= '9') || argv[i][j] == '+' || argv[i][j] == '-') ||
				((argv[i][j] == '+' || argv[i][j] == '-') && !('0' <= argv[i][j + 1] && argv[i][j + 1] <= '9')))
				return (-1);
			j++;
		}
		if (argv[i][0] == '-' && (j > 11 || ft_atoll(argv[i]) < -2147483648LL))
			return (-1);
		else if (argv[i][0] != '-' && (j > 10 || ft_atoll(argv[i]) > 2147483647LL))
			return (-1);
	}
	return (0);
}

int check_repeat(int argc, char *argv[])
{
	int i;
	int j;
	int crt;

	i = 0;
	while (++i < argc)
	{
		j = i + 1;
		crt = ft_atoll(argv[i]);
		while (j < argc)
		{
			if (crt == ft_atoll(argv[j]))
				return (-1);
			j++;
		}
	}
	return (0);
}

t_node *free_if_failed(t_node **head, int cnt) //실패 시 free
{
	int i;
	t_node *next;

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

void free_linked_list(t_node **head, int cnt) //실패 시 free
{
	int i;
	t_node *next;

	i = 0;
	next = (*head)->right;
	while (i < cnt)
	{
		free(*head);
		*head = next;
		next = next->right;
		i++;
	}
}

t_node *create_new_node(int content) //노드 생성
{
	t_node *new;

	new = (t_node *)ft_calloc(sizeof(t_node), 1);
	if (new == NULL)
		return (NULL);
	new->data = content;
	new->left = new;
	new->right = new;
	return (new);
}

t_node *push_front(t_node *head, t_node *tail, t_node *new) // head로 push
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

void swap(t_node **tmp_ary, int i, int j)
{
	t_node *temp;

	temp = tmp_ary[i];
	tmp_ary[i] = tmp_ary[j];
	tmp_ary[j] = temp;
}

int partition(t_node **tmp_ary, int left, int right, int argc)
{
	int pivot; // 피벗의 위치는 가장 왼쪽에서 시작
	int low;
	int high;

	pivot = tmp_ary[left]->data;
	low = left + 1;
	high = right;

	while (low <= high) // 교차되기 전까지 반복한다
	{
		while (low <= right && pivot >= tmp_ary[low]->data)		   // 피벗보다 큰 값을 찾는 과정
			low++;												   // low를 오른쪽으로 이동
		while (high >= (left + 1) && pivot <= tmp_ary[high]->data) // 피벗보다 작은 값을 찾는 과정
			high--;												   // high를 왼쪽으로 이동
		if (low <= high)										   // 교차되지 않은 상태이면 스왑 과정 실행
			swap(tmp_ary, low, high);							   // low와 high를 스왑
	}
	swap(tmp_ary, left, high); // 피벗과 high가 가리키는 대상을 교환
	return (high);			   // 옮겨진 피벗의 위치정보를 반환
}

void quick_sort_recursive(t_node **tmp_ary, int left, int right, int argc)
{
	int pivot_position;

	if (left >= right)
		return;
	pivot_position = partition(tmp_ary, left, right, argc);
	quick_sort_recursive(tmp_ary, left, pivot_position - 1, argc);
	quick_sort_recursive(tmp_ary, pivot_position + 1, right, argc);
}

void quick_sort(t_node **tmp_ary, int argc)
{
	int left;
	int right;

	left = 0;
	right = argc - 2;
	quick_sort_recursive(tmp_ary, left, right, argc);
}

void make_new_index(t_node **head, int argc)
{
	int cnt;
	t_node *curr;
	t_node **tmp_ary;

	cnt = 0;
	curr = *head;
	tmp_ary = (t_node **)ft_calloc(sizeof(t_node *), (argc - 1));
	if (tmp_ary == NULL)
		return;
	while (cnt < argc - 1) // 구조체 배열에 배치
	{
		tmp_ary[cnt] = curr;
		curr = curr->right;
		cnt++;
	}
	quick_sort(tmp_ary, argc); //구조체 배열을 정렬
	cnt = 0;
	while (cnt < argc - 1) //정렬된 인덱스를 저장
	{
		tmp_ary[cnt]->idx = cnt;
		cnt++;
	}
	free(tmp_ary);
}

t_node *fill_stack_a(int argc, char *argv[]) // input으로 stack_a 채우기
{
	int cnt;
	t_node *new;
	t_node *head;
	t_node *tail;

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

int main(int argc, char *argv[]) // argc : 1번부터, argc - 1(num): 들어온 인자 개수
{
	t_node *stack_a;
	t_node *stack_b;

	stack_a = NULL;
	stack_b = NULL;
	if (argc < 2)
		return (-1);
	if (check_input(argc, argv) == -1 || check_repeat(argc, argv) == -1)
	{
		write(1, "Error\n", 6);
		exit(-1);
	}
	stack_a = fill_stack_a(argc, argv);
	if (stack_a == NULL)
		exit(-2);
	stack_a = sort_stack_a(stack_a, stack_b, argc - 1, argc - 1); //인자 개수만큼 넘겨 줌
	free_linked_list(&stack_a, argc - 1);
	return (0);
}
