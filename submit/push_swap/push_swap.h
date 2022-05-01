/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 09:04:50 by chanhyle          #+#    #+#             */
/*   Updated: 2022/04/24 09:04:54 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <unistd.h>
#include <stdlib.h>

typedef struct s_node
{
    struct s_node *left;
    int data;
    int idx;
    struct s_node *right;
} t_node;

typedef struct s_aux
{
    int pa_cnt;
    int pb_cnt;
    int ra_cnt;
    int rb_cnt;
    int sorted_cnt;
    int big;
    int small;
} t_aux;

long long ft_atoll(const char *nptr);
void print_stack(t_node *stack, int cnt);
void swap_a(t_node **stack_a, int flag);
void swap_b(t_node **stack_b, int flag);
void swap_s(t_node **stack_a, t_node **stack_b, int flag);
void push_a(t_node **stack_a, t_node **stack_b, int flag);
void push_b(t_node **stack_a, t_node **stack_b, int flag);
void rotate_a(t_node **stack_a, int flag);
void rotate_b(t_node **stack_b, int flag);
void rotate_r(t_node **stack_a, t_node **stack_b, int flag);
void reverse_rotate_a(t_node **stack_a, int flag);
void reverse_rotate_b(t_node **stack_b, int flag);
void reverse_rotate_r(t_node **stack_a, t_node **stack_b, int flag);
void sort_three_items(t_node **stack_a, t_node **stack_b, int num);
void sort_reverse_three_items(t_node **stack_a, t_node **stack_b, int num);
void init_aux(t_aux *aux);
int find_index(t_node **stack_b, int num, int flag);
int set_pivot(t_node **stack_a, t_node **stack_b, int num, int flag);
void move_b_to_a(t_node **stack_a, t_node **stack_b, int num, int argc); // stack_a -> stack_b
void move_a_to_b(t_node **stack_a, t_node **stack_b, int num, int argc); // stack_a -> stack_b
t_node *sort_stack_a(t_node *stack_a, t_node *stack_b, int num, int argc);
int check_input(int argc, char *argv[]);
void free_linked_list(t_node **head, int cnt);
t_node *create_new_node(int content);
t_node *push_front(t_node *head, t_node *tail, t_node *new);
void swap(t_node **tmp_ary, int i, int j);
int partition(t_node **tmp_ary, int left, int right, int argc);
void quick_sort_recursive(t_node **tmp_ary, int left, int right, int argc);
void quick_sort(t_node **tmp_ary, int argc);
void make_new_index(t_node **head, int argc);
t_node *fill_stack_a(int argc, char *argv[]);

#endif
