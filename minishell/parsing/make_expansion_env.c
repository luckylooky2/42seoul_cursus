/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_expansion_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 00:08:20 by chanhyle          #+#    #+#             */
/*   Updated: 2022/07/28 11:34:20 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// value 안에 공백이 존재하면 meaning을 1로 바꿔주는 함수 => 원래는 0으로 memset
// why?
static void	save_meaning_of_space(char *meaning, char *str)
{
	while (*str)
	{
		if (*str == ' ')
			*meaning = 1;
		str++;
		meaning++;
	}
}

static void	do_replace(t_syntax *s, char *str, int i,  char *end)
{
	int		len;
	char	*new_input;
	char	*new_meaning;

	// 원래 문자열 길이 + value 길이 - key 길이
	// i : $ 문자가 나온 index
	len = ft_strlen(s->input) + ft_strlen(str) - (end - s->input - i);
	new_input = (char *)malloc(sizeof(char) * (len + 1));
	new_meaning = (char *)malloc(sizeof(char) * len);
	if (new_input == NULL || new_meaning == NULL)
		panic_memory();
	// input 배열 이어붙이기
	// 1. input 시작부터 dstsize - 1만큼 복사하고, 마지막에 '\0' => $ 전까지 복사
	ft_strlcpy(new_input, s->input, i + 1);
	// 2. value를 new_input의 '\0'를 찾아서 이어 붙임, dstsize - ft_strlen(dst) - 1만큼 복사, 마지막에 '\0'
	ft_strlcat(new_input, str, i + ft_strlen(str) + 1);
	// 3. end 포인터부터 끝까지 이어 붙임, 마지막에 '\0' 추가
	ft_strlcat(new_input, end, i + ft_strlen(str) + ft_strlen(end) + 1);
	// meaning 배열 이어붙이기
	ft_memcpy(new_meaning, s->meaning, i);
	ft_memset(new_meaning + i, 0, ft_strlen(str));
	ft_memcpy(new_meaning + i + ft_strlen(str), s->meaning + (end - s->input), ft_strlen(end));
	save_meaning_of_space(new_meaning + i, str);
	free(s->input);
	free(s->meaning);
	s->input = new_input;
	s->meaning = new_meaning;
}

static char	*fetch_env_wrapper(char **key)
{
	char	*value;

	// 2차원 배열로 들어가지만, env_commands 함수 안에서 알아서 1차원으로 변환
	value = env_commands(GET_ENV, key);
	if (value == NULL)
		value = "$";
	return (ft_strdup(value));
}

static void	fetch_and_replace(t_syntax *s, int *i)
{
	char	*end;
	char	*key;
	char	*value;

	end = s->input + *i + 1; // 일단 ? 뒤로 이동
	// exit_status인 경우
	if (*end == '?')
	{
		key = ft_strdup("");
		value = ft_itoa(global_status(GET_STATUS, 0));
	}
	// 환경 변수인 경우
	else
	{
		while (ft_isalnum(*end) || *end == '_') // 네이밍 규칙 건너뛰기
			end++;
		// input 배열에서 네이밍 규칙이 적용되는 길이까지 자름
		key = ft_substr(s->input + *i, 1, --end - s->input - *i);
		if (key == NULL)
			panic_memory();
		// env_list에서 찾아 return
		value = fetch_env_wrapper(&key);
		if (value == NULL)
			panic_memory();
	}
	// key를 value로 대체
	do_replace(s, value, *i, ++end);
	*i += (int)ft_strlen(value);
	free(key);
	free(value);
}

// i = 0
void	expand_env(t_syntax *s, int i)
{
	// $ 문자 인덱스를 발견하면 진행
	while (s->input[i])
	{
		if (s->input[i] == '$' && s->meaning[i] == 1)
		{
			fetch_and_replace(s, &i);
			expand_env(s, i); // 재귀 호출 => 반복
			return ;
		}
		i++;
	}
	return ;
}