/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 20:36:00 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/28 23:52:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

char	*get_next_line(int fd)
{
	size_t	check;
	char	buf;
	char	*new_ary;

	i = 0;
	while (1)
	{
		check = read(fd, &buf, 1);
		if (check != 0)
		{
			
		}
		else
			break ;
	}
	return (new_ary);
}

int main()
{
	int fd;
	int	i;

	i = 0;
	fd = open("a.txt", O_RDONLY);
	while (i < 1)
	{
		get_next_line(fd);
		i++;
	}
}