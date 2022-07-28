/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_meaning_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:09:25 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/28 15:58:36 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

static int	error_on_parsing(char *meaning, t_p_e_status status)
{
	if (status == OPEN_BRACKET)
		error_handle("unclosed bracket.");
	else if (status == CLOSE_BRACKET)
		parsing_error(NULL, ")", 0);
	else if (status == OPEN_QUOTE)
		error_handle("unclosed quote.");
	else if (status == INCOMPLETE)
		error_handle("incomplete command.");
	else if (status == MAXIMUM_DEPTH)
		error_handle("maximum number of brackets.");
	else
		return (0);
	free(meaning);
	return (1);
}

static void	decide_meaning_quote(char *input, char *meaning, t_q_status *s)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (*s == CLOSED)
		{
			meaning[i] = 1;
			if ((input[i] == '\"' || input[i] == '\'') && \
			(i == 0 || !meaning[i - 1] || input[i - 1] != '\\'))
				*s = (unsigned char)input[i];
		}
		else if (*s == (unsigned char)input[i])
		{
			meaning[i] = 1;
			*s = CLOSED;
		}
		else if (*s == OPEN_D && input[i] == '$')
			meaning[i] = 1;
		else
			meaning[i] = 0;
		i++;
	}
}

static int	decide_meaning_backslash(char *input, char *meaning)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\\' && meaning[i])
		{
			if (i == (int)ft_strlen(input) - 1)
				return (error_on_parsing(meaning, INCOMPLETE));
			else
				meaning[i + 1] = 0;
		}
		i++;
	}
	return (0);
}

static int	decide_meaning_bracket(char *input, char *meaning)
{
	int	i;
	int	depth;

	i = 0;
	depth = 0;
	while (input[i])
	{
		if (input[i] == '(' && meaning[i])
			meaning[i] += depth++;
		else if (input[i] == ')' && meaning[i])
		{
			if (--depth < 0 || input[i - 1] == '(')
				return (error_on_parsing(meaning, CLOSE_BRACKET));
			meaning[i] += depth;
		}
		else if (depth && meaning[i])
			meaning[i] = 1 + depth;
		i++;
		if (depth == 127)
			error_on_parsing(meaning, MAXIMUM_DEPTH);
	}
	return (error_on_parsing(meaning, depth != 0));
}

char	*make_meaning(char *input)
{
	char		*meaning;
	t_q_status	status;

	meaning = ft_strdup(input);
	if (meaning == NULL)
		panic_memory();
	status = CLOSED;
	decide_meaning_quote(input, meaning, &status);
	if (status != CLOSED && error_on_parsing(meaning, OPEN_QUOTE))
		return (NULL);
	if (decide_meaning_backslash(input, meaning))
		return (NULL);
	if (decide_meaning_bracket(input, meaning))
		return (NULL);
	return (meaning);
}
