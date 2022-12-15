#include <fcntl.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "project1.hpp"

void mainPage()
{
    WINDOW *win1 = newwin(18, 80, 0, 0);
    WINDOW *win2 = newwin(6, 80, 18, 0);
    wbkgd(win1, COLOR_PAIR(1));
    wbkgd(win2, COLOR_PAIR(2));
    mvwprintw(win1, 6, 34, "> Login");
    mvwprintw(win1, 8, 34, "  Sign Up");
    wrefresh(win1);
    wrefresh(win2);
}

void updownPage(char key, int k, std::string l, int fd_cs2, int fd_sc2)
{
    WINDOW *win1 = newwin(18, 80, 0, 0);
    WINDOW *win2 = newwin(6, 80, 18, 0);
    wbkgd(win1, COLOR_PAIR(1));
    wbkgd(win2, COLOR_PAIR(2));
    wrefresh(win1);
    wrefresh(win2);
    if (key == 3)
    { // 위로 버튼 입력시
        k = 1;
    }
    else if (key == 2)
    { // 아래로 버튼 입력시
        k = 2;
    }
    else if (key == 10)
    { // 엔터 입력시
        if (k == 1)
        { // login 선택
            WINDOW *win1 = newwin(18, 80, 0, 0);
            WINDOW *win2 = newwin(6, 80, 18, 0);
            wbkgd(win1, COLOR_PAIR(1));
            wbkgd(win2, COLOR_PAIR(2));
            // 로그인 화면 구현
            mvwprintw(win1, 4, 34, "ID: ");
            mvwprintw(win1, 6, 34, "PW: ");
            mvwprintw(win1, 9, 35, "  Login");
            wrefresh(win1);
            mvwprintw(win2, 0, 35, "%s", l.c_str());
            wrefresh(win2);
            // 빈 배열 생성
            char id[10] = "";
            char pw[10] = "";
            loginPage(0, 0, 0, 3, win1, win2, id, pw, fd_cs2, fd_sc2); // 로그인
        }
        else
        { // signup 선택
            WINDOW *win1 = newwin(18, 80, 0, 0);
            WINDOW *win2 = newwin(6, 80, 18, 0);
            wbkgd(win1, COLOR_PAIR(1));
            wbkgd(win2, COLOR_PAIR(2));
            // signup 화면 구현
            mvwprintw(win1, 4, 32, "NAME: ");
            mvwprintw(win1, 6, 34, "ID: ");
            mvwprintw(win1, 8, 34, "PW: ");
            mvwprintw(win1, 12, 35, "  Sign Up");
            wrefresh(win1);
            mvwprintw(win2, 0, 35, "%s", l.c_str());
            wrefresh(win2);
            // 빈 배열 생성
            char name[10] = "";
            char id[10] = "";
            char pw[10] = "";
            signupPage(0, 0, 0, 0, 3, win1, win2, name, id, pw, fd_cs2, fd_sc2); // signup
        }
    }

    if (k == 1)
    { // 커서의 위치 login
        mvwprintw(win1, 6, 34, "> Login");
        mvwprintw(win1, 8, 34, "  Sign Up");
        wrefresh(win1);
        wrefresh(win2);
    }
    else
    { // 커서의 위치 signup
        mvwprintw(win1, 6, 34, "  Login");
        mvwprintw(win1, 8, 34, "> Sign Up");
        wrefresh(win1);
        wrefresh(win2);
    }

    key = getch();                             // 키를  입력받음
    if (key != 10 && key != 27)                // 엔터와 esc키가 아니면
        updownPage(key, k, l, fd_cs2, fd_sc2); // 입력받은 키로 updownpage 다시 호출
    else if (key == 27)
    {           // esc키 입력
        return; // main으로 돌아감
    }
    else
    {
        if (k == 1)
        { // login 선택
            WINDOW *win1 = newwin(18, 80, 0, 0);
            WINDOW *win2 = newwin(6, 80, 18, 0);
            wbkgd(win1, COLOR_PAIR(1));
            wbkgd(win2, COLOR_PAIR(2));
            mvwprintw(win1, 4, 34, "ID: ");
            mvwprintw(win1, 6, 34, "PW: ");
            mvwprintw(win1, 9, 35, "  Login");
            wrefresh(win1);
            mvwprintw(win2, 0, 35, "%s", l.c_str());
            wrefresh(win2);
            char id[11] = "";
            char pw[11] = "";
            loginPage(0, 0, 0, 3, win1, win2, id, pw, fd_cs2, fd_sc2);
        }
        else
        { // signup 선택
            WINDOW *win1 = newwin(18, 80, 0, 0);
            WINDOW *win2 = newwin(6, 80, 18, 0);
            wbkgd(win1, COLOR_PAIR(1));
            wbkgd(win2, COLOR_PAIR(2));
            mvwprintw(win1, 4, 32, "NAME: ");
            mvwprintw(win1, 6, 34, "ID: ");
            mvwprintw(win1, 8, 34, "PW: ");
            mvwprintw(win1, 12, 35, "  Sign Up");
            wrefresh(win1);
            mvwprintw(win2, 0, 35, "%s", l.c_str());
            wrefresh(win2);
            char name[11] = "";
            char id[11] = "";
            char pw[11] = "";
            signupPage(0, 0, 0, 0, 3, win1, win2, name, id, pw, fd_cs2, fd_sc2);
        }
    }
}

