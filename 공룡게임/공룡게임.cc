//300������ �ӵ� ���� (sleep�Լ��� �ð� ����)
//���� ���� �պκ��� ������ ������ ���ӿ���
//������ ������ �ö�
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

int GetKeyDown(); //�Է��� Ű
void DrawDinosaur(int);
void DrawTree(int);
void GotoXY(int, int);  //(X,Y)
void InitConsoleConfig();
void PrintScore(int);
void PrintGameOver(int);

//bool legDraw = true;//������ �����̷��� �������� ���ִ� ��ĵ� ����
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
    InitConsoleConfig();//�ܼ�â ������ ����

    while (again) {
        //scanf�� �Է��� ������ ��ٸ��ϱ� ����
        if (GetKeyDown() == 32 && walking) {//�����̽��� ������ ���� �Ȱ� ���� ��
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

        if (treeX <= 12 && dinosaurY == DINOSAUR_DISTANCE_FROM_TOP_Y) { //������ �Դµ� ������ �ٴڿ� ���� -> ����
            PrintGameOver(score);
            break;
        }

        else score += 5; //����+

        if (score % 300 == 0 && score != 0) {//150������ �ӵ�++
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            GotoXY(SPEED_UP_FROM_LEFT, SPEED_UP_FROM_TOP);
            printf("SPEED UP!!");
            if (sleepTime > 0) {
                sleepTime -= 15;
            }//sleepTime�� 0�̸� �ִ�ӵ�
        }
        if (score % 300 <= 30 && score > 30) { //speed up ǥ�� ����
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            GotoXY(SPEED_UP_FROM_LEFT, SPEED_UP_FROM_TOP);
            printf("SPEED UP!!");
        }
        treeX = treeX - speed;//�̰Ÿ� �ϸ� ������ �ż� ������ ������
        //�ܻ� ���ֱ�(cmd cls)
        DrawDinosaur(dinosaurY);
        DrawTree(treeX);
        PrintScore(score);
        Sleep(sleepTime);
        system("cls");//stdlib.h

    }
    return 0;
}

void InitConsoleConfig() {
    system("mode con:cols=100 lines=25"); //�ܼ�â ũ�� ����
}

int GetKeyDown() {
    if (_kbhit()) { //Ű���带 ������ �Է½�Ʈ���� ������ (queue)
        return _getch();//�� queue�� �ִ� �ָ� ������
    }
    return 0;
}
void GotoXY(int x, int y) {
    COORD coord;//�ܼ� (�Ʒ��� �Ϸ��� ���°�)
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); //�ڵ��̶�°� �����쿡�� �����ϴ� ��
}

void DrawDinosaur(int dinosaurY) {

    static bool legDraw = true; //�������� �� ������ globaló�� ����(���� ������)
    GotoXY(0, dinosaurY); //(0,12)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
    //system("color 2E");//�Ź� ����
    //���̺귯�� ���
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