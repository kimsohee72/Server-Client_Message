#include <fcntl.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void mainPage();
int mainwindow(WINDOW *win1,WINDOW *win2,char* id, char*id2);
void updownPage(char key, int k, std::string l,int fd_cs2,int fd_sc2);
void printPage();
void loginPage(int x, int y, int a, char b, WINDOW *c, WINDOW *d, char *e,
               char *f,int fd_cs2,int fd_sc2
            );
void signupPage(int x, int z, int y, int a, char b, WINDOW *c, WINDOW *d,
                char *e, char *f, char *g,int fd_cs2,int fd_sc2
            );
void printPage(int n, int p, char c, char *a, char *b, WINDOW *k, WINDOW *v,
               std::string *s,int fd_cs2,int fd_sc2,int x,char *id2
            );
int firstPage(int fd_cs2,int fd_sc2);

#define MAX_SIZE 512

struct Mem {
    char name[MAX_SIZE + 1];
    char id[MAX_SIZE + 1];
    char pw[MAX_SIZE + 1];
    int count;
    char arr[MAX_SIZE][MAX_SIZE + 1];
};

struct CS2 {
    int page;
    char id[MAX_SIZE + 1];
    char id2[MAX_SIZE + 1];
    char name[MAX_SIZE + 1];
    char pw[MAX_SIZE + 1];
};
struct SC2 {
    int page;
    char check[MAX_SIZE + 1];
    char id[MAX_SIZE + 1];
    char problem[MAX_SIZE + 1];
    char name[MAX_SIZE + 1];

};


