#include <stdio.h>
#include <windows.h> //GotoXY(), system(cls())
#include <time.h>
#include <conio.h> //_hbhit()
#define DINO_BOTTOM_Y 12
#define TREE_BOTTOM_X 45
#define TREE_BOTTOM_Y 20

//�ܼ� â ũ�� ���� ����
void SetConsoleView(){
    system("mode con:cols=100 lines=25");
    system("title Google Dino");
}

//Ŀ�� ��ġ x,y�� �̵�
void GotoXY(int x, int y){
    COORD Pos;
    Pos.X = 2*x;
    Pos.Y= y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//Ű���� �Է�
int GetKeyDown(){
    if(_kbhit() !=0){
        return _getch();
    }
    return 0;
}

//���� �׸���
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

//����
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

// �浹 �� ���ӿ���
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
        // ���ӽ��۽� �ʱ�ȭ
        bool isJunmping = false;
        bool isBottom = true;
        const int gravity = 3;

        int dinoY = DINO_BOTTOM_Y;
        int treeX = TREE_BOTTOM_X;

        int score = 0;
        clock_t start, curr; //���� ���� �ʱ�ȭ
        start = clock();    //�ð��ð� �ʱ�ȭ

        while (true) //�� �ǿ� ���� ����
        {   
            // �浹üũ Ʈ�� x��, ���� y������ �Ǵ�
            if(isCollision(treeX, dinoY))
                break;
            if(GetKeyDown() == 'z' & isBottom){
                isJunmping = true;
                isBottom = false;
            }

            if(isJunmping){
                // �������̶�� y ����, ���� ������ y����
                dinoY -= gravity;
            }else{
                dinoY += gravity;
            }

            //y�� ��� �����ϴ� ���� �������� �ٴ� ����
            if(dinoY >= DINO_BOTTOM_Y){
                dinoY = DINO_BOTTOM_Y;
                isBottom = true;
            }

            //������ �������� ������, ������ ��ġ�� ���� ������ ���� �ٽ� ������ ������ ��ȯ
            treeX -= 2;
            if(treeX<=0){
                treeX = TREE_BOTTOM_X;
            }

            //������ ������ ������ ���� ��
            if (dinoY <=3){
                isJunmping = false;
            }

            DrawDino(dinoY);
            DrawTree(treeX);

            curr = clock();
            if((curr-start)/(CLOCKS_PER_SEC)>=1) //1�ʰ� �Ѿ��� ��
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