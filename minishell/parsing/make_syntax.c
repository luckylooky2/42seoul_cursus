/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_syntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:09:18 by chanhyle          #+#    #+#             */
/*   Updated: 2022/07/27 16:55:25 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	there_are_only_space(char *input, int len)
{
	while (len-- && *input == ' ')
		input++;
	return (len == -1 || *input == 0);
}

// semicolon이 처음으로 나오거나 "		;"과 같은 case를 찾아내는 함수
static	check_before_slice(t_syntax *s, int i, int length, t_delimiter d)
{
	// t_delimiter : delimiter를 나타내는 enum
	if (d == SEMICOLON)
	{
		if (i == 0)
			return (0);
		return (length == 0 && i < (int)ft_strlen(s->input)); // semicolon으로 시작하는 input 1 return
	}
	return (length == 0 || (there_are_only_space(s->input + i, length) && \
	length != (int)ft_strlen(s->input))); // semicolon 앞에 공백밖에 없는 경우 1 return
}

t_syntax	*slice_syntax(t_syntax *s, int i, int length, t_delimiter delimiter)
{
	t_syntax	*syntax;

	if (check_before_slice(s, i, length, delimiter))
	{
		// default : P_ERROR(0), delimiter를 P_ERROR로 설정 => 에러 처리
		if (global_status(GET_P_ERROR, 0) != PRINTED)
			global_status(SET_P_ERROR, delimiter);
		return (NULL);
	}
	if (length == 0)
		return (NULL);
	syntax = malloc(sizeof(t_syntax));
	if (syntax == NULL)
		panic_memory();
	syntax->input = (char *)malloc(sizeof(char) * (length + 1));
	if (syntax->input == NULL)
		panic_memory();
	syntax->meaning = (char *)malloc(sizeof(char) * length);
	if (syntax->meaning == NULL)
		panic_memory();
	// 문자열은 ft_strlcpy()를 이용
	ft_strlcpy(syntax->input, s->input + i, length + 1);
	// 문자 배열은 ft_memcpy()를 이용
	ft_memcpy(syntax->meaning, s->meaning + i, length);
	return (syntax);
}

t_syntax	*syntax_from_input(char *input, char *meaning);
{
	t_syntax	*syntax;

	if (meaning == NULL)
		return (NULL);
	syntax = (t_syntax *)malloc(sizeof(t_syntax));
	if (syntax == NULL)
		panic_memory();
	syntax->input = ft_strdup(input);
	syntax->meaning = meaning;
	return (syntax);
}