/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 12:37:55 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/02 11:27:01 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line_bonus.h"
#include "../include/push_swap_bonus.h"

int	apply_command(t_node **stack_a, t_node **stack_b, char *cmd)
{
	if (cmd[0] == 'p' && cmd[1] == 'a' && cmd[2] == '\n')
		push_a(stack_a, stack_b, 1);
	else if (cmd[0] == 'p' && cmd[1] == 'b' && cmd[2] == '\n')
		push_b(stack_a, stack_b, 1);
	else if (cmd[0] == 's' && cmd[1] == 'a' && cmd[2] == '\n')
		swap_a(stack_a, 1);
	else if (cmd[0] == 's' && cmd[1] == 'b' && cmd[2] == '\n')
		swap_b(stack_b, 1);
	else if (cmd[0] == 's' && cmd[1] == 's' && cmd[2] == '\n')
		swap_s(stack_a, stack_b, 1);
	else if (cmd[0] == 'r' && cmd[1] == 'a' && cmd[2] == '\n')
		rotate_a(stack_a, 1);
	else if (cmd[0] == 'r' && cmd[1] == 'b' && cmd[2] == '\n')
		rotate_b(stack_b, 1);
	else if (cmd[0] == 'r' && cmd[1] == 'r' && cmd[2] == '\n')
		rotate_r(stack_a, stack_b, 1);
	else if (cmd[0] == 'r' && cmd[1] == 'r' && cmd[2] == 'a' && cmd[3] == '\n')
		reverse_rotate_a(stack_a, 1);
	else if (cmd[0] == 'r' && cmd[1] == 'r' && cmd[2] == 'b' && cmd[3] == '\n')
		reverse_rotate_b(stack_b, 1);
	else if (cmd[0] == 'r' && cmd[1] == 'r' && cmd[2] == 'r' && cmd[3] == '\n')
		reverse_rotate_r(stack_a, stack_b, 1);
	else
		return (0);
	return (1);
}

void	print_result(t_node **stack_a, t_node **stack_b, int argc)
{
	if (*stack_b != NULL)
	{
		while (*stack_b != NULL)
			push_a(stack_a, stack_b, 1);
		write(1, "KO\n", 3);
		return ;
	}
	if (check_sorted(stack_a, argc - 2) == 1)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
}

int	check_command(t_node **stack_a, t_node **stack_b)
{
	char	*cmd;

	cmd = NULL;
	while (1)
	{
		cmd = get_next_line(0);
		if (cmd == NULL)
			break ;
		if (apply_command(stack_a, stack_b, cmd) == 0)
		{
			write(2, "Error\n", 6);
			while (*stack_b != NULL)
				push_a(stack_a, stack_b, 1);
			free(cmd);
			return (0);
		}
		free(cmd);
	}
	return (1);
}

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
		exit(EXIT_FAILURE);
	stack_a = fill_stack_a(argc, new_argv);
	free_new_argv(&new_argv);
	if (stack_a == NULL)
		exit(EXIT_FAILURE);
	if (check_command(&stack_a, &stack_b) == 1)
		print_result(&stack_a, &stack_b, argc);
	free_linked_list(&stack_a, argc - 1);
	exit(EXIT_SUCCESS);
}
