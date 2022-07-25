/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 00:20:11 by hangokim          #+#    #+#             */
/*   Updated: 2022/03/15 11:50:13 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	substr_len;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (s_len <= start)
		substr_len = 0;
	else
		substr_len = ft_strlen(s + start);
	if (substr_len > len)
		substr_len = len;
	substr = (char *)malloc(sizeof(char) * (substr_len + 1));
	if (substr == 0)
		return (0);
	ft_strlcpy(substr, s + start, substr_len + 1);
	return (substr);
}
