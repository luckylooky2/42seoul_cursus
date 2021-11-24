/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:12:33 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/19 11:16:02 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_return(char *dest, size_t size)
{
	size_t	i;

	i = 0;
	while (dest[i])
	{
		if (i >= size)
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen((char *)src);
	if (size == 0 || (ft_check_return(dest, size) == 1))
		return (size + src_len);
	dest_len = ft_strlen(dest);
	while ((dest_len + 1 + i < size) && src[i])
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	if (size != 0)
		dest[dest_len + i] = 0;
	if (size <= dest_len)
		return (size + src_len);
	else
		return (dest_len + src_len);
}
