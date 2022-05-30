/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 01:02:32 by chanhyle          #+#    #+#             */
/*   Updated: 2022/05/31 01:04:27 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv, char **envp)
{
    pid_t   pid;
    pid_t   pid2;
    int status;
    int fd[2];
    int fd1[2];
    char **a;
    char **b;
    int fd12;
	
    // inputdata_check(argc, argv, &data);
    fd12 = open("file2", O_WRONLY);
    pipe(fd);
    pipe(fd1);
    pid = fork();
    if (pid != 0)
        pid2 = fork();
    if(pid == 0)                    // fd[0] = 4 fd[1] = 6                 pipe파일생성 fd[0] = 파일에서 읽는다 fd[1] = 파일에다 쓴다.
    {
        dup2(fd[0], 0);
        close(fd[1]);
        dup2(fd12, 1);
        // dup2(fd1[1], 1);
        // close(fd1[0]);
        b = (char **)malloc(sizeof(char *) * 3);
        b[0] = "wc";
        b[1] = NULL;
        execve("/usr/bin/wc",b, NULL);
    }
    // else if (pid2 == 0)
    // {
    //  char **c;
    //  dup2(fd1[0], 0);
    //  close(fd1[1]);
    //  c = (char **)malloc(sizeof(char *) * 3);
    //  c[0] = "wc";
    //  c[1] = NULL;
    //  if (execve("/usr/bin/wc",c, NULL) == -1)
    //      printf("error");
    // }
    else
    {
        dup2(fd[1], 1);
        close(fd[0]);
        a = (char **)malloc(sizeof(char *) * 3);
        a[0] = "cat";
        a[1] = "file1";
        a[2] = NULL;
        if (execve("/bin/cat",a, NULL) == -1)
            printf("no cat\n");
    }
}
