/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hangokim <hangokim@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:42:21 by hangokim          #+#    #+#             */
/*   Updated: 2022/06/17 15:42:27 by hangokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_gnl(int fd)
{
	static t_contents	contents[OPEN_MAX];
	int					check;
	int					bytes_to_read;

	if (fd < 0 || OPEN_MAX <= fd || BUFFER_SIZE <= 0)
		return (0);
	if (BUFFER_SIZE < 4096)
		bytes_to_read = BUFFER_SIZE;
	else
		bytes_to_read = 4096;
	while (1)
	{
		if (contents[fd].nl_cnt)
			return (with_wrapper(flush_content(contents + fd), contents + fd));
		check = fill_content(contents + fd, fd, bytes_to_read);
		if (check == -1)
			return (0);
		else if (check == 0)
			return (with_wrapper(flush_content(contents + fd), contents + fd));
	}
}

int	fill_content(t_contents *content, int fd, int bytes_to_read)
{
	char		*buf;
	char		*new_line;
	int			cnt;
	int			new_line_cnt;

	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (buf == 0)
		return (-1);
	cnt = read(fd, buf, bytes_to_read);
	if (cnt == 0 || cnt == -1)
		return (with_free(cnt, buf));
	new_line_cnt = content->line_cnt + content->buf_cnt;
	new_line = (char *)malloc(sizeof(char) * (new_line_cnt + 1));
	if (new_line == 0)
		return (with_free(-1, buf));
	if (content->line)
		_memcpy(new_line, content->line, content->line_cnt);
	_memcpy(new_line + content->line_cnt, content->buf, content->buf_cnt);
	if (content->line)
		free(content->line);
	content->line = new_line;
	content->line_cnt = new_line_cnt;
	content->buf_cnt = cnt;
	content->nl_cnt += _memcpy_with_detect(content->buf, buf, cnt);
	return (with_free(1, buf));
}

char	*flush_content(t_contents *content)
{
	char	*str;
	int		len;
	int		new_buf_cnt;

	if (content->buf_cnt == 0)
		return (0);
	len = 1;
	while (content->buf[len - 1] != '\n' && len < content->buf_cnt)
		++len;
	new_buf_cnt = content->buf_cnt - len;
	str = (char *)malloc(sizeof(char) * (content->line_cnt + len + 1));
	if (str == 0)
		return (0);
	_memcpy(str, content->line, content->line_cnt);
	_memcpy_with_null(str + content->line_cnt, content->buf, len);
	_memcpy(content->buf, content->buf + len, new_buf_cnt);
	if (content->line)
		free(content->line);
	content->line = 0;
	content->line_cnt = 0;
	content->buf_cnt = new_buf_cnt;
	--content->nl_cnt;
	return (str);
}

char	*with_wrapper(char *line, t_contents *content)
{
	if (content->line)
		free(content->line);
	return (line);
}

int	with_free(int val, char *buf)
{
	if (buf)
		free(buf);
	return (val);
}
