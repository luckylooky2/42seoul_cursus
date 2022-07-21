/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 00:23:03 by hangokim          #+#    #+#             */
/*   Updated: 2022/03/12 18:05:09 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	index;
	size_t	s_len;

	s_len = ft_strlen(s);
	index = 0;
	while (index < s_len)
	{
		f(index, &s[index]);
		++index;
	}
}