void loginPage(int x, int y, int k, char key, WINDOW *win1, WINDOW *win2,
               char *id, char *pw, int fd_cs2, int fd_sc2)
{
    curs_set(1); // 커서 생성
    if (key == 3)
    { // 위 방향키
        if (k > 0)
        {
            k--;
        }
    }
    else if (key == 2)
    { // 아래 방향키
        if (k < 2)
        {
            k++;
        }
    }
    else if (key == 27)
    {                              // esc키
        firstPage(fd_cs2, fd_sc2); // main으로 돌아감
    }
    else if (key != 10)
    { // 엔터키가 아닌값이 들어오는 경우
        // id의 길이가 10보다 짧고 id의 위치에 커서가 있는 경우
        if (k == 0 && x < 10)
        {
            mvwprintw(win1, 4, 38 + x, "%c", key); // 받아온 키값 출력
            id[x] = char(key);                     // 배열에 저장
            wrefresh(win1);
            x++;
            // 입력된 id의 길이가 10보다 작고 입력된 key가 위,아래,esc,enter가
            // 아닌 경우
            while (x < 10 && key != 10 && key != 3 && key != 2 && key != 27)
            {
                key = getch();
                // 입력된 key가 위,아래,esc,enter가 아닌 경우
                if (key != 10 && key != 3 && key != 2 && key != 27)
                {
                    mvwprintw(win1, 4, 38 + x, "%c", key);
                    wrefresh(win1);
                    id[x] = char(key);
                    x++;
                }
            }
            if (x < 9)                                                       // 길이가 9보다 작은 경우
                loginPage(x, y, k, key, win1, win2, id, pw, fd_cs2, fd_sc2); // 다시 로그인 호출
            // pw의 길이가 10보다 짧고 pw의 위치에 커서가 있는 경우
        }
        else if (k == 1 && y < 10)
        {
            mvwprintw(win1, 6, 38 + y, "*"); //*로 화면 출력
            pw[y] = char(key);
            wrefresh(win1);
            y++;
            while (y < 10 && key != 10 && key != 10 && key != 3 && key != 2 &&
                   key != 27)
            {
                key = getch();
                if (key != 10 && key != 3 && key != 2 && key != 27)
                {
                    mvwprintw(win1, 6, 38 + y, "*");
                    wrefresh(win1);
                    pw[y] = char(key);
                    y++;
                }
            }
            if (y < 9)
                loginPage(x, y, k, key, win1, win2, id, pw, fd_cs2, fd_sc2);
        }
    }

    if (k == 0)
    { // 커서위치 id
        move(4, 38 + x);
        mvwprintw(win1, 9, 35, "  Login");
        wrefresh(win1);
    }
    else if (k == 1)
    { // 커서위치 pw
        move(6, 38 + y);
        mvwprintw(win1, 9, 35, "  Login");
        wrefresh(win1);
    }
    else if (k == 2)
    {
        curs_set(0); // 커서 없애기
        mvwprintw(win1, 9, 35, "> Login");
        wrefresh(win1);
    }

    key = getch();
    if (key != 10) // 엔터가 아니면
        loginPage(x, y, k, key, win1, win2, id, pw, fd_cs2, fd_sc2);
    else
    {
        if (k == 2)
        { // 로그인 버튼에 커서가 있는 경우
            Mem *mem = (Mem *)malloc(sizeof(Mem));
            memset(mem->pw, '\0', MAX_SIZE + 1);
            memset(mem->id, '\0', MAX_SIZE + 1);
            std::string filepath = "";
            ssize_t rSize = 0;
            int i = 0;
            // id, pw를 모두 입력 받은 경우
            if (strlen(id) != 0)
            {
                if (strlen(pw) != 0)
                {
                    // 입력받은 id로 dat파일 이름 생성
                    // filepath += "./";
                    // if (x == 10)
                    // {
                    //     for (int l = 0; l < 10; l++)
                    //     {
                    //         filepath += id[l];
                    //     }
                    // }
                    // else
                    // {
                    //     filepath += id;
                    // }
                    // filepath += ".dat";
                    // int fd1 = open(filepath.c_str(), O_RDONLY, 0755);
                    // if (fd1 == -1)
                    // { // 파일이 존재하지 않음
                    //     i++;
                    // }
                    // else
                    // { // 파일이 존재함
                    //     rSize = read(fd1, (Mem *)mem, sizeof(Mem));
                    //     if (!strcmp(pw, mem->pw))
                    //     { // 비밀번호 확인
                    //         int count = 4;
                    //         // 메세지 배열
                    //         std::string *arr = new std::string[count];
                    //         arr[0] = "Message1";
                    //         arr[1] = "Message2";
                    //         arr[2] = "Message3";
                    //         arr[3] = "Message4";
                    //         WINDOW *win1 = newwin(18, 80, 0, 0);
                    //         WINDOW *win2 = newwin(6, 80, 18, 0);
                    //         wbkgd(win1, COLOR_PAIR(1));
                    //         wbkgd(win2, COLOR_PAIR(2));
                    //         // 메인화면 화면 구성
                    //         for (int i = 0; i < sizeof(arr) / 2; i++)
                    //         {
                    //             mvwprintw(win1, i, 0, "  %s", arr[i].c_str());
                    //         }
                    //         mvwprintw(win1, 0, 0, "> %s", arr[0].c_str());
                    //         mvwprintw(win2, 0, 72, "  Logout");
                    //         wrefresh(win1);
                    //         wrefresh(win2);
                    //         printPage(0, 0, 3, mem->id, mem->name, win1, win2,
                    //                   arr, fd_cs2, fd_sc2); // 메인화면으로 이동
                    //     }
                    //     else
                    //     { // 비밀번호가 다름
                    //         mvwprintw(win2, 0, 35, "Incorrect Password");
                    //         wrefresh(win2);
                    //         key = getch();
                    //         if (key != 0)
                    //         {
                    //             free(mem);
                    //             close(fd1);
                    //             updownPage(10, 1, "", fd_cs2, fd_sc2); // 다시 로그인 입력
                    //         }
                    //     }
                    // }
                    // if (i != 0)
                    // { // 파일이 존재하지 않는 경우
                    //     mvwprintw(win2, 0, 35, "ID doesn't exist");
                    //     wrefresh(win2);
                    //     key = getch();
                    //     if (key != 0)
                    //     {
                    //         free(mem);
                    //         close(fd1);
                    //         updownPage(10, 1, "", fd_cs2, fd_sc2); // 다시 로그인 입력
                    //     }
                    // }
                    CS2 *cs2 = (CS2 *)malloc(sizeof(CS2));
                        memset(cs2->id, '\0', MAX_SIZE + 1);
                         memset(cs2->id2, '\0', MAX_SIZE + 1);
                        memset(cs2->pw, '\0', MAX_SIZE + 1);
                        

                        SC2 *sc2 = (SC2 *)malloc(sizeof(SC2));
                        sc2->page=1;
                        memset(sc2->check, '\0', MAX_SIZE + 1);
                        memset(sc2->problem, '\0', MAX_SIZE + 1);

                        cs2->page = 0;
                        strcpy(cs2->id, id);
                        strcpy(cs2->pw,pw);

                        write(fd_cs2, (CS2 *)cs2, sizeof(CS2));
                        read(fd_sc2, (SC2 *)sc2, sizeof(SC2));
                        mvwprintw(win2, 0, 35, "%s", sc2->check);
                        wrefresh(win2);
                        if (sc2->page == 1){
                            key = getch();
                            if (key != 0)
                                updownPage(10, 1, "", fd_cs2, fd_sc2);
                        }
                        else{
                            int count = 4;
                            // 메세지 배열
                            std::string *arr = new std::string[count];
                            arr[0] = "Message1";
                            arr[1] = "Message2";
                            arr[2] = "Message3";
                            arr[3] = "Message4";
                            WINDOW *win1 = newwin(18, 80, 0, 0);
                            WINDOW *win2 = newwin(6, 80, 18, 0);
                            wbkgd(win1, COLOR_PAIR(1));
                            wbkgd(win2, COLOR_PAIR(2));
                            // 메인화면 화면 구성
                            mvwprintw(win1, 0, 0, "Input user ID : ");
                            mvwprintw(win1, 1, 0, ">> ");
                            mvwprintw(win1, 2, 0, "=====================================================================");
                            mvwprintw(win1, 3, 0, "User List ( 1 / 3 )");

                            
                            for (int i = 0; i < sizeof(arr) / 2; i++)
                            {
                                mvwprintw(win1, 4+i, 0, "  %s", arr[i].c_str());
                            }
                            mvwprintw(win1, 4, 0, "> %s", arr[0].c_str());
                            mvwprintw(win2, 0, 72, "  Logout");
                            wrefresh(win1);
                            wrefresh(win2);
                            char id2[10] = "";
                            printPage(0, 0, 3, sc2->id, sc2->name, win1, win2, arr, fd_cs2, fd_sc2,0,id2); // 메인화면으로 이동
                        }
                }
                else
                {
                    updownPage(10, 1, "", fd_cs2, fd_sc2);
                }
            }
            else
            {
                updownPage(10, 1, "", fd_cs2, fd_sc2);
            }
        }
        else
        { // 로그인이 아닌 곳에 커서가 있는 경우
            loginPage(x, y, k, key, win1, win2, id, pw, fd_cs2, fd_sc2);
        }
    }
}

