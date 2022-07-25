/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_funcs2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 21:35:16 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/17 21:43:33 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_str_array(void *arr)
{
	char	**str_arr;

	if (arr == NULL)
		return ;
	str_arr = arr;
	while (*str_arr)
	{
		free(*str_arr);
		*str_arr = NULL;
		str_arr++;
	}
	free(arr);
}

void	delete_t_state(void *arg)
{
	t_state	*state;
	int		i;

	if (arg == NULL)
		return ;
	state = arg;
	free(state->pid);
	state->pid = NULL;
	i = 0;
	while (i < state->pipe_cnt)
	{
		free(state->pipes[i]);
		state->pipes[i++] = NULL;
	}
	free(state->pipes);
	state->pipes = NULL;
	delete_str_array(state->path);
	state->path = NULL;
}
