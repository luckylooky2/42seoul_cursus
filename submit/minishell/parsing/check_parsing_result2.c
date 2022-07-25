/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing_result2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 16:01:36 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/24 17:09:43 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	there_are_parse_error_in_subshell(t_syntax *s)
{
	int		i;
	int		j;
	char	*subshell_input;
	t_deq	*parsed_args_in_subshell;

	i = 0;
	while (s->input[i])
	{
		if (s->input[i] == '(' && s->meaning[i] == 1)
		{
			j = i + 1;
			while (s->input[j] != ')' || s->meaning[j] != 1)
				j++;
			subshell_input = s->input + i + 1;
			subshell_input[j - (i + 1)] = 0;
			parsed_args_in_subshell = parse_args(subshell_input);
			subshell_input[j - (i + 1)] = ')';
			if (parsed_args_in_subshell == NULL)
				return (1);
			ft_deq_delete(&parsed_args_in_subshell, delete_linked_commands);
			i = j;
		}
		i++;
	}
	return (0);
}

static int	there_is_only_one_ampersand(t_syntax *s)
{
	int	i;

	i = 0;
	while (s->input[i])
	{
		if (s->input[i] == '&' && s->meaning[i] == 1)
		{
			if (s->input[i + 1] != '&')
			{
				parsing_error(s->input, NULL, i);
				return (1);
			}
			i++;
		}
		i++;
	}
	return (0);
}

int	parsing_error_on_syntax(t_syntax *syntax)
{
	return (there_is_only_one_ampersand(syntax) || \
	_parsing_error_on_syntax(syntax) || \
	there_are_parse_error_in_subshell(syntax));
}
