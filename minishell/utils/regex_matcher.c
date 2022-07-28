/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_matcher.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:45:04 by chanhyle          #+#    #+#             */
/*   Updated: 2022/07/28 14:12:26 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// 일치하는 파일이 있으면 1, 아니면 0을 return
int	regex_matcher(char *input, char *regex)
{
	char	*asterisk;

	// 디렉토리가 빈 문자열 => 0
	if (*input == 0)
		return (0);
	// regex가 "*"이면 무조건 1 return
	// *가 아니어도 input과 똑같으면 1, 다르다면 0 return : 맨 마지막에 *가 나오는 것을 고려(재귀 호출)
	else if (ft_strlen(regex) == 1)
		return (*regex == '*' || (ft_strlen(input) == 1 && *input == *regex));
	// regex가 *인 경우
	else if (*regex == '*')
	{
		while (*input)
		{
			// 다음 문자 확인 : 1이면 return 1, 0이면 return 0
			// 필요없는 문자는 넘기는 과정 e.g., *e => Makefile : e이외의 모든 문자는 불필요
			if (regex_matcher(input++, regex + 1))
				return (1);
		}
		return (0);
	}
	// regex가 *가 아닌 경우(일반 문자) : * 앞에 문자가 나온 경우
	else
	{
		asterisk = ft_strchr(regex, '*');
		// regex에 *가 없는데, 똑같은 경우 1 return
		if (asterisk == NULL)
			return (!ft_strncmp(input, regex, ft_strlen(regex) + 1));
		// asterisk까지 다르면 0 return
		if (ft_strncmp(input, regex, asterisk - regex))
			return (0);
		// asterisk 뒤부터 다시 재귀 호출
		return (regex_matcher(input + (asterisk - regex), asterisk));
	}
}