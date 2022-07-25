/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 00:16:31 by hangokim          #+#    #+#             */
/*   Updated: 2022/03/15 10:55:17 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	void	*to_return;

	to_return = b;
	while (len)
	{
		*(unsigned char *)b = (unsigned char)c;
		++b;
		--len;
	}
	return (to_return);
}
