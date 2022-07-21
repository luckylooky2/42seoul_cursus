/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 00:19:00 by hangokim          #+#    #+#             */
/*   Updated: 2022/03/15 12:51:54 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	ndl_len;

	if (*needle == 0)
		return ((char *)haystack);
	if (len == 0)
		return (0);
	ndl_len = ft_strlen(needle);
	while (*haystack && ndl_len <= len)
	{
		if (*haystack == *needle && ft_strncmp(haystack, needle, ndl_len) == 0)
			return ((char *)haystack);
		++haystack;
		--len;
	}
	return (0);
}
