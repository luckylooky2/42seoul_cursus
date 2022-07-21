/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 00:22:43 by hangokim          #+#    #+#             */
/*   Updated: 2022/03/12 18:01:12 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	index;
	size_t	s_len;

	s_len = ft_strlen(s);
	str = (char *)malloc(s_len + 1);
	if (str == 0)
		return (0);
	index = 0;
	while (index < s_len)
	{
		str[index] = f(index, s[index]);
		++index;
	}
	str[index] = 0;
	return (str);
}
