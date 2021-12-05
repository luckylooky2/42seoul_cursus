/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 20:36:00 by chanhyle          #+#    #+#             */
/*   Updated: 2021/12/05 21:06:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static t_list	*ft_make_new_node(t_list *char_lst, char *buf)
{
	char	*new_char;
	t_list	*new_node;

	new_char = (char *)malloc(sizeof(char));
	if (new_char == NULL)
	{
		ft_lstclear(&char_lst, free);
		return (NULL);
	}
	*new_char = *buf;
	new_node = ft_lstnew(new_char);
	if (new_node == NULL)
	{
		ft_lstclear(&char_lst, free);
		return (NULL);
	}
	ft_lstadd_back(&char_lst, new_node);
	return (char_lst);
}

static char	*ft_copy_str(char *new_str, t_list *char_lst)
{
	int		i;
	t_list	*curr;

	i = 0;
	curr = char_lst;
	while (curr)
	{
		new_str[i] = *((char *)((curr)->content));
		curr = (curr)->next;
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char		buf[BUFFER_SIZE];
	static int		index;
	char			*new_str;
	static t_list	*char_lst;
	int				check;
	
	while (fd >= 0)
	{
		if (index == 0)
		{
			ft_bzero(buf, BUFFER_SIZE);
			check = read(fd, buf, BUFFER_SIZE);
		}
		while (index < BUFFER_SIZE && check > 0)
		{
			char_lst = ft_make_new_node(char_lst, &buf[index]);
			index++;
			if (buf[index - 1] == '\n')
				break ;
		}
		if ((index == BUFFER_SIZE || fd == 0) && buf[index - 1] == '\n')
		{
			index = 0;
			break ;
		}
		else if ((index == BUFFER_SIZE || fd == 0) && check > 0) 
			index = 0;
		else 
			break ; 
	}
	new_str = (char *)malloc(sizeof(char) * (ft_lstsize(char_lst) + 1));
	if (new_str == NULL || char_lst == NULL || fd < 0 || check == -1)
	{
		ft_lstclear(&char_lst, free);
		return (NULL);
	}
	new_str = ft_copy_str(new_str, char_lst);
	ft_lstclear(&char_lst, free);
	return (new_str);
}

#include <stdio.h>
#include <fcntl.h>
int main()
{
	int fd;
	char	*str;

	str = "123";
	// fd = open("a.txt", O_RDONLY);
	fd = 0;

	int i = 0;
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		// printf("return : '%s'\n", str);
		printf("%s", str);
		free(str);
		i++;
	}

	// fd = 0;
	// str = get_next_line(fd);
	// printf("%s", str);
	// str = get_next_line(fd);
	// printf("%s", str);
	// str = get_next_line(fd);
	// printf("%s", str);
}

