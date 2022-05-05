/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 09:04:50 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/05 22:45:59 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <unistd.h>
# include <stdlib.h>

typedef struct s_node
{
	struct s_node	*left;
	int				data;
	int				idx;
	struct s_node	*right;
}	t_node;

typedef struct s_aux
{
	int	cnt;
	int	pa;
	int	pb;
	int	ra;
	int	rb;
	int	sorted;
	int	big;
	int	small;
}	t_aux;

typedef struct s_sort
{
	int	one;
	int	two;
	int	three;
}	t_sort;

void		swap_a(t_node **stack_a, int flag);
void		swap_b(t_node **stack_b, int flag);
void		swap_s(t_node **stack_a, t_node **stack_b, int flag);
void		push_a(t_node **stack_a, t_node **stack_b, int flag);
void		push_b(t_node **stack_a, t_node **stack_b, int flag);
void		rotate_a(t_node **stack_a, int flag);
void		rotate_b(t_node **stack_b, int flag);
void		rotate_r(t_node **stack_a, t_node **stack_b, int flag);
void		reverse_rotate_a(t_node **stack_a, int flag);
void		reverse_rotate_b(t_node **stack_b, int flag);
void		reverse_rotate_r(t_node **stack_a, t_node **stack_b, int flag);

void		sort_three(t_node **stack_a, t_node **stack_b, int num);
void		sort_reverse_three(t_node **stack_a, t_node **stack_b, int num);
void		sort_only_three(t_node **stack_a);
void		sort_only_four(t_node **stack_a, t_node **stack_b);
void		sort_only_five(t_node **stack_a, t_node **stack_b);
void		quick_sort(t_node **tmp_ary, int argc);

void		*ft_calloc(size_t nmemb, size_t size);
long long	ft_atoll(const char *nptr);
size_t		ft_strlen(const char *s);
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char **s1, char *s2);

int			check_sorted(t_node **stack, int num);
int			check_input(int argc, char *argv[]);
int			check_repeat(int argc, char *argv[]);
int			check_blank(char *str);
int			find_index(t_node **stack_b, int num, int flag);
char		**parse_input(char *argv[]);
int			count_argc(char *argv[]);
void		init_aux(t_aux *aux);
void		init_count(t_aux *aux);
int			set_pivot(t_node **stack, int num, int flag);
void		free_linked_list(t_node **head, int cnt);
t_node		*free_if_failed(t_node **head, int cnt);
t_node		*create_new_node(int content);
t_node		*push_front(t_node *head, t_node *tail, t_node *new);
void		make_new_index(t_node **head, int argc);

void		move_a_to_b(t_node **stack_a, t_node **stack_b, int num, int argc);
void		move_b_to_a(t_node **stack_a, t_node **stack_b, int num, int argc);
t_node		*sort_stack_a(t_node *stack_a, t_node *stack_b, int num, int argc);
t_node		*fill_stack_a(int argc, char *argv[]);

#endif
