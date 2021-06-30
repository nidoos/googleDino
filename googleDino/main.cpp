#include <stdio.h>
#include <windows.h> //GotoXY(), system(cls())
#include <time.h>
#include <conio.h> //_hbhit()
#define DINO_BOTTOM_Y 12
#define TREE_BOTTOM_X 45
#define TREE_BOTTOM_Y 20

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

bool isCollision(const int treeX, const int dinoY){
    GotoXY(0,0);
    printf("treeX : %d, dinoY : %d", treeX, dinoY);
    if(treeX <= 8 && treeX >=4 && dinoY >8){
        return true;
    }
    return false;
}

int main(){
    SetConsoleView();

    while(true){
        // 게임시작시 초기화
        bool isJunmping = false;
        bool isBottom = true;
        const int gravity = 3;

        int dinoY = DINO_BOTTOM_Y;
        int treeX = TREE_BOTTOM_X;

        int score = 0;
        clock_t start, curr; //점수 변수 초기화
        start = clock();    //시각시간 초기화

        while (true) //한 판에 대한 루프
        {   
            // 충돌체크 트리 x값, 공룡 y값으로 판단
            if(isCollision(treeX, dinoY))
                break;
            if(GetKeyDown() == 'z' & isBottom){
                isJunmping = true;
                isBottom = false;
            }

            if(isJunmping){
                // 점프중이라면 y 감소, 점프 끝나면 y증가
                dinoY -= gravity;
            }else{
                dinoY += gravity;
            }

            //y가 계속 증가하는 것을 막기위해 바닥 지정
            if(dinoY >= DINO_BOTTOM_Y){
                dinoY = DINO_BOTTOM_Y;
                isBottom = true;
            }

            //나무가 왼쪽으로 가도록, 나무의 위치가 왼쪽 끝으로 가면 다시 오른쪽 끝으로 소환
            treeX -= 2;
            if(treeX<=0){
                treeX = TREE_BOTTOM_X;
            }

            //점프의 맨위를 찍으면 점프 끝
            if (dinoY <=3){
                isJunmping = false;
            }

            DrawDino(dinoY);
            DrawTree(treeX);

            curr = clock();
            if((curr-start)/(CLOCKS_PER_SEC)>=1) //1초가 넘었을 때
            {
                score++;
                start = clock();
            }
            Sleep(60);
            system("cls");

            GotoXY(22, 0);
            printf("Score : %d ", score);
        }
        DrawGameOver(score);
    }
    return 0;
} 