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

static char	*copy_str(char *new_str, t_list *char_lst)
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

static char	*make_new_str(int fd, t_list *char_lst, int read_byte)
{
	char	*new_str;
	t_list	*curr;
	int		lst_len;

	lst_len = 0;
	curr = char_lst;
	while (curr)
	{
		curr = curr->next;
		lst_len++;
	}
	new_str = (char *)malloc(sizeof(char) * (lst_len + 1));
	if (new_str == NULL || char_lst == NULL
		|| fd < 0 || fd > OPEN_MAX || read_byte == -1 || BUFFER_SIZE <= 0)
	{
		ft_lstclear(&char_lst, free);
		free(new_str);
		return (NULL);
	}
	new_str = copy_str(new_str, char_lst);
	ft_lstclear(&char_lst, free);
	return (new_str);
}

static int	check_index_n_break(char *buf, int *index, int read_byte)
{
	if ((*index == BUFFER_SIZE) && buf[*index - 1] == '\n')
	{
		*index = 0;
		return (1);
	}
	else if ((*index == BUFFER_SIZE) && read_byte > 0)
	{
		*index = 0;
		return (0);
	}
	else
		return (1);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	static int	index;
	char		*new_str;
	t_list		*char_lst;
	int			read_byte;

	char_lst = NULL;
	while (0 <= fd && fd <= OPEN_MAX && BUFFER_SIZE > 0)
	{
		if (index == 0)
		{
			ft_bzero(buf, BUFFER_SIZE);
			read_byte = read(fd, buf, BUFFER_SIZE);
		}
		while (index < BUFFER_SIZE && read_byte > 0 && buf[index] != '\0')
		{
			char_lst = make_new_node(char_lst, &buf[index++]);
			if (buf[index - 1] == '\n')
				break ;
		}
		if (check_index_n_break(buf, &index, read_byte) == 1)
			break ;
	}
	new_str = make_new_str(fd, char_lst, read_byte);
	return (new_str);
}
