/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:13:27 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/16 12:13:37 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
