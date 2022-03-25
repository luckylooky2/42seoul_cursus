/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 14:42:50 by chanhyle          #+#    #+#             */
/*   Updated: 2022/03/06 14:43:21 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_node
{
	struct s_node *left;
	int data;
	struct s_node *right;
} t_node;

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

void print_stack(t_node *stack, int cnt) // stack 출력
{
	int i;

	i = 0;
	if (stack == NULL)
	{
		printf("null");
		return;
	}
	printf("bottom | ");
	while (i < cnt)
	{
		printf("%d ", stack->data);
		stack = stack->right;
		i++;
	}
	printf("| top");
}

void swap_a(t_node ***stack_a, int flag)
{
	t_node *tail;
	t_node *tail_left;
	t_node *tail_left_left;

	if (**stack_a == NULL || **stack_a == (**stack_a)->right)
		return;
	tail = (**stack_a)->left;
	tail_left = tail->left;
	tail_left_left = tail->left->left;
	if (tail_left == **stack_a)
		**stack_a = (**stack_a)->left;
	else if (tail_left->left == **stack_a)
	{
		(**stack_a)->right = tail;
		(**stack_a)->left = tail_left;
		tail_left->right = **stack_a;
		tail_left->left = tail;
		tail->right = tail_left;
		tail->left = **stack_a;
	}
	else
	{
		tail->right = tail_left;
		tail->left = tail_left_left;
		tail_left->right = **stack_a;
		tail_left->left = tail;
		(**stack_a)->left = tail_left;
		tail_left_left->right = tail;
	}
	if (flag == 0)
		write(1, "sa\n", 3);
}

void swap_b(t_node ***stack_b, int flag)
{
	t_node *tail;
	t_node *tail_left;
	t_node *tail_left_left;

	if (**stack_b == NULL || **stack_b == (**stack_b)->right)
		return;
	tail = (**stack_b)->left;
	tail_left = tail->left;
	tail_left_left = tail->left->left;
	if (tail_left == **stack_b)
		**stack_b = (**stack_b)->left;
	else if (tail_left->left == **stack_b)
	{
		(**stack_b)->right = tail;
		(**stack_b)->left = tail_left;
		tail_left->right = **stack_b;
		tail_left->left = tail;
		tail->right = tail_left;
		tail->left = **stack_b;
	}
	else
	{
		tail->right = tail_left;
		tail->left = tail_left_left;
		tail_left->right = **stack_b;
		tail_left->left = tail;
		(**stack_b)->left = tail_left;
		tail_left_left->right = tail;
	}
	if (flag == 0)
		write(1, "sb\n", 3);
}

void swap_s(t_node ***stack_a, t_node ***stack_b, int flag)
{
	flag = 1;
	if (**stack_a == NULL || **stack_a == (**stack_a)->right || **stack_b == NULL || **stack_b == (**stack_b)->right)
		return;
	swap_a(stack_a, flag);
	swap_b(stack_b, flag);
	write(1, "ss\n", 3);
}

void push_a(t_node ***stack_a, t_node ***stack_b, int flag)
{
	t_node *a_tail;
	t_node *b_tail;
	t_node *b_tail_left;

	if (**stack_b == NULL)
		return;
	a_tail = NULL;
	b_tail = (**stack_b)->left;
	b_tail_left = b_tail->left;
	if (**stack_a == NULL) // b->a
	{
		**stack_a = b_tail;
		b_tail = b_tail->left;
		(**stack_a)->left = **stack_a;
		(**stack_a)->right = **stack_a;
		if (**stack_b == (**stack_b)->right)
		{
			**stack_b = NULL;
			return;
		}
		b_tail->right = **stack_b;
		(**stack_b)->left = b_tail;
	}
	else
	{
		a_tail = (**stack_a)->left;
		if (a_tail == a_tail->right)
		{
			a_tail->left = b_tail;
			b_tail->right = a_tail;
			b_tail->left = a_tail;
			a_tail->right = b_tail;
			if ((**stack_b)->right == **stack_a)
			{
				**stack_b = NULL;
				return;
			}
			b_tail_left->right = **stack_b;
			(**stack_b)->left = b_tail_left;
		}
		else
		{
			a_tail->right = b_tail;
			b_tail->left = a_tail;
			b_tail->right = **stack_a;
			(**stack_a)->left = b_tail;
			if ((**stack_b)->right == **stack_a)
			{
				**stack_b = NULL;
				return;
			}
			b_tail_left->right = **stack_b;
			(**stack_b)->left = b_tail_left;
		}
	}
	if (flag == 0)
		write(1, "pa\n", 3);
}

void push_b(t_node ***stack_a, t_node ***stack_b, int flag)
{
	t_node *a_tail;
	t_node *a_tail_left;
	t_node *b_tail;

	if (**stack_a == NULL)
		return;
	a_tail = (**stack_a)->left;
	a_tail_left = a_tail->left;
	b_tail = NULL;
	if (**stack_b == NULL) // stack_b가 비었을 때
	{
		**stack_b = a_tail;
		a_tail = a_tail->left;
		(**stack_b)->left = **stack_b;
		(**stack_b)->right = **stack_b;
		if (**stack_a == (**stack_a)->right)
		{
			**stack_a = NULL;
			return;
		}
		a_tail->right = **stack_a;
		(**stack_a)->left = a_tail;
	}
	else // stack_b에 하나 이상 있을 때
	{
		b_tail = (**stack_b)->left;
		if (b_tail == b_tail->right) // stack_b에 하나 있을 떄
		{
			b_tail->left = a_tail;
			a_tail->right = b_tail;
			a_tail->left = b_tail;
			b_tail->right = a_tail;
			if ((**stack_a)->right == **stack_b)
			{
				**stack_a = NULL;
				return;
			}
			a_tail_left->right = **stack_a;
			(**stack_a)->left = a_tail_left;
		}
		else
		{
			b_tail->right = a_tail;
			a_tail->left = b_tail;
			a_tail->right = **stack_b;
			(**stack_b)->left = a_tail;
			if ((**stack_a)->right == **stack_b)
			{
				**stack_a = NULL;
				return;
			}
			a_tail_left->right = **stack_a;
			(**stack_a)->left = a_tail_left;
		}
	}
	if (flag == 0)
		write(1, "pb\n", 3);
}

void rotate_a(t_node ***stack_a, int flag)
{
	if (**stack_a == NULL)
		return;
	**stack_a = (**stack_a)->left;
	if (flag == 0)
		write(1, "ra\n", 3);
}

void rotate_b(t_node ***stack_b, int flag)
{
	if (**stack_b == NULL)
		return;
	**stack_b = (**stack_b)->left;
	if (flag == 0)
		write(1, "rb\n", 3);
}

void rotate_r(t_node ***stack_a, t_node ***stack_b, int flag)
{
	flag = 1;
	if (**stack_a == NULL || **stack_b == NULL)
		return;
	rotate_a(stack_a, flag);
	rotate_b(stack_b, flag);
	write(1, "rr\n", 3);
}

void reverse_rotate_a(t_node ***stack_a, int flag)
{
	if (**stack_a == NULL)
		return;
	**stack_a = (**stack_a)->right;
	if (flag == 0)
		write(1, "rra\n", 4);
}

void reverse_rotate_b(t_node ***stack_b, int flag)
{
	if (**stack_b == NULL)
		return;
	**stack_b = (**stack_b)->right;
	if (flag == 0)
		write(1, "rrb\n", 4);
}

void reverse_rotate_r(t_node ***stack_a, t_node ***stack_b, int flag)
{
	flag = 1;
	if (**stack_a == NULL || **stack_b == NULL)
		return;
	reverse_rotate_a(stack_a, flag);
	reverse_rotate_b(stack_b, flag);
	write(1, "rrr\n", 4);
}

void a_to_b(t_node **stack_a, t_node **stack_b, int argc) // stack_a -> stack_b
{
	// 	int pivot_position;

	// 	if (left >= right)
	// 		return;
	// 	pivot_position = partition(stack_a, left, right, argc);
	// 	printf("left : %d, right : %d, pivot : %d\n", left, right, pivot_position);
	// 	if (left == pivot_position)
	// 		printf("pb\n");
	// 	a_to_b(stack_a, stack_b, argc);
	// 	b_to_a(stack_a, stack_b, argc);
	push_b(&stack_a, &stack_b, 0);
	push_b(&stack_a, &stack_b, 0);
	push_b(&stack_a, &stack_b, 0);
	push_b(&stack_a, &stack_b, 0);
	// push_b(&stack_a, &stack_b, 0);
	// push_a(&stack_a, &stack_b, 0);
	// push_a(&stack_a, &stack_b, 0);
	// push_a(&stack_a, &stack_b, 0);
	// push_a(&stack_a, &stack_b, 0);
	// push_a(&stack_a, &stack_b, 0);
	// rotate_a(&stack_a, 0);
	// // push_b(&stack_a, &stack_b, 0);
	// push_b(&stack_a, &stack_b, 0);
	// reverse_rotate_b(&stack_b, 0);
	// reverse_rotate_a(&stack_a, 0);
	// rotate_r(&stack_a, &stack_b, 0);
	// reverse_rotate_r(&stack_a, &stack_b, 0);
	// push_b(&stack_a, &stack_b, 0);
	swap_a(&stack_a, 0);
	swap_b(&stack_b, 0);
}

t_node *sort_stack_a(t_node *stack_a, t_node *stack_b, int argc)
{
	a_to_b(&stack_a, &stack_b, argc);

	printf("[stack A] ");
	print_stack(stack_a, 10);
	printf("\n");
	printf("[stack B] ");
	print_stack(stack_b, 10);
	printf("\n");
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

void free_if_failed(t_node **head, int cnt) //실패 시 free
{
	int i;
	t_node *next;

	i = 0;
	next = (*head)->right;
	while (i < cnt)
	{
		free(*head);
		if (i == cnt - 1)
			return;
		*head = next;
		if (i != cnt - 2)
			next = next->right;
		i++;
	}
}

t_node *create_new_node(int content) //노드 생성
{
	t_node *new;

	new = (t_node *)calloc(sizeof(t_node), 1);
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
		{
			free_if_failed(&head, cnt - 1);
			return (NULL);
		}
		head = push_front(head, tail, new);
		if (cnt == 1)
			tail = head;
	}
	return (head);
}

int main(int argc, char *argv[])
{
	int i;
	t_node *stack_a;
	t_node *stack_b;

	stack_a = NULL;
	stack_b = NULL;
	if (argc < 2)
		return (-1);
	if (check_input(argc, argv) == -1)
	{
		write(1, "Error\n", 6);
		exit(-1);
	}
	stack_a = fill_stack_a(argc, argv);
	if (stack_a == NULL)
		exit(-2);
	stack_a = sort_stack_a(stack_a, stack_b, argc - 1);
	// print_stack(stack_a, argc - 1);
	return (0);
}

// "a_to_b(r)"
//	1. if (r <= 3) {3개 끼리 정렬}
//  2. 스택 a에서 피봇 2개를 선택(big = mid, small = mid/2)
//  3. 스택 a, b를 나눔
//  	3-1. if (a.top >= big) {ra} else {pb}
//		3-2. if (b.top >= small) {rb}
//  4. ra, rb한 만큼 rra, rrb 수행
//	5. a_to_b(ra), b_to_a(rb), b_to_a(pb - rb) 재귀 호출

// "b_to_a(r)"
//	1. if (r == 1) {pa} else if (r <= 3) {정렬 후 pa}
//  2. 스택 b에서 피봇 2개를 선택(big = mid, small = mid/2)
//  3. 스택 a, b를 나눔
//  	3-1. if (a.top >= big) {ra} else {pb}
//		3-2. if (b.top >= small) {rb}
//  4. ra, rb한 만큼 rra, rrb 수행
//	5. a_to_b(ra), b_to_a(rb), b_to_a(pb - rb) 재귀 호출
