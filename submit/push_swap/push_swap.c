/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 14:42:50 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/05 22:24:20 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char *argv[])
{
	t_node	*stack_a;
	t_node	*stack_b;

	stack_a = NULL;
	stack_b = NULL;
	if (argc < 2)
		exit(-1);
	argv = parse_input(argv);
	if (argv == NULL)
		exit(-2);
	argc = count_argc(argv);
	if (argv[1] == NULL
		|| check_input(argc, argv) == -1 || check_repeat(argc, argv) == -1)
	{
		write(1, "Error\n", 6);
		exit(-3);
	}
	stack_a = fill_stack_a(argc, argv);
	free(argv);
	if (stack_a == NULL)
		exit(-4);
	if (check_sorted(&stack_a, argc - 2) == 0)
		stack_a = sort_stack_a(stack_a, stack_b, argc - 1, argc - 1);
	free_linked_list(&stack_a, argc - 1);
	return (0);
}
