/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:12:23 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/22 10:51:23 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	index_big;
	size_t	index_little;
	size_t	cnt;

	index_big = 0;
	if (ft_strlen((char *)little) == 0)
		return ((char *)big);
	while (index_big < len && big[index_big])
	{
		if (big[index_big] == *little)
		{
			cnt = 0;
			index_little = 0;
			while (little[index_little] && index_big + index_little < len)
			{
				if (big[index_big + index_little] == little[index_little])
					cnt++;
				index_little++;
			}
			if (ft_strlen((char *)little) == cnt)
				return ((char *)big + index_big);
		}
		index_big++;
	}
	return (NULL);
}
