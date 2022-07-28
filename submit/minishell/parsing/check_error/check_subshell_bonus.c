/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_subshell_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 17:55:41 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/28 15:57:58 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_bonus.h"

static int	check_characters_inside(char *input, int i, int j)
{
	int	k;

	k = ++i;
	while (k < j)
	{
		if (input[k] != ' ')
			return (0);
		k++;
	}
	return (1);
}

static int	check_characters_outside(char *input, int i, int j)
{
	while (0 <= --i)
	{
		if (input[i] == '|' || input[i] == '&' || input[i] == ';' || \
		input[i] == ' ')
			break ;
		else
			return (i);
	}
	while (input[++j])
	{
		if (input[j] == '|' || input[j] == '&' || input[j] == ';' || \
		input[j] == ' ' || input[j] == '<' || input[j] == '>')
			break ;
		else
			return (j);
	}
	return (-1);
}

int	there_are_subshell_parsing_error(t_syntax *syntax)
{
	int	i;
	int	j;

	i = -1;
	while (syntax->input[++i])
	{
		if (syntax->input[i] == '(' && syntax->meaning[i] == 1)
		{
			j = i + 1;
			while (syntax->input[j] != ')' || syntax->meaning[j] != 1)
				j++;
			if (check_characters_inside(syntax->input, i, j))
				parsing_error(NULL, ")", 0);
			else if (check_characters_outside(syntax->input, i, j) == -1)
				continue ;
			else if (check_characters_outside(syntax->input, i, j) < i)
				parsing_error(syntax, NULL, i + 1);
			else
				parsing_error(syntax, NULL, j + 1);
			return (1);
		}
	}
	return (0);
}

int	there_are_parse_error_in_subshell(t_syntax *s)
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
			parsed_args_in_subshell = parse_args(subshell_input, SUB);
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
