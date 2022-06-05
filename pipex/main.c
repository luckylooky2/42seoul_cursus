/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhyle <chanhyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 01:02:32 by chanhyle          #+#    #+#             */
/*   Updated: 2022/06/05 14:31:50 by chanhyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv, char **envp)
{
    pid_t pid;
    pid_t pid2;
    pid_t pid3;
    int status;
    int fd[2];
    int fd1[2];
    char **a;
    char **b;
    int fd12;

    // inputdata_check(argc, argv, &data);
    fd12 = open("file2", O_RDWR | O_CREAT, 0644);
    pipe(fd);
    // printf("fd[0] : %d, fd[1] : %d\n", fd[0], fd[1]);
    // pipe(fd1);
    pid = fork();
    if (pid != 0)
        pid2 = fork();
    if (pid == 0) // fd[0] = 4 fd[1] = 6                 pipe파일생성 fd[0] = 파일에서 읽는다 fd[1] = 파일에다 쓴다.
    {
        wait();
    }
    else if (pid2 == 0)
    {
        // char **c;
        // dup2(fd1[0], 0);
        // close(fd1[1]);
        // c = (char **)malloc(sizeof(char *) * 3);
        // c[0] = "wc";
        // c[1] = NULL;
        // if (execve("/usr/bin/wc",c, NULL) == -1)
        //     printf("error");
        dup2(fd[1], 1); // 4과 1 연결, (3, 1), (4, 0)을 연결하려고 하면 bad fd 오류 발생
        close(fd[0]); // 부모 프로세스의 3번을 닫으면 문제가 없는데, 자식 프로세스의 4번을 안 닫으면 문제가 생김
        // write(fd[0], "hello\n", 6); // 3번에 출력 -> 출력 안 됨. 어디로?
        // write(1, "hello\n", 6); // dup2에 의해 4번에 출력
        a = (char **)malloc(sizeof(char *) * 3);
        a[0] = "cat";
        a[1] = "file1";
        a[2] = NULL;
        if (execve("/bin/cat", a, NULL) == -1)
            printf("no cat\n");
    }
    else
    {
        dup2(fd[0], 0); // 3과 0 연결
        write(fd[1], "world\n", 6); // pipe를 통해서 자식 프로세스의 입력으로 들어감
        close(fd[1]); // 닫아주지 않으면 입력이 2개? 부모 프로세스는 꺼지고, 자식 프로세스만 백그라운드에서 돌아감
        // write(fd[0], "world\n", 6);
        dup2(fd12, 1); // write할 파일(file2, fd12)의 fd와 1 연결
        // dup2(fd1[1], 1);
        // close(fd1[0]);
        b = (char **)malloc(sizeof(char *) * 3);
        b[0] = "wc";
        b[1] = "-l";
        b[2] = NULL;
        execve("/usr/bin/wc", b, NULL);
        write(fd[0], "asd\n", 3);
    }
}
