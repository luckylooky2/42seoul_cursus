/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_meaning.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:11:07 by chanhyle          #+#    #+#             */
/*   Updated: 2022/07/27 16:14:42 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// t_p_e_status : 파싱 에러 종류를 나타내는 enum
static int	error_on_parsing(char *meaning, t_p_e_status status)
{
	if (status == OPEN_BRACKET)
		error_handle("unclosed bracket.");
	else if (status == CLOSE_BRACKET)
		error_handle("parse error near `)'");
	else if (status == OPEN_QUOTE)
		error_handle("unclosed quote.");
	else if (status == INCOMPLETE)
		error_handle("incomplete command.");
	else if (status == NO_COMMAND)
		error_handle("no command inside brackets.");
	else if (status == MAXIMUM_DEPTH)
		error_handle("maximum number of brackets.");
	else
		return (0); // 에러가 아닐 경우 그냥 return
	free(meaning); // 에러일 경우 free() 후 return
	return (1);
}

static int	decide_meaning_quote(char *input, char *meaning, t_q_status *s)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (*s == CLOSED)
		{
			meaning[i] = 1; // 의미가 있음
			// 유효한 " or '가 나오면 34(") or 39(')로 변경
			if ((input[i] == '\"' || input[i] == '\'') && \
			(i = 0 || !meaning[i - 1] || input[i - 1] != '\\'))
				*s = (unsigned char)input[i]; // char로 판단
		}
		else if (*s == (unsigned char)input[i]) // 저장해 놓은 char와 같은 char가 나올 떄
		{
			meaning[i] = 1;
			*s = CLOSED;
		}
		else if (*s = OPEN_D && input[i] == '$') // " 안에 $ 가 나올 떄
			meaning = 1;
		else
			meaning = 0;
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
			if (i == (int)ft_strlen(input) - 1) // input의 끝이면
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
	int	depth; // subshell의 depth

	i = 0;
	depth = 0;
	while (input[i])
	{
		if (input[i] == '(' && meaning[i])
			meaning[i] += depth++; // 앞 괄호는 앞의 depth와 일치
		else if (input[i] == ')' && meaning[i])
		{
			if (--depth < 0) // )
				return (error_on_parsing(meaning, CLOSE_BRACKET));
			if (input[i - 1] == '(') // ()
				return (error_on_parsing(meaning, NO_COMMAND));
			meaning[i] += depth; // 뒤 괄호는 증가된 depth
		}
		else if (depth)
			meaning[i] = 1 + depth; // 괄호 안에 있는 내용은 depth를 더한 값
		i++;
		if (depth == 127)
			error_on_parsing(meaning, MAXIMUM_DEPTH); // ( 가 127개
	}
	// 끝까지 돌았을 때, depth가 0이 아니면 닫히지 않은 것 => OPEN_BRACKET
	return (error_on_parsing(meaning, depth != 0));
}

char	*make_meaning(char *input)
{
	char		*meaning;
	// 따옴표가 열렸는지 닫혔는지를 나타내는 enum
	t_q_status	status;

	meaning = ft_strdup(input);
	if (meaning == NULL)
		panic_memory();
	status = CLOSED;
	// ", ', \, (, )와 에러를 판단하면서 meaning의 값을 할당
	decide_meaning_quote(input, meaning, &status);
	if (status != CLOSED && error_on_parsing(meaning, OPEN_QUOTE))
		return (NULL);
	if (decide_meaning_backslack(input, meaning))
		return (NULL);
	if (decide_meaning_bracket(input, meaning))
		return (NULL);
	// 1과 0으로 의미 유무를 판단하는 meaning 배열 return
	return (meaning);
}