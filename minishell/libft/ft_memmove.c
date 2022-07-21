/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 00:17:15 by hangokim          #+#    #+#             */
/*   Updated: 2022/03/15 12:12:11 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	void	*to_return;

	to_return = dst;
	if (dst < src)
	{
		while (len)
		{
			*(unsigned char *)dst = *(unsigned char *)src;
			++dst;
			++src;
			--len;
		}
	}
	else if (dst != src && len > 0)
	{
		dst += len;
		src += len;
		while (len)
		{
			*(unsigned char *)--dst = *(unsigned char *)--src;
			--len;
		}
	}
	return (to_return);
}
