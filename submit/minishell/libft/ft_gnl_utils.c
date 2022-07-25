/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:45:40 by hangokim          #+#    #+#             */
/*   Updated: 2022/06/17 15:45:47 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	_memcpy(char *dst, char *src, size_t size)
{
	while (size)
	{
		*dst = *src;
		++dst;
		++src;
		--size;
	}
}

void	_memcpy_with_null(char *dst, char *src, size_t size)
{
	while (size)
	{
		*dst = *src;
		++dst;
		++src;
		--size;
	}
	*dst = 0;
}

int	_memcpy_with_detect(char *dst, char *src, size_t size)
{
	int	cnt;

	cnt = 0;
	while (size)
	{
		if (*src == '\n')
			++cnt;
		*dst = *src;
		++dst;
		++src;
		--size;
	}
	return (cnt);
}
