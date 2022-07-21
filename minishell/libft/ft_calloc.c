/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 00:19:28 by hangokim          #+#    #+#             */
/*   Updated: 2022/03/11 21:06:25 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*alloc;
	size_t	total_size;

	total_size = count * size;
	alloc = malloc(total_size);
	if (alloc != 0)
		alloc = ft_memset(alloc, 0, total_size);
	return (alloc);
}
