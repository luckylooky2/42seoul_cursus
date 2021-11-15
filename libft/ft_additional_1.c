/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_additional_1.c                                  :+:      :+:    :+:   */
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
	char			*ptr;
	size_t			i;
	unsigned int	s_len;

	i = 0;
	s_len = ft_strlen(s);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (0);
	while (i < len)
	{
		if (s_len > start)
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
	int		i;

	index = 0;
	i = 0;
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ptr)
		return (0);
	while (s1[i])
	{
		ptr[index++] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		ptr[index++] = s2[i];
		i++;
	}
	ptr[index] = 0;
	return (ptr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	int		ptr_index;
	int		set_index;
	int		cnt;

	ptr_index = 0;
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!ptr)
		return (0);
	while (*s1)
	{
		set_index = 0;
		cnt = 0;
		while (set[set_index])
		{
			if (*s1 != set[set_index])
				cnt++;
			set_index++;
		}
		if (set_index == cnt)
			ptr[ptr_index++] = *s1;
		s1++;
	}
	ptr[ptr_index] = 0;
	return (ptr);
}
