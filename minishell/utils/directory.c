/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:10:13 by chanhyle          #+#    #+#             */
/*   Updated: 2022/07/28 13:33:49 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// 현재 디렉토리를 연 후, DIR 자료형을 반환하는 함수
static	DIR	*init_dirp(void)
{
	// 디렉토리 포인터
	DIR	*dirp;

	// 현재 디렉토리 열어서 DIR 자료형에 저장
	dirp = opendir(".");
	if (dirp == NULL)
	{
		if (errno == ENOMEM)
			panic_memory();
		else
		{
			error_handle("cannot access current directory.");
			return (NULL);
		}
	}
	return (dirp);
}

t_dirent	*get_next_dir(t_dir_cmd cmd)
{
	// 현재 디렉토리에 관한 내용을 저장하는 DIR 자료형 static 변수
	// 먼저 디렉토리 포인터를 열어야 함?
	// GET_DIR을 통해 그 안에 dirent 구조체에 현재 읽고 있는 파일에 대한 내용을 저장?
	static DIR	*dirp = NULL;
	t_dirent	*dir;

	if (cmd == INIT_DIR)
		dirp = init_dirp();
	else if (cmd == CLOSE_DIR)
	{
		if (dirp != NULL)
			closedir(dirp);
		dirp = NULL;
	}
	else if (cmd == GET_DIR)
	{
		if (dirp != NULL)
		{
			// 하나씩 읽어올 때마다, 다음 파일을 받아오나? (readdir 버퍼에서처럼)
			dir = readdir(dirp);
			if (dir == NULL && (errno == EBADF || errno == EIO || errno == EFAULT))
				error_errno("readdir");
			return (dir);
		}
	}
	return ((t_dirent *)dirp);
}