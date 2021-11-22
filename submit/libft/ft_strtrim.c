/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:09:01 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/19 15:09:40 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_check_front(char const *s1, char const *set)
{
	int	index;
	int	set_index;
	int	cnt;

	index = 0;
	while (s1[index])
	{
		cnt = 0;
		set_index = 0;
		while (set[set_index])
		{
			if (s1[index] != set[set_index])
				cnt++;
			set_index++;
		}
		if (cnt == set_index)
			return ((char *)s1 + index);
		else
			index++;
	}
	return ((char *)s1 + index);
}

static char	*ft_check_back(char const *s1, char const *set)
{
	int	index;
	int	set_index;
	int	cnt;

	index = ft_strlen((char *)s1) - 1;
	if (index == -1)
		return ((char *)s1);
	while (index >= 0)
	{
		cnt = 0;
		set_index = 0;
		while (set[set_index])
		{
			if (s1[index] != set[set_index])
				cnt++;
			set_index++;
		}
		if (cnt == set_index)
			return ((char *)s1 + index);
		else
			index--;
	}
	if (index == -1)
		index = 0;
	return ((char *)s1 + index);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s1_front;
	char	*s1_back;
	char	*ptr;
	int		i;

	i = 0;
	s1_front = ft_check_front(s1, set);
	s1_back = ft_check_back(s1, set);
	if (s1_front > s1_back)
		s1_front = s1_back;
	ptr = (char *)malloc(sizeof(char) * (s1_back - s1_front + 2));
	if (!ptr)
		return (0);
	while (s1_front != s1_back)
	{
		ptr[i] = *(s1_front);
		i++;
		s1_front++;
	}
	ptr[i] = *(s1_front);
	if (i != 0)
		ptr[i + 1] = 0;
	return (ptr);
}
