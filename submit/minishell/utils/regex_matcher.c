/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_matcher.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youhan <youhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:25:47 by hangokim          #+#    #+#             */
/*   Updated: 2022/07/22 19:08:18 by youhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	regex_matcher(char *input, char *regex)
{
	char	*asterisk;

	if (*input == 0)
		return (0);
	else if (ft_strlen(regex) == 1)
		return (*regex == '*' || (ft_strlen(input) == 1 && *input == *regex));
	else if (*regex == '*')
	{
		while (*input)
		{
			if (regex_matcher(input++, regex + 1))
				return (1);
		}
		return (0);
	}
	else
	{
		asterisk = ft_strchr(regex, '*');
		if (asterisk == NULL)
			return (!ft_strncmp(input, regex, ft_strlen(regex) + 1));
		if (ft_strncmp(input, regex, asterisk - regex))
			return (0);
		return (regex_matcher(input + (asterisk - regex), asterisk));
	}
}
