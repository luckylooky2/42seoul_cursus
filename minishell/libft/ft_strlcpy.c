/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 00:17:25 by hangokim          #+#    #+#             */
/*   Updated: 2022/03/15 12:21:19 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	to_return;

	to_return = ft_strlen(src);
	if (dstsize > 0)
	{
		--dstsize;
		while (dstsize && *src)
		{
			*dst = *src;
			++dst;
			++src;
			--dstsize;
		}
		*dst = 0;
	}
	return (to_return);
}
