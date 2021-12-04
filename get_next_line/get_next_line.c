/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 20:36:00 by chanhyle          #+#    #+#             */
/*   Updated: 2021/12/04 11:43:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
}

static t_list	*ft_make_linked_list(t_list *char_lst, char *buf)
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
	static char	buf[BUFFER_SIZE];
	static int	index;
	char		*new_str;
	t_list		*char_lst;
	t_list		*curr;
	int			check;
	int			i = 0;

	char_lst = NULL;
	if (fd < 0)
		return (NULL);
	while (1)
	{
		if (index == 0)
		{
			i = 0;
			ft_bzero(buf, BUFFER_SIZE);
			check = read(fd, buf, BUFFER_SIZE);
			if (check == 0)
				return (NULL);
			// printf("read : %d\n", check); 
			// while (i < BUFFER_SIZE)
			// 	printf("read %d : %c\n", i , buf[i++]);
			if (check == -1)
			{
				ft_lstclear(&char_lst, free);
				return (NULL);
			}
		}
		while (index < BUFFER_SIZE)
		{
			// printf("index : %d*%c\n", index, buf[index]);
			char_lst = ft_make_linked_list(char_lst, &buf[index]);
			index++;
			if (buf[index - 1] == '\n' || buf[index - 1] == '\0')
				break ;
		}
		// printf("%d\n", index);
		if (index == BUFFER_SIZE)
		{
			index = 0;
			if (buf[index - 1] != '\n')
				break ;
			// printf("init\n");
		}
		else
			break ;
	}
	curr = char_lst;
	new_str = (char *)malloc(sizeof(char) * (ft_lstsize(curr) + 1));
	if (new_str == NULL)
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
	int	i;
	char	*str;

	i = 0;
	str = "123";
	fd = open("a.txt", O_RDONLY);

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

	// str = get_next_line(fd);
	// printf("%s", str);
	// str = get_next_line(fd);
	// printf("%s", str);
	// str = get_next_line(fd);
	// printf("%s", str);
}

