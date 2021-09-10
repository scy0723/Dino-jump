//300점마다 속도 증가 (sleep함수의 시간 줄임)
//공룡 몸통 앞부분이 나무와 닿으면 게임오버
//점수는 꾸준히 올라감
#include <stdlib.h>
#include<Windows.h>
#include<conio.h>
#include<stdio.h>

#define DINOSAUR_DISTANCE_FROM_TOP_Y 12
#define TREE_DISTANCE_FROM_LEFT_X 90
#define TREE_DISTANCE_FROM_TOP_Y 20
#define SCORE_BOARD_FROM_LEFT 45
#define GAME_OVER_FROM_LEFT 45
#define GAME_OVER_FROM_TOP 10
#define SPEED_UP_FROM_TOP 4
#define SPEED_UP_FROM_LEFT 45

int GetKeyDown(); //입력한 키
void DrawDinosaur(int);
void DrawTree(int);
void GotoXY(int, int);  //(X,Y)
void InitConsoleConfig();
void PrintScore(int);
void PrintGameOver(int);

//bool legDraw = true;//공룡이 움직이려면 전역으로 해주는 방식도 가능
int main(int argc, char* argv[]) {
    int dinosaurY = DINOSAUR_DISTANCE_FROM_TOP_Y;
    bool jumping = false;
    bool walking = true;
    const int gravity = 3;
    const int speed = 5;
    int score = 0;
    int treeX = TREE_DISTANCE_FROM_LEFT_X;
    int sleepTime = 70;

    int again = true;
    InitConsoleConfig();//콘솔창 사이즈 조절

    while (again) {
        //scanf는 입력할 때까지 기다리니까 ㄴㄴ
        if (GetKeyDown() == 32 && walking) {//스페이스를 눌렀고 지금 걷고 있을 때
            jumping = true;
            walking = false;
        }
        if (jumping) {
            dinosaurY = dinosaurY - gravity;
        }
        else {
            dinosaurY = dinosaurY + gravity;
        }
        if (dinosaurY <= 0) {
            dinosaurY = 0;
            jumping = false;
        }
        if (dinosaurY >= DINOSAUR_DISTANCE_FROM_TOP_Y) {
            dinosaurY = DINOSAUR_DISTANCE_FROM_TOP_Y;
            walking = true;
        }
        if (treeX <= 0) {
            treeX = TREE_DISTANCE_FROM_LEFT_X;
        }

        if (treeX <= 12 && dinosaurY == DINOSAUR_DISTANCE_FROM_TOP_Y) { //나무는 왔는데 공룡은 바닥에 있음 -> 죽음
            PrintGameOver(score);
            break;
        }

        else score += 5; //점수+

        if (score % 300 == 0 && score != 0) {//150점마다 속도++
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            GotoXY(SPEED_UP_FROM_LEFT, SPEED_UP_FROM_TOP);
            printf("SPEED UP!!");
            if (sleepTime > 0) {
                sleepTime -= 15;
            }//sleepTime이 0이면 최대속도
        }
        if (score % 300 <= 30 && score > 30) { //speed up 표시 유지
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            GotoXY(SPEED_UP_FROM_LEFT, SPEED_UP_FROM_TOP);
            printf("SPEED UP!!");
        }
        treeX = treeX - speed;//이거만 하면 음수가 돼서 나무가 빠개짐
        //잔상 없애기(cmd cls)
        DrawDinosaur(dinosaurY);
        DrawTree(treeX);
        PrintScore(score);
        Sleep(sleepTime);
        system("cls");//stdlib.h

    }
    return 0;
}

void InitConsoleConfig() {
    system("mode con:cols=100 lines=25"); //콘솔창 크기 조절
}

int GetKeyDown() {
    if (_kbhit()) { //키보드를 누르면 입력스트림에 저장함 (queue)
        return _getch();//그 queue에 있는 애를 가져옴
    }
    return 0;
}
void GotoXY(int x, int y) {
    COORD coord;//콘솔 (아래줄 하려고 쓰는거)
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); //핸들이라는게 윈도우에서 제공하는 거
}

void DrawDinosaur(int dinosaurY) {

    static bool legDraw = true; //컴파일이 될 때부터 global처럼 쓰임(끝날 때까지)
    GotoXY(0, dinosaurY); //(0,12)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
    //system("color 2E");//매번 실행
    //라이브러리 사용
    printf("        &&&&&&& \n");
    printf("       && &&&&&&\n");
    printf("       &&&&&&&&&\n");
    printf("&      &&&      \n");
    printf("&&     &&&&&&&  \n");
    printf("&&&   &&&&&     \n");
    printf(" &&  &&&&&&&&&& \n");
    printf(" &&&&&&&&&&&    \n");
    printf("  &&&&&&&&&&    \n");
    printf("    &&&&&&&&    \n");
    printf("     &&&&&&     \n");

    if (legDraw) {

        printf("     &    &&&     \n");
        printf("     &&           ");

        legDraw = false;

    }

    else {
        printf("     &&&  &       \n");
        printf("          &&      ");

        legDraw = true;

    }
}
void DrawTree(int treeX) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
    GotoXY(treeX, TREE_DISTANCE_FROM_TOP_Y);
    printf("$$$$");
    GotoXY(treeX, TREE_DISTANCE_FROM_TOP_Y + 1);
    printf(" $$ ");
    GotoXY(treeX, TREE_DISTANCE_FROM_TOP_Y + 2);
    printf(" $$ ");
    GotoXY(treeX, TREE_DISTANCE_FROM_TOP_Y + 3);
    printf(" $$ ");
    GotoXY(treeX, TREE_DISTANCE_FROM_TOP_Y + 4);
    printf(" $$ ");
}
void PrintScore(int score) {
    GotoXY(SCORE_BOARD_FROM_LEFT, 1);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    printf("Score:%d", score);
}
void PrintGameOver(int score) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    GotoXY(GAME_OVER_FROM_LEFT, GAME_OVER_FROM_TOP);
    printf("GAME OVER");
    GotoXY(GAME_OVER_FROM_LEFT - 2, GAME_OVER_FROM_TOP + 1);
    printf("Your Score:%d\n\n\n\n\n\n\n", score);

}