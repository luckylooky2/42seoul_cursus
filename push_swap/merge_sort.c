/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 14:43:08 by chanhyle          #+#    #+#             */
/*   Updated: 2022/03/06 14:44:34 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

long long ft_atoll(const char *nptr)
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

void merge(long long *stack_a, long long *tmp, int left, int mid, int right, int argc)
{
	int i;
	int left_idx;
	int right_idx;

	i = left;
	left_idx = left;
	right_idx = mid + 1;
	printf("left : %d, mid : %d, right : %d\n", left, mid, right);
	while (left_idx <= mid && right_idx <= right)
	{
		if (stack_a[left_idx] < stack_a[right_idx]) // 한 쪽이 끝날 때까지 tmp에 복사
			tmp[i++] = stack_a[left_idx++];
		else
		{
			tmp[i++] = stack_a[right_idx++];
			write(1, "sa\n", 3);
		}
	}
	if (left_idx > mid) // 남은 쪽을 tmp에 복사
	{
		while (right_idx <= right)
			tmp[i++] = stack_a[right_idx++];
	}
	else
	{
		while (left_idx <= mid)
			tmp[i++] = stack_a[left_idx++];
	}
	int b = 0;
	if (left == 0 && right == (argc - 2) / 2)
	{
		while (b <= right)
		{
			write(1, "pb\n", 3);
			b++;
		}
	}
	while (left <= right) // tmp를 다시 stack_a에 복사
	{
		stack_a[left] = tmp[left];
		left++;
	}
	int a = 0;
	printf("\nstack_a : ");
	while (a <= argc - 2)
		printf("%lld ", stack_a[a++]);
	printf("\n------------------------------\n");
}

void merge_sort(long long *stack_a, long long *tmp, int left, int right, int argc)
{
	int mid;

	if (right == left)
		return;
	mid = (left + right) / 2;
	merge_sort(stack_a, tmp, left, mid, argc);
	merge_sort(stack_a, tmp, mid + 1, right, argc);
	merge(stack_a, tmp, left, mid, right, argc);
}

int check_input(int argc, char *argv[])
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
	}
	return (0);
}

int main(int argc, char *argv[])
{
	int i;
	long long *stack_a;
	long long *stack_b;
	long long *tmp;

	i = 0;
	if (argc < 2)
		return (-1);
	if (check_input(argc, argv) == -1) // input 예외 처리
	{
		write(1, "Error\n", 6);
		return (-1);
	}
	stack_a = (long long *)calloc(sizeof(long long), (argc - 1)); // 스택 동적 할당
	stack_b = (long long *)calloc(sizeof(long long), (argc - 1));
	tmp = (long long *)calloc(sizeof(long long), (argc - 1));
	while (++i < argc) // input을 스택에 저장
		stack_a[i - 1] = ft_atoll(argv[i]);
	merge_sort(stack_a, tmp, 0, argc - 2, argc); // 합병 정렬
	// i = 0;								   // 정렬된 스택 출력
	// while (i < argc - 1)
	// 	printf("%lld\n", stack_a[i++]);
	free(stack_a); // 할당 해제
	free(stack_b);
	free(tmp);
	return (0);
}
