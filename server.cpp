#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "project1.hpp"

#define PERMS 0666
#define MAX_BUF_SIZE 32 + 1

int main(int argc, char const *argv[])
{
    int value, fd_cs2 = 0, fd_sc2 = 0;
    char buf[MAX_BUF_SIZE] = {
        0,
    };

    // 이전에 fifo 파일이 있다면 삭제
    mkdir("./tmp", 0777);
    mkdir("./tmp/2020203031", 0777);
    mkfifo("./tmp/2020203031/SC2", 0666);
    mkfifo("./tmp/2020203031/CS2", 0666);

    // fifo 파일을 생성한다.

    fd_sc2 = open("./tmp/2020203031/SC2", O_WRONLY);
    fd_cs2 = open("./tmp/2020203031/CS2", O_RDONLY);

    while (1)
    {
        CS2 *cs2 = (CS2 *)malloc(sizeof(CS2));
        memset(cs2->id, '\0', MAX_SIZE + 1);
        memset(cs2->id2, '\0', MAX_SIZE + 1);
        memset(cs2->name, '\0', MAX_SIZE + 1);
        memset(cs2->pw, '\0', MAX_SIZE + 1);

        Mem *c = (Mem *)malloc(sizeof(Mem));
        memset(c->id, '\0', MAX_SIZE + 1);
        memset(c->name, '\0', MAX_SIZE + 1);
        memset(c->pw, '\0', MAX_SIZE + 1);

        SC2 *sc2 = (SC2 *)malloc(sizeof(SC2));
        sc2->page = 3;
        memset(sc2->problem, '\0', MAX_SIZE + 1);
        memset(sc2->check, '\0', MAX_SIZE + 1);
        memset(sc2->id, '\0', MAX_SIZE + 1);
        memset(sc2->name, '\0', MAX_SIZE + 1);

        if ((value = read(fd_cs2, (CS2 *)cs2, sizeof(CS2))) > 0)
        {
            if (cs2->page == 1)
            {
                printf("<%s> try ro sign up ...", cs2->id);
                // sc2->page=1;
                std::string file = "./";
                file += cs2->id;
                file += ".dat";
                // strcpy(sc2->check,"ID Alread exsisted");
                // write(fd_sc2,(SC2*)sc2,sizeof(CS2));
                // std::string file = "./";
                // file+=cs2->id;
                // file+=".dat";
                int fd = open(file.c_str(), O_RDONLY, 0755);
                if (fd != -1)
                {
                    printf("denied   %s\n", "ID Alread exsisted");
                    strcpy(sc2->check, "ID Alread exsisted");
                    sc2->page = 1;
                    write(fd_sc2, (SC2 *)sc2, sizeof(SC2));
                    free(sc2);
                }
                else
                {
                    sc2->page = 0;
                    write(fd_sc2, (SC2 *)sc2, sizeof(SC2));
                    printf("success\n");
                    int f = open(file.c_str(), O_CREAT | O_RDWR, 0755);
                    strcpy(c->id,cs2->id);
                    strcpy(c->pw,cs2->pw);
                    strcpy(c->name,cs2->name);
                    write(f, (Mem *)c, sizeof(Mem));
                    close(f);
                    free(sc2);
                }

                // else{
                //     sc2->page=0;
                // }
            }
            else if(cs2->page==0){
                printf("<%s> try to login...", cs2->id);
                std::string file = "./";
                file+=cs2->id;
                file+=".dat";
                int fd = open(file.c_str(), O_RDONLY, 0755);
                if(fd == -1){
                    printf("denied   %s\n","ID doesn't exist");
                    sc2->page=1;
                    strcpy(sc2->check,"ID doesn't exist");
                    write(fd_sc2,(SC2*)sc2,sizeof(SC2));
                }
                else{
                    read(fd,(Mem*)c,sizeof(Mem));
                    if(strcmp(c->pw,cs2->pw)){
                        printf("denied   %s\n","Incorrect Password");
                        sc2->page=1;
                        strcpy(sc2->check,"Incorrect Password");
                        write(fd_sc2,(SC2*)sc2,sizeof(SC2));
                    }else{
                        sc2->page=0;
                        strcpy(sc2->id,c->id);
                        strcpy(sc2->name,c->name);
                        write(fd_sc2,(SC2*)sc2,sizeof(SC2));
                        printf("success\n");
                    }

                }
            }
            else if(cs2->page==2){
                printf("<%s> enter message window...", cs2->id);
                std::string file = "./";
                file+=cs2->id2;
                file+=".dat";
                int fd = open(file.c_str(), O_RDONLY, 0755);
                if(fd == -1){
                    printf("denied   %s\n","ID doesn't exist");
                    sc2->page=1;
                    strcpy(sc2->check,"ID doesn't exist");
                    write(fd_sc2,(SC2*)sc2,sizeof(SC2));
                }
                else{
                    if(!strcmp(cs2->id2,cs2->id)){
                        printf("denied   %s\n","Input error");
                        sc2->page=1;
                        strcpy(sc2->check,"Input error");
                        write(fd_sc2,(SC2*)sc2,sizeof(SC2));
                    }else{
                        sc2->page=0;
                        strcpy(sc2->id,c->id);
                        strcpy(sc2->name,c->name);
                        write(fd_sc2,(SC2*)sc2,sizeof(CS2));
                        printf("success\n");
                    }

                }
            }
        }
    }

    return 0;
}