void signupPage(int x, int y, int z, int k, char key, WINDOW *win1,
                WINDOW *win2, char *name, char *id, char *pw, int fd_cs2, int fd_sc2)
{
    curs_set(1);
    if (key == 3)
    {
        if (k > 0)
        {
            k--;
        }
    }
    else if (key == 2)
    {
        if (k < 3)
        {
            k++;
        }
    }
    else if (key == 27)
    {
        firstPage(fd_cs2, fd_sc2);
    }
    else
    {
        // name, id, pw입력
        if (k == 0 && x < 10 && key != 10)
        {
            mvwprintw(win1, 4, 38 + x, "%c", key);
            name[x] = char(key);
            wrefresh(win1);
            x++;
            while (x < 9 && key != 10 && key != 27 && key != 3 && key != 2)
            {
                key = getch();
                if (key != 10 && key != 27 && key != 3 && key != 2)
                {
                    mvwprintw(win1, 4, 38 + x, "%c", key);
                    wrefresh(win1);
                    name[x] = char(key);
                    x++;
                }
            }
            if (x < 9)
            {
                signupPage(x, y, z, k, key, win1, win2, name, id, pw, fd_cs2, fd_sc2);
            }
        }
        else if (k == 1 && y < 10 && key != 10)
        {
            mvwprintw(win1, 6, 38 + y, "%c", key);
            id[y] = char(key);
            wrefresh(win1);
            y++;
            while (y < 9 && key != 10 && key != 27 && key != 3 && key != 2)
            {
                key = getch();
                if (key != 10 && key != 27 && key != 3 && key != 2)
                {
                    mvwprintw(win1, 6, 38 + y, "%c", key);
                    wrefresh(win1);
                    id[y] = char(key);
                    y++;
                }
            }
            if (y < 9)
                signupPage(x, y, z, k, key, win1, win2, name, id, pw, fd_cs2, fd_sc2);
        }
        else if (k == 2 && z < 10 && key != 10)
        {
            mvwprintw(win1, 8, 38 + z, "*");
            pw[z] = char(key);
            wrefresh(win1);
            z++;
            while (z < 9 && key != 10 && key != 27 && key != 3 && key != 2)
            {
                key = getch();
                if (key != 10 && key != 27 && key != 3 && key != 2)
                {
                    mvwprintw(win1, 8, 38 + z, "*");
                    wrefresh(win1);
                    pw[z] = char(key);
                    z++;
                }
            }
            if (z < 9)
                signupPage(x, y, z, k, key, win1, win2, name, id, pw, fd_cs2, fd_sc2);
        }
    }

    if (k == 0)
    {
        move(4, 38 + x);
        mvwprintw(win1, 12, 35, "  Sign Up");
        wrefresh(win1);
    }
    else if (k == 1)
    {
        move(6, 38 + y);
        mvwprintw(win1, 12, 35, "  Sign Up");
        wrefresh(win1);
    }
    else if (k == 2)
    {
        move(8, 38 + z);
        mvwprintw(win1, 12, 35, "  Sign Up");
        wrefresh(win1);
    }
    else if (k == 3)
    {
        curs_set(0);
        mvwprintw(win1, 12, 35, "> Sign Up");
        wrefresh(win1);
    }
    key = getch();
    if (key != 10)
        signupPage(x, y, z, k, key, win1, win2, name, id, pw, fd_cs2, fd_sc2);
    else if (key == 10)
    {
        if (k == 3)
        {

            ssize_t rSize;
            int i = 0;
            std::string filepath = "";

            // name, id, pw가 모두 입력된 경우
            if (strlen(name) != 0)
            {
                if (strlen(id) != 0)
                {
                    if (strlen(pw) != 0)
                    {
                        CS2 *cs2 = (CS2 *)malloc(sizeof(CS2));
                        cs2->page=0;
                        memset(cs2->id, '\0', MAX_SIZE + 1);
                        memset(cs2->id2, '\0', MAX_SIZE + 1);
                        memset(cs2->name, '\0', MAX_SIZE + 1);
                        memset(cs2->pw, '\0', MAX_SIZE + 1);
                        

                        SC2 *sc2 = (SC2 *)malloc(sizeof(SC2));
                        sc2->page=100;
                        memset(sc2->check, '\0', MAX_SIZE + 1);
                        memset(sc2->id, '\0', MAX_SIZE + 1);
                        memset(sc2->name, '\0', MAX_SIZE + 1);
                        memset(sc2->problem, '\0', MAX_SIZE + 1);

                        cs2->page = 1;
                        strcpy(cs2->id, id);
                        strcpy(cs2->name,name);
                        strcpy(cs2->pw,pw);

                        write(fd_cs2, (CS2 *)cs2, sizeof(CS2));
                        read(fd_sc2, (SC2 *)sc2, sizeof(SC2));
                        mvwprintw(win2, 0, 35, "%s",sc2->check);
                        wrefresh(win2);
                        if (sc2->page == 1){
                            key = getch();
                            if (key != 0)
                                updownPage(10, 2, "", fd_cs2, fd_sc2);
                        }
                        else{
                            updownPage(10, 1, "", fd_cs2, fd_sc2);
                        }
                    }
                    else
                    {
                        mvwprintw(win2, 0, 35, "Please fill all the blanks");
                        wrefresh(win2);
                        key = getch();
                        if (key != 0)
                            updownPage(10, 2, "", fd_cs2, fd_sc2);
                    }
                }
                else
                {
                    mvwprintw(win2, 0, 35, "Please fill all the blanks");
                    wrefresh(win2);
                    key = getch();
                    if (key != 0)
                        updownPage(10, 2, "", fd_cs2, fd_sc2);
                }
            }
            else
            {
                mvwprintw(win2, 0, 35, "Please fill all the blanks");
                wrefresh(win2);
                key = getch();
                if (key != 0)
                    updownPage(10, 2, "", fd_cs2, fd_sc2);
            }
        }
        else
        {
            signupPage(x, y, z, k, key, win1, win2, name, id, pw, fd_cs2, fd_sc2);
        }
    }
}
void printPage(int num, int k, char key, char *id, char *name, WINDOW *win1,
               WINDOW *win2, std::string *arr, int fd_cs2, int fd_sc2,int x,char *id2)
{
    for (int i = 0; i < sizeof(arr) / 2; i++)
    { // 배열의 사이즈만큼 내용 출력
        mvwprintw(win1, 4+i, 0, "  %s", arr[i].c_str());
    }
    // 받아온 id, name 출력
    mvwprintw(win2, 0, 0, "ID: %s", id);
    mvwprintw(win2, 1, 0, "NAME: %s", name);
    wrefresh(win2);

    if (key == 3)
    {
        if (k > 0)
        {
            k--;
        }
    }
    else if (key == 2)
    {
        if(k==0){
            curs_set(0);
        }
        if (k < sizeof(arr) / 2)
        { // 메세지 개수 만큼
            k++;
        }
        
    }
    else if (key == 27)
    { // esc키를 누른 경우
        if (num % 2 == 1)
        {
            mvwprintw(win2, 0, 72, "  Logout");
            curs_set(1);
            move(0,15);
            // mvwprintw(win1, 4, 0, "> %s", arr[0].c_str()); // 맨 커음 값에 표시
            wrefresh(win1);
            wrefresh(win2);
            k = 0; // 커서위치 0으로 설정
        }
        else
        {
            mvwprintw(win1, 4+k, 0, "  %s", arr[k].c_str());
            mvwprintw(win2, 0, 72, "> Logout");
            wrefresh(win1);
            wrefresh(win2);
            k = -1; // 커서 -1로 설정(위아래 키를 입력받았을때 k값에 변동이
                    // 없도록)
        }
        num++;
    }
    else if(k==0){
        move(0,17);
        while (x < 10)
            {
                mvwprintw(win1, 0, 16 + x, "%c",char(key));
                wrefresh(win1);
                id2[x] = char(key);
                x++;
                key = getch();
                if(key==10){
                    CS2 *cs2 = (CS2 *)malloc(sizeof(CS2));
                    memset(cs2->id, '\0', MAX_SIZE + 1);
                    memset(cs2->pw, '\0', MAX_SIZE + 1);
                     memset(cs2->id2, '\0', MAX_SIZE + 1);
                    

                    SC2 *sc2 = (SC2 *)malloc(sizeof(SC2));
                    memset(sc2->check, '\0', MAX_SIZE + 1);
                    memset(sc2->problem, '\0', MAX_SIZE + 1);

                    cs2->page = 2;
                    strcpy(cs2->id, id);
                    strcpy(cs2->id2, id2);

                    write(fd_cs2, (CS2 *)cs2, sizeof(CS2));
                    read(fd_sc2, (SC2 *)sc2, sizeof(SC2));
                    mvwprintw(win1, 1, 4, "%s", sc2->check);
                    wrefresh(win1);
                    if(sc2->page==1){
                        getch();
                        char id2[10] = "";
                        werase(win1);
                        mvwprintw(win1, 0, 0, "Input user ID : ");
                        mvwprintw(win1, 1, 0, ">> ");
                        mvwprintw(win1, 2, 0, "=====================================================================");
                        mvwprintw(win1, 3, 0, "User List ( 1 / 3 )");
                        wrefresh(win1);
                        printPage(0, 0, 3, id, name, win1, win2, arr, fd_cs2, fd_sc2,0,id2); // 메인화면으로 이동
                    }
                    else{
                        WINDOW *win1 = newwin(18, 80, 0, 0);
                        WINDOW *win2 = newwin(6, 80, 18, 0);
                        wbkgd(win1, COLOR_PAIR(1));
                        wbkgd(win2, COLOR_PAIR(2));
                        std::string a = std::string(id);
                        mvwprintw(win1, 0, 74-a.length(), "<%s(me)>", id);
                        mvwprintw(win2, 0, 0, "Message with %s", id2);
                        mvwprintw(win2, 1, 0, "Input Message : ");
                        curs_set(1);
                        move(50,20);
                        wrefresh(win1);
                        wrefresh(win2);
                        mainwindow(win1,win2,id,id2);
                    }


                }
                
            }
    }
    for (int i = 0; i < sizeof(arr) / 2; i++)
    {
        if(k==0){
            mvwprintw(win1, 4, 0, "  %s", arr[0].c_str());
            curs_set(1);
            move(0,16);
            wrefresh(win2);
            wrefresh(win1);
        }
        if (k-1 == i)
        { // k값과 같은 부분의 메세지에 표시
            curs_set(0);
            mvwprintw(win1, 4+i, 0, "> %s", arr[i].c_str());
            wrefresh(win2);
            wrefresh(win1);
        }
    }
    key = getch();
    if (key != 10)
    {
        printPage(num, k, key, id, name, win1, win2, arr, fd_cs2, fd_sc2,x,id2);
    }
    else
    {
        if (k == -1)
        {                              // 로그아웃에 있을 때
            firstPage(fd_cs2, fd_sc2); // 메인으로 돌아감
        }
        else
        {
            printPage(num, k, key, id, name, win1, win2, arr, fd_cs2, fd_sc2,x,id2);
        }
    }
}

