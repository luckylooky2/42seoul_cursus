/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_semicolon.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:11:51 by chanhyle          #+#    #+#             */
/*   Updated: 2022/07/27 17:05:24 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_deq	*break_semicolon(t_syntax *s)
{
	t_deq	*broken_units;
	int		last;
	int		i;

	broken_units = ft_deq_new();
	if (broken_units == NULL)
		panic_memory();
	last = 0;
	i = 0;
	while (s->input[i])
	{
		if (s->meaning[i] == 1 && s->input[i] == ';')
		{
			/* 자르고 syntax를 만들어 deq에 push
				처음 들어갈 때)
				i : semicolon의 위치,
				last = 0 */
			if (ft_deq_push_back(broken_units, \
			slice_syntax(s, last, i - last, SEMICOLON)) == -1)
				panic_memory();
			last = i + 1; // semicolon 뒤에 인덱스
		}
		i++;
	}
	// 제일 마지막에 semicolon이 없는 경우
	if (ft_deq_push_back(broken_units, \
	slice_syntax(s, last, i - last, SEMICOLON)) == -1)
		panic_memory();
	// cleanup을 왜 하는가?
	return (cleanup_deque(broken_units, delete_t_syntax));
}