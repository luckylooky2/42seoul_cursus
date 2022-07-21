/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing_result2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 21:03:06 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/19 19:51:37 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	there_are_two_brackets(t_syntax *s)
{
	int	i;
	int	has_decreased;

	if (*s->input == 0)
		return (0);
	i = 1;
	has_decreased = 0;
	while (s->input[i])
	{
		if (s->meaning[i - 1] > s->meaning[i] && 2 <= s->meaning[i - 1])
			has_decreased = 1;
		else if ((s->meaning[i - 1] < s->meaning[i]))
		{
			if (has_decreased && 2 <= s->meaning[i])
			{
				error_handle("parse error near `('");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

static int	check_characters(char *input, int i, int j)
{
	while (0 <= --i)
	{
		if (input[i] == '|')
			break ;
		else if (input[i] != ' ')
			return (1);
	}
	while (input[++j])
	{
		if (input[j] == '|')
			break ;
		else if (input[j] != ' ')
			return (1);
	}
	return (0);
}

static int	there_is_a_meaningful_char_near_bracket(t_syntax *syntax)
{
	int	i;
	int	j;

	i = 0;
	while (syntax->input[i])
	{
		if (syntax->input[i] == '(' && syntax->meaning[i] == 1)
		{
			j = i + 1;
			while (syntax->input[j] != ')' || syntax->meaning[j] != 1)
				j++;
			if (check_characters(syntax->input, i, j))
			{
				error_handle("duplicate commands.");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

static int	there_are_redirection_parsing_error(t_syntax *s)
{
	int		i;
	char	*str;

	i = -1;
	while (s->input[++i])
	{
		if ((s->input[i] == '>' || s->input[i] == '<') && s->meaning[i] == 1)
		{
			str = s->input + i;
			if (!ft_strncmp(str, "<>", 2) || !ft_strncmp(str, "<<>", 3) \
			|| !ft_strncmp(str, ">>>", 3))
				error_handle("parse error near `>'");
			else if (!ft_strncmp(str, "><", 2) || !ft_strncmp(str, ">><", 3) \
			|| !ft_strncmp(str, "<<<", 3))
				error_handle("parse error near `<'");
			else
			{
				while ((s->input[i + 1] == '>' || s->input[i + 1] == '<'))
					i++;
				if (!check_characters(s->input, 0, i))
					error_handle("parse error near `\\n'");
				else
					continue ;
			}
			return (1);
		}
	}
	return (0);
}

int	parsing_error_on_syntax(t_syntax *syntax)
{
	return (there_are_two_brackets(syntax) || \
		there_is_a_meaningful_char_near_bracket(syntax) || \
		there_are_redirection_parsing_error(syntax));
}
