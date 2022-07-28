/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ampersand_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 17:56:57 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/28 15:57:43 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_bonus.h"

int	there_is_only_one_ampersand(t_syntax *s)
{
	int	i;

	i = 0;
	while (s->input[i])
	{
		if (s->input[i] == '&' && s->meaning[i] == 1)
		{
			if (s->input[i + 1] != '&')
			{
				parsing_error(s, NULL, i);
				return (1);
			}
			i++;
		}
		i++;
	}
	return (0);
}
