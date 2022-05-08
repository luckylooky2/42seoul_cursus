/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 14:42:50 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/09 00:45:54 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static	int	check_error(int argc, char *argv[], char **new_argv)
{
	if (argv[1] == NULL || check_input(argc, new_argv) == -1
		|| check_repeat(argc, new_argv) == -1)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_node	*stack_a;
	t_node	*stack_b;
	char	**new_argv;

	stack_a = NULL;
	stack_b = NULL;
	if (argc < 2)
		exit(EXIT_FAILURE);
	new_argv = parse_input(argv);
	if (new_argv == NULL)
		exit(EXIT_FAILURE);
	argc = count_argc(new_argv);
	if (check_error(argc, argv, new_argv) == 1)
	{
		new_argv = free_new_argv(new_argv);
		exit(EXIT_FAILURE);
	}
	stack_a = fill_stack_a(argc, new_argv);
	new_argv = free_new_argv(new_argv);
	if (stack_a == NULL)
		exit(EXIT_FAILURE);
	if (check_sorted(&stack_a, argc - 2) == 0)
		stack_a = sort_stack_a(stack_a, stack_b, argc - 1, argc - 1);
	free_linked_list(&stack_a, argc - 1);
	return (0);
}
