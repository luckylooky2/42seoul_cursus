/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_expansion_asterisk.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:30:17 by chanhyle          #+#    #+#             */
/*   Updated: 2022/07/28 14:39:03 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	append_to_syntax(t_syntax *s, char *str)
{
	size_t	len;
	char	*new_input;
	char	*new_meaning;

	if (str == NULL)
		panic_memory();
	len = ft_strlen(s->input) + ft_strlen(str) + 1;
	new_input = (char *)malloc(sizeof(char) * (len + 1));
	new_meaning = (char *)malloc(sizeof(char) * len);
	if (new_input == NULL || new_meaning == NULL)
		panic_memory();
	// 기존 input, meaning 복사 => regex까지 포햠?
	ft_strlcpy(new_input, s->input, ft_strlen(s->input) + 1);
	ft_memcpy(new_meaning, s->meaning, ft_strlen(s->input));
	// 공백 추가
	ft_strlcat(new_input + ft_strlen(s->input), " ", 2);
	new_meaning[ft_strlen(s->input)] = 1;
	// 파일 이름 append
	ft_strlcat(new_input + ft_strlen(s->input) + 1, str, ft_strlen(str) + 1);
	ft_memset(new_meaning + ft_strlen(s->input) + 1, 0, ft_strlen(str)); // 0으로 초기화하는 이유는? 문자열 취급?
	free(str);
	free(s->input);
	free(s->meaning);
	s->input = new_input;
	s->meaning = new_meaning;	
}

static int	does_match(char *name_buffer, int name_length, char *regex)
{
	char	*name_str;
	int		result;
	
	// ., .. 의 경우 예외 처리
	if (1 <= name_length && name_buffer[0] == '.')
		return (0);
	name_str = ft_substr(name_buffer, 0, name_length);
	if (name_str == NULL)
		panic_memory();
	// 비교하기 위해 해당 파일 이름, regex를 인자로 보냄
	result = regex_matcher(name_str, regex);
	free(name_str);
	return (result);
}	

static t_syntax	*make_syntax_matching_regex(char *regex)
{
	t_syntax	*s;
	// 디렉토리 파일은 디렉토리에 속하는 파일들의 이름 + inode 번호로 구성 => 논리적 트리 구조
	// 디렉토리 파일에 속하는 파일들은 디렉토리 파일에 dirent 구조체로 관리
	t_dirent	*dir;

	if (get_next_dir(INIT_DIR) == NULL)
		return (NULL);
	s = (t_syntax *)malloc(sizeof(t_syntax));
	if (s == NULL)
		panic_memory();
	s->input = ft_strdup("");
	s->meaning = ft_strdup("");
	if (s->input == NULL || s->meaning == NULL)
		panic_memory();
	while (1)
	{
		dir = get_next_dir(GET_DIR);
		// 현재 dirp의 마지막 dirent까지 다 읽으면 NULL을 반환?
		if (dir == NULL)
			break ;
		// dir->d_name과 regex가 일치하면 append
		if (does_match(dir->d_name, dir->d_namlen, regex))
			append_to_syntax(s, ft_substr(dir->d_name, 0, dir->d_namlen));
	}
	get_next_dir(CLOSE_DIR);
	return (s);
}

static int	fetch_and_replace(t_syntax *s, int i, char *regex, char *start)
{
	// start : *의 위치
	t_syntax	*result_syntax;
	int			retval;

	result_syntax = make_syntax_matching_regex(regex);
	if (result_syntax != NULL && *result_syntax->input)
	{
		// regex 이후의 문자 개수 반환
		retval = ft_strlen(start + ft_strlen(regex));
		// s->input에서 앞으로 옮기기 : regex 삭제
		ft_memmove(start, start + ft_strlen(regex), retval + 1);
		ft_memmove(s->meaning + (start - s->input), s->meaning + (start - s->input) + ft_strlen(regex), retval);
		// append한 result_syntax을 s->input, meaning으로 insert
		insert_syntax(s, result_syntax, start - s->input);
		delete_t_syntax(result_syntax);
		return (retval);
	}
	if (result_syntax != NULL)
		delete_t_syntax(result_syntax);
	return (1);
}

// i = 0
void	expand_asterisk(t_syntax *s, int i)
{
	// * 문자가 있는 위치
	char	*start;
	char	*end;
	char	*regex;

	while (s->input[i])
	{
		// * 문자를 발견하면 진행
		if (s->input[i] == '*' && s->meaning[i] == 1)
		{
			start = s->input + i;
			// 의미 있는 공백이 나오기 전까지 start를 앞으로 옮김
			while (s->input < start && *(start - 1) != ' ' && s->meaning[start - s->input - 1] == 1)
				start--;
			end = s->input + i + 1;
			// 의미 있는 공백이 나오기 전까지 end를 뒤로 옮김
			while (*end && &end != ' ' && s->meaning[end - s->input] == 1)
				end++;
			regex = ft_substr(start, 0, end - start);
			if (regex == NULL)
				panic_memory();
			i += fetch_and_replace(s, i, regex, start);
			free(regex);
			// 이어붙인 이후 재귀 호출
			expand_asterisk(s, i);
		}
	}
}