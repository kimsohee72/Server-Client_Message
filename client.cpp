#include <fcntl.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include "project1.hpp"


#define PERMS 0600

int main(int argc, char const *argv[])
{
    int num = 0;
    int value, fd_cs2=0,fd_sc2=0;


    // 이전에 fifo 파일이 있다면 삭제
    mkdir("./tmp",0777);
    mkdir("./tmp/2020203031",0777);

    // fifo 파일을 생성한다.
//    mkfifo("/tmp/2020203031/SC2", 0666);
//     mkfifo("/tmp/2020203031/CS2", 0666);

    // fifo 파일을 생성한다.

    fd_sc2 = open("./tmp/2020203031/SC2", O_RDONLY);
    fd_cs2 = open("./tmp/2020203031/CS2", O_WRONLY);
    
    firstPage(fd_cs2,fd_sc2);
    //fd = open("./tmp/2020203031/C2S", O_WRONLY);
    
    // dup2(fd, STDOUT_FILENO);

    // while (1)
    // {
    //     num = rand() % 10;
    //     printf("[%d] %d\n", getpid(), num);
    //     fflush(stdout);

    //     if (num == 5)
    //     {
    //         break;
    //     }
    //     else
    //     {
    //         sleep(1);
    //     }
    // }
    // close(fd);
    return 0;
}
