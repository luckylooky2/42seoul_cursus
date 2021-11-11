/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_strjoin_strtrim.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 21:11:53 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/08 21:11:55 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	int		i;
	int		s_len;

	i = 0;
	s_len = ft_strlen(s);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr || (s_len < start))
		return (0);
	while (i < len)
	{
		if (s_len - start >= 0)
			ptr[i] = s[start];
		else
			break ;
		i++;
		start++;
	}
	ptr[i] = 0;
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		index;

	index = 0;
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ptr)
		return (0);
	while (*s1)
	{
		ptr[index++] = *s1;
		s1++;
	}
	while (*s2)
	{
		ptr[index++] = *s2;
		s2++;
	}
	ptr[index] = 0;
	return (ptr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	int		i;
	int		cnt;

	ptr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!ptr)
		return (0);
	while (*s1)
	{
		i = 0;
		cnt = 0;
		while (set[i])
		{
			if (*s1 != set[i])
				cnt++;
			i++;
		}
		if (i == cnt)
			(*ptr)++ == *s1;
		s1++;
	}
	*ptr = 0;
	return (ptr);
}
