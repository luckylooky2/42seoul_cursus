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

#include "get_next_line_bonus.h"
#include <stdio.h>

static t_list	*make_new_node(t_list *char_lst, char *buf)
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

static int	check_repeat_or_break(char *buf, int index)
{
	if ((buf[index] == '\0' && buf[index - 1] == '\n')
		|| ((buf[index] == '\0') && buf[index - 1] == '\0'))
	{
		ft_memset(buf, 0, BUFFER_SIZE + 1);
		return (1);
	}
	else if (buf[index] == '\0')
	{
		ft_memset(buf, 0, BUFFER_SIZE + 1);
		return (0);
	}
	else
		return (1);
}

static char	*make_new_string(int fd, t_list *char_lst, int read_size)
{
	char	*new_str;
	t_list	*curr;
	int		i;

	i = 0;
	curr = char_lst;
	new_str = (char *)malloc(sizeof(char) * (ft_lstsize(char_lst) + 1));
	if (new_str == NULL || char_lst == NULL
		|| fd < 0 || fd > OPEN_MAX || read_size == -1 || BUFFER_SIZE <= 0)
	{
		ft_lstclear(&char_lst, free);
		free(new_str);
		return (NULL);
	}
	while (curr)
	{
		new_str[i] = *((char *)((curr)->content));
		curr = (curr)->next;
		i++;
	}
	new_str[i] = '\0';
	ft_lstclear(&char_lst, free);
	return (new_str);
}

static int	rearrange_string(char *buf)
{
	int	index;
	int	new_index;

	index = 0;
	new_index = 0;
	while (index < BUFFER_SIZE && buf[index] != '\n' && buf[index] != '\0')
		index++;
	if (buf[index] == '\n')
		index++;
	while (index < BUFFER_SIZE + 1)
	{
		buf[new_index] = buf[index];
		if (buf[index] == '\0')
			break ;
		new_index++;
		index++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*new_str;
	t_list		*char_lst;
	int			index;
	int			read_size;

	char_lst = NULL;
	read_size = 0;
	// printf("fd : %d\n", fd);
	while (0 <= fd && fd <= OPEN_MAX && BUFFER_SIZE > 0)
	{
		index = rearrange_string(buf);
		if (buf[0] == '\0')
			read_size = read(fd, buf, BUFFER_SIZE);
		while (index < BUFFER_SIZE && buf[index] != '\0')
		{
			// printf("index : %d, char : %c\n", index, buf[index]);
			char_lst = make_new_node(char_lst, &buf[index++]);
			if (char_lst == NULL || buf[index - 1] == '\n')
				break ;
		}
		if (check_repeat_or_break(buf, index) == 1)
			break ;
	}
	new_str = make_new_string(fd, char_lst, read_size);
	printf("str : %s\n", new_str);
	return (new_str);
}

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
int main()
{
	char *str = "!23";
	// int fd = open("a.out", O_RDONLY);

	// while (str != NULL)
	// {
	// 	str = get_next_line(fd);
	// 	printf("%s", str);
	// 	free(str);
	// }

	// str = get_next_line(fd);
	// printf("%s", str);
	// free(str);
	// str = get_next_line(fd);
	// printf("%s", str);
	// free(str);
	// str = get_next_line(fd);
	// printf("%s", str);
	// free(str);	

	int fd[4];
	
	fd[0] = open("files/41_with_nl", O_RDWR);
	str = get_next_line(fd[0]);
	printf("%s\n", str);
	if (!strcmp(str, "0123456789012345678901234567890123456789\n"))
		printf("good\n");
	else
		printf("bad\n");

	fd[1] = open("files/42_with_nl", O_RDWR);
	str = get_next_line(fd[1]);
	printf("%s\n", str);
	if (!strcmp(str, "01234567890123456789012345678901234567890\n"))
		printf("good\n");
	else
		printf("bad\n");

	fd[2] = open("files/43_with_nl", O_RDWR);
	str = get_next_line(fd[2]);
	printf("%s\n", str);
	if (!strcmp(str, "012345678901234567890123456789012345678901\n"))
		printf("good\n");
	else
		printf("bad\n");

	// str = get_next_line(fd[0]);
	// printf("%s\n", str);
	// if (!strcmp(str, "0"))
	// 	printf("good\n");
	// else
	// 	printf("bad\n");

	// str = get_next_line(fd[1]);
	// printf("%s\n", str);
	// if (!strcmp(str, "1"))
	// 	printf("good\n");
	// else
	// 	printf("bad\n");	

	// str = get_next_line(fd[2]);
	// printf("%s\n", str);
	// if (!strcmp(str, "2"))
	// 	printf("good\n");
	// else
	// 	printf("bad\n");

}
