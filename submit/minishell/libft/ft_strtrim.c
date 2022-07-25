/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 00:20:44 by hangokim          #+#    #+#             */
/*   Updated: 2022/03/15 11:47:36 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char const	*start;
	char const	*end;

	start = s1;
	end = start + ft_strlen(s1) - 1;
	while (start <= end && ft_strchr(set, *start) != 0)
		++start;
	while (start <= end && ft_strchr(set, *end) != 0)
		--end;
	return (ft_substr(start, 0, end - start + 1));
}
