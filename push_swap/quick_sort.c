/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 14:44:08 by chanhyle          #+#    #+#             */
/*   Updated: 2022/03/07 17:27:02 by chanhyle         ###   ########.fr       */
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

void swap(int *stack_a, int i, int j) //나머지 경우
{
	int temp;

	temp = stack_a[i];
	stack_a[i] = stack_a[j];
	stack_a[j] = temp;
}

int partition(int *stack_a, int left, int right, int argc)
{
	int pivot; // 피벗의 위치는 가장 왼쪽에서 시작
	int low;
	int high;

	pivot = stack_a[left];
	low = left + 1;
	high = right;

	while (low <= high) // 교차되기 전까지 반복한다
	{
		while (low <= right && pivot >= stack_a[low])		 // 피벗보다 큰 값을 찾는 과정
			low++;											 // low를 오른쪽으로 이동
		while (high >= (left + 1) && pivot <= stack_a[high]) // 피벗보다 작은 값을 찾는 과정
			high--;											 // high를 왼쪽으로 이동
		if (low <= high)									 // 교차되지 않은 상태이면 스왑 과정 실행
			swap(stack_a, low, high);						 // low와 high를 스왑
	}
	swap(stack_a, left, high); // 피벗과 high가 가리키는 대상을 교환
	return (high);			   // 옮겨진 피벗의 위치정보를 반환
}

void quick_sort_recursive(int *stack_a, int left, int right, int argc)
{
	int pivot_position;

	if (left >= right)
		return;
	pivot_position = partition(stack_a, left, right, argc);
	printf("left : %d, right : %d, pivot : %d\n", left, right, pivot_position);
	// printf("pivot : %d\n", pivot_position);
	quick_sort_recursive(stack_a, left, pivot_position - 1, argc);
	quick_sort_recursive(stack_a, pivot_position + 1, right, argc);
}

void quick_sort(int *stack_a, int left, int right, int argc)
{
	quick_sort_recursive(stack_a, 0, right, argc);
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
		if (argv[i][0] == '-' && (j > 11 || ft_atoll(argv[i]) < -2147483648LL))
			return (-1);
		else if (argv[i][0] != '-' && (j > 10 || ft_atoll(argv[i]) > 2147483647LL))
			return (-1);
	}
	return (0);
}

int main(int argc, char *argv[])
{
	int i;
	int *stack_a;
	int *stack_b;

	i = 0;
	if (argc < 2)
		return (-1);
	// if (argc < 7)
	// {
	// 	printf("input under 6\n");
	// 	return (-2);
	// }
	if (check_input(argc, argv) == -1) // input 예외 처리
	{
		write(1, "Error\n", 6);
		return (-1);
	}
	stack_a = (int *)calloc(sizeof(int), (argc - 1)); // 스택 동적 할당
	stack_b = (int *)calloc(sizeof(int), (argc - 1));
	while (++i < argc) // input을 스택에 저장
		stack_a[i - 1] = ft_atoll(argv[i]);
	quick_sort(stack_a, 0, argc - 2, argc); // 합병 정렬
	i = 0;									// 정렬된 스택 출력
	while (i < argc - 1)
		printf("%d\n", stack_a[i++]);
	free(stack_a); // 할당 해제
	free(stack_b);
	return (0);
}

// 1. pivot과 high의 차이가 1 -> sa
// 2. pivot과 high의 차이가 2 -> pb / ra / pb sb pa / rra / pa
// 3. pivot과 high의 차이가 3 -> pb / ra ra / pb sb pa / rra rra / pa
// 4. pivot과 high의 차이가 4 -> rra rra / pb / ra / pb sb pa / rra / pa / ra ra
// 5. pivot과 high의 차이가 5 -> rra / sa / ra
