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
	void	*new_str;
	size_t	i;

	i = 0;
	new_str = malloc(nmemb * size);
	if (!new_str)
		return (NULL);
	else
	{
		while (i < nmemb * size)
			((unsigned char *)new_str)[i++] = 0;
		return (new_str);
	}
}
