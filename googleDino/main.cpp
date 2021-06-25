#include <stdio.h>
#include <windows.h> //GotoXY(), system(cls())
#include <time.h>
#include <conio.h> //_hbhit()
#define DINO_BOTTOM_Y 12
#define TREE_BOTTOM_X 20
#define TREE_BOTTOM_Y 45

//콘솔 창 크기 제목 지정
void SetConsoleView(){
    system("mode con:cols=100 lines=25");
    system("title Google Dino");
}

//커서 위치 x,y로 이동
void GotoXY(int x, int y){
    COORD Pos;
    Pos.X = 2*x;
    Pos.Y= y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//키보드 입력
int GetKeyDown(){
    if(_kbhit() !=0){
        return _getch();
    }
    return 0;
}

//공룡 그리기
void DrawDino(int dinoY){
    GotoXY(0,dinoY);
    static bool legFlag = true;
    printf("        $$$$$$$ \n");
    printf("       $$ $$$$$$\n");
    printf("       $$$$$$$$$\n");
    printf("$      $$$      \n");
    printf("$$     $$$$$$$  \n");
    printf("$$$   $$$$$     \n");
    printf(" $$  $$$$$$$$$$ \n");
    printf(" $$$$$$$$$$$    \n");
    printf("  $$$$$$$$$$    \n");
    printf("    $$$$$$$$    \n");
    printf("     $$$$$$     \n");

     if (legFlag)
    {
        printf("     $    $$$    \n");
        printf("     $$          ");
        legFlag = false;
    }
    else
    {
        printf("     $$$  $     \n");
        printf("          $$    ");
        legFlag = true;
    }
}

//나무
void DrawTree(int treeX)
{
    GotoXY(treeX, TREE_BOTTOM_Y);
    printf("$$$$");
    GotoXY(treeX, TREE_BOTTOM_Y + 1);
    printf(" $$ ");
    GotoXY(treeX, TREE_BOTTOM_Y + 2);
    printf(" $$ ");
    GotoXY(treeX, TREE_BOTTOM_Y + 3);
    printf(" $$ ");
    GotoXY(treeX, TREE_BOTTOM_Y + 4);
    printf(" $$ ");
}

// 충돌 시 게임오버
void DrawGameOver(const int score){
    system("cls");
    int x = 18;
    int y = 8;
    GotoXY(x, y);
    printf("===========================");
    GotoXY(x, y + 1);
    printf("======G A M E O V E R======");
    GotoXY(x, y + 2);    
    printf("===========================");
    GotoXY(x, y + 5);
    printf("SCORE : %d", score);
 
    printf("\n\n\n\n\n\n\n\n\n");
    system("pause");
}

bool inCollision(const int treeX, const int dinoY){
    GotoXY(0,0);
    printf("treeX : %d, dinoY : %d", treeX, dinoY);
    if(treeX <= 8 && treeX >=4 && dinoY >8){
        return true;
    }
    return false;
}

int main(){
    SetConsoleView();
}