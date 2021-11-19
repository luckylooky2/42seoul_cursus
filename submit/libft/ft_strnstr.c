/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:12:23 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/19 11:16:21 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	cnt;

	i = 0;
	if (ft_strlen((char *)little) == 0)
		return ((char *)big);
	while (i < len && big[i])
	{
		if (big[i] == *little)
		{
			cnt = 0;
			j = 0;
			while (little[j] && i + j <= len)
			{
				if (big[i + j] == little[j])
					cnt++;
				j++;
			}
			if (ft_strlen((char *)little) == cnt)
				return ((char *)big + i);
		}
		i++;
	}
	return (0);
}
