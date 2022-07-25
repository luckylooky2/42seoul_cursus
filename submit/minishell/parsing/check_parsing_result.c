/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing_result.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 21:03:06 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/24 17:04:15 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (input[i] == '|' || input[i] == '&' || input[i] == ';')
			break ;
		else if (input[i] != ' ')
			return (i);
	}
	while (input[++j])
	{
		if (input[j] == '|' || input[j] == '&' || input[j] == ';')
			break ;
		else if (input[j] != ' ')
			return (j);
	}
	return (-1);
}

static int	there_are_subshell_parsing_error(t_syntax *syntax)
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
			if (check_characters_inside(syntax->input, i, j))
				parsing_error(NULL, ")", 0);
			else if (check_characters_outside(syntax->input, i, j) == -1)
				continue ;
			else if (check_characters_outside(syntax->input, i, j) < i)
				parsing_error(syntax->input, NULL, i + 1);
			else
				parsing_error(syntax->input, NULL, j + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	there_are_redirection_parsing_error(t_syntax *s, int i)
{
	while (s->input[++i])
	{
		if ((s->input[i] == '>' || s->input[i] == '<') && s->meaning[i] == 1)
		{
			if (!ft_strncmp(s->input + i, "<>", 2) || \
			!ft_strncmp(s->input + i, "<<>", 3) || \
			!ft_strncmp(s->input + i, ">>>", 3))
				parsing_error(NULL, ">", 0);
			else if (!ft_strncmp(s->input + i, "><", 2) || \
			!ft_strncmp(s->input + i, ">><", 3) || \
			!ft_strncmp(s->input + i, "<<<", 3))
				parsing_error(NULL, "<", 0);
			else
			{
				while ((s->input[i + 1] == '>' || s->input[i + 1] == '<'))
					i++;
				if (check_characters_outside(s->input, 0, i) != -1)
					continue ;
				parsing_error(s->input, NULL, i + 1);
			}
			return (1);
		}
	}
	return (0);
}

int	_parsing_error_on_syntax(t_syntax *syntax)
{
	int	i;

	i = -1;
	return (there_are_subshell_parsing_error(syntax) || \
		there_are_redirection_parsing_error(syntax, i));
}
