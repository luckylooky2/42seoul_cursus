/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 17:56:37 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/28 15:57:56 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_bonus.h"

static int	check_filename(t_syntax *s, int i)
{
	int	name_flag;

	name_flag = 0;
	while (s->input[++i])
	{
		if (s->meaning[i] && s->input[i] == '(')
			return (i);
		else if (s->meaning[i] && s->input[i] == ' ' && name_flag == 1)
			name_flag = 2;
		else if (s->meaning[i] && (s->input[i] == ')' || \
		s->input[i] == '|' || s->input[i] == '&' || s->input[i] == ';'))
			break ;
		else if (s->meaning[i] && (s->input[i] == '<' || s->input[i] == '>'))
			return ((name_flag != 2) * i);
		else if (s->input[i] != ' ' && name_flag == 0)
			name_flag = 1;
		if (!s->input[i + 1] && name_flag == 1)
			name_flag = 2;
	}
	return ((name_flag == 0) * i);
}

static int	check_redirection_character(char *input)
{
	if (!ft_strncmp(input, "<>", 2) || !ft_strncmp(input, "<<>", 3) || \
		!ft_strncmp(input, ">>>", 3))
	{
		parsing_error(NULL, ">", 0);
		return (1);
	}
	else if (!ft_strncmp(input, "><", 2) || !ft_strncmp(input, ">><", 3) || \
	!ft_strncmp(input, "<<<", 3))
	{
		parsing_error(NULL, "<", 0);
		return (1);
	}
	return (0);
}

int	there_are_redirection_parsing_error(t_syntax *s)
{
	int	i;
	int	check;

	i = 0;
	while (s->input[i])
	{
		if ((s->input[i] == '>' || s->input[i] == '<') && s->meaning[i])
		{
			if (!check_redirection_character(s->input + i))
			{
				while ((s->input[i + 1] == '>' || s->input[i + 1] == '<'))
					i++;
				check = check_filename(s, i++);
				if (!check)
					continue ;
				parsing_error(s, NULL, check);
			}
			return (1);
		}
		i++;
	}
	return (0);
}
