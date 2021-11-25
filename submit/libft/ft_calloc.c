/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:03:32 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/25 17:29:24 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*new_ary;
	size_t	i;

	i = 0;
	new_ary = malloc(nmemb * size);
	if (!new_ary)
		return (NULL);
	else
	{
		while (i < nmemb * size)
			((unsigned char *)new_ary)[i++] = 0;
		return (new_ary);
	}
}
