/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_semicolon.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 19:08:29 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/19 14:44:30 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_deq	*break_semicolon(t_syntax *s)
{
	t_deq	*broken_unit;
	int		last;
	int		i;

	broken_unit = ft_deq_new();
	if (broken_unit == NULL)
		panic_memory();
	last = 0;
	i = 0;
	while (s->input[i])
	{
		if (s->meaning[i] == 1 && s->input[i] == ';')
		{
			if (ft_deq_push_back(broken_unit, \
			slice_syntax(s, last, i - last, SEMICOLON)) == -1)
				panic_memory();
			last = i + 1;
		}
		i++;
	}
	if (ft_deq_push_back(broken_unit, \
	slice_syntax(s, last, i - last, SEMICOLON)) == -1)
		panic_memory();
	return (cleanup_deque(broken_unit, delete_t_syntax));
}
