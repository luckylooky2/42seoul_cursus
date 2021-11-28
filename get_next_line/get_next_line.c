/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 20:36:00 by chanhyle          #+#    #+#             */
/*   Updated: 2021/11/29 01:36:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*new_ary;
	int		i;
	int		check;
	char	buf;
	t_list	**lst;


	i = 0;
	*lst = NULL;
	while (buf != '\n' && check != 0)
	{
		buf = '\0';
		check = read(fd, &buf, 1);
		if (check != 0)
			ft_lstadd_back(lst, ft_lstnew(&buf));
	}
	while (*lst)
	{
		printf("%c", *((char *)((*lst)->content)));
		*lst = (*lst)->next;
	}
	// new_ary = (char *)malloc(5);
	// printf("%p", new_ary);
	// if (new_ary == NULL)
	// 	return (NULL);
	// while (*lst)
	// {
	// 	new_ary[i++] = *((char *)((*lst)->content));
	// 	*lst = (*lst)->next;
	// }
	// new_ary[i] = '\0';
	return (NULL);
}

int main()
{
	int fd;
	int	i;

	i = 0;
	fd = open("a.txt", O_RDONLY);

	get_next_line(fd);

}