int firstPage(int fd_cs2, int fd_sc2)
{
    initscr();
    if (has_colors() == FALSE)
    {
        puts("Terminal");
        endwin();
        return 1;
    }
    else
    {
        start_color();
        init_pair(1, COLOR_BLUE, COLOR_WHITE);
        init_pair(2, COLOR_WHITE, COLOR_BLUE);
    }
    refresh();

    char key;
    while (true)
    {
        curs_set(0);
        keypad(stdscr, TRUE);
        noecho();
        mainPage(); // 첫 화면 구성
        key = getch();
        if (key == 27)
        { // esc키 입력
            endwin();
            exit(true);
        }
        else if (key == 2)
        {                                          // 위 아래 키 입력
            updownPage(2, 1, " ", fd_cs2, fd_sc2); // 위아래로 이동하는 함수
            endwin();
            exit(true);
        }
        else if (key == 3)
        { // 위 아래 키 입력
            updownPage(3, 1, " ", fd_cs2, fd_sc2);
            endwin();
            exit(true);
        }
        else if (key == 10)
        {
            updownPage(10, 1, " ", fd_cs2, fd_sc2);
            endwin();
            exit(true);
        }
    }
    endwin();
    return 0;
}

int mainwindow(WINDOW *win1,WINDOW *win2,char* id, char*id2){
    
    getch();
    return 0;
}