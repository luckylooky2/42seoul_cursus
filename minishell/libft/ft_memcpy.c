/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 00:17:03 by hangokim          #+#    #+#             */
/*   Updated: 2022/03/19 21:02:29 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*to_return;

	if (dst == src)
		return (dst);
	to_return = dst;
	while (n)
	{
		*(unsigned char *)dst = *(unsigned char *)src;
		++dst;
		++src;
		--n;
	}
	return (to_return);
}
