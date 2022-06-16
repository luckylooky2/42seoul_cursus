/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:39:06 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/16 11:44:01 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philosophers.h"

size_t	ft_atoull(const char *nptr)
{
	int			i;
	size_t		longlong;

	i = 0;
	longlong = 0;
	if (!nptr)
		return (0);
	while ((9 <= nptr[i] && nptr[i] <= 13) || nptr[i] == 32) //18,446,744,073,709,551,615
		i++;
	if (nptr[i] == '+')
		i++;
	while (nptr[i] == '0')
		i++;
	while ('0' <= nptr[i] && nptr[i] <= '9')
	{
		longlong = longlong * 10 + (nptr[i] - '0');
		if ((longlong == SIZE_T_MAX / 10) && nptr[i + 1] > ('0' + SIZE_T_MAX % 10 - 1)) // 1844674407370955161
			return (SIZE_T_MAX);
		else if (longlong > SIZE_T_MAX / 10 && ('0' <= nptr[i + 1] && nptr[i + 1] <= '9')) // 1844674407370955162
			return (SIZE_T_MAX);
		i++;
	}
	return (longlong);
}

long long	ft_atoll(const char *nptr)
{
	int			i;
	int			sign;
	long long	longlong;

	i = 0;
	sign = 1;
	longlong = 0;
	if (!nptr)
		return (0);
	while ((9 <= *nptr && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while ('0' <= nptr[i] && nptr[i] <= '9')
		longlong = longlong * 10 + (nptr[i++] - '0');
	if (sign == -1)
		longlong *= -1;
	return (longlong);
}

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

size_t	ft_strlen(const char *s)
{
	size_t	cnt;

	cnt = 0;
	if (s == NULL)
		return (0);
	while (s[cnt])
		cnt++;
	return (cnt);
}
