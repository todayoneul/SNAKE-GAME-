#include "main.h"
#include "game.h"
#include "util.h"


void Setup_easy()
{
    gameOver = 0;  // 게임 종료 여부 초기화
    dir = STOP;  // 이동 방향 초기화
    x = WIDTH_easy / 2;  // 뱀의 초기 x 좌표
    y = HEIGHT_easy / 2;  // 뱀의 초기 y 좌표
    fruitX = rand() % WIDTH_easy;  // 과일의 초기 x 좌표
    fruitY = rand() % HEIGHT_easy;  // 과일의 초기 y 좌표
    bombX = rand() % WIDTH_easy;  // 폭탄의 초기 x 좌표
    bombY = rand() % HEIGHT_easy;  // 폭탄의 초기 y 좌표
    score = 0;  // 점수 초기화
    nTail = 0; //만약 뱀이 길어졌다가 게임오버될 경우 꼬리를 초기화 해주어야 다시 게임 진행 가능

}

void Setup_hard()
{
    gameOver = 0;  // 게임 종료 여부 초기화
    dir = STOP;  // 이동 방향 초기화
    x = WIDTH_hard / 2;  // 뱀의 초기 x 좌표
    y = HEIGHT_hard / 2;  // 뱀의 초기 y 좌표
    fruitX = rand() % WIDTH_hard;  // 과일의 초기 x 좌표
    fruitY = rand() % HEIGHT_hard;  // 과일의 초기 y 좌표
    for (int i = 0; i < BOMB_COUNT; i++)
    {
        bombX_hard[i] = rand() % WIDTH_hard;  // 폭탄의 초기 x 좌표
        bombY_hard[i] = rand() % HEIGHT_hard;  // 폭탄의 초기 y 좌표
    }
    score = 0;  // 점수 초기화
    nTail = 0; //만약 뱀이 길어졌다가 게임오버될 경우 꼬리를 초기화 해주어야 다시 게임 진행 가능

}

void Draw_easy()
{
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPos;
    cursorPos.X = 0;
    cursorPos.Y = 0;
    SetConsoleCursorPosition(hConsole, cursorPos); 


    for (int i = 0; i < WIDTH_easy + 2; i++)
        printf("#");
    printf("\n");

    for (int i = 0; i < HEIGHT_easy; i++)
    {
        for (int j = 0; j < WIDTH_easy; j++)
        {
            if (j == 0)
                printf("#");

            if (i == y && j == x)
                printf("O");
            else if (i == fruitY && j == fruitX)
                printf("F");
            else if (i == bombY && j == bombX)
                printf("B");
            else
            {
                int printTail = 0;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        printf("o");
                        printTail = 1;
                    }
                }
                if (!printTail)
                    printf(" ");
            }

            if (j == WIDTH_easy - 1)
                printf("#");
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH_easy + 2; i++)
        printf("#");
    printf("\n");

    printf("Score: %d\n", score);  // 점수 출력
}

void Draw_hard()
{

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPos;
    cursorPos.X = 0;
    cursorPos.Y = 0;
    SetConsoleCursorPosition(hConsole, cursorPos);  //

    for (int i = 0; i < WIDTH_hard + 2; i++)
        printf("#");
    printf("\n");
    for (int i = 0; i < HEIGHT_hard; i++)
    {
        for (int j = 0; j < WIDTH_hard; j++)
        {
            if (j == 0)
                printf("#");

            if (i == y && j == x)
                printf("O");
            else if (i == fruitY && j == fruitX)
                printf("F");
            else
            {
                int printTail = 0;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        printf("o");
                        printTail = 1;
                        break;
                    }
                }
                if (!printTail)
                {
                    int printBomb = 0;
                    for (int k = 0; k < BOMB_COUNT; k++)
                    {
                        if (bombX_hard[k] == j && bombY_hard[k] == i)
                        {
                            printf("B");
                            printBomb = 1;
                            break;
                        }
                    }
                    if (!printBomb)
                        printf(" ");
                }
            }

            if (j == WIDTH_hard - 1)
                printf("#");
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH_hard + 2; i++)
        printf("#");
    printf("\n");

    printf("Score: %d\n", score);  // 점수 출력
}

void Input()
{
    if (_kbhit())  // 키보드 입력이 있는지 확인
    {
        switch (_getch())  // 키 입력 받기
        {
        case 'a':
            if (dir != RIGHT)
                dir = LEFT;  // 왼쪽으로 이동
            break;
        case 'd':
            if (dir != LEFT)
                dir = RIGHT;  // 오른쪽으로 이동
            break;
        case 'w':
            if (dir != DOWN)
                dir = UP;  // 위쪽으로 이동
            break;
        case 's':
            if (dir != UP)
                dir = DOWN;  // 아래쪽으로 이동
            break;
        case 'x':
            gameOver = 1;
            break;
        }
    }
}

void Logic_easy()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
    case LEFT:
        x--;  // 왼쪽으로 이동
        break;
    case RIGHT:
        x++;  // 오른쪽으로 이동
        break;
    case UP:
        y--;  // 위쪽으로 이동
        break;
    case DOWN:
        y++;  // 아래쪽으로 이동
        break;
    }

    if (x < 0)
        x = WIDTH_easy - 1;  // 벽을 통과하여 반대쪽으로 나타나도록 설정
    else if (x >= WIDTH_easy)
        x = 0;

    if (y < 0)
        y = HEIGHT_easy - 1;  // 벽을 통과하여 반대쪽으로 나타나도록 설정
    else if (y >= HEIGHT_easy)
        y = 0;

    for (int i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y) {
            nTail = 0;
           
            gameOver = 1;  // 뱀의 꼬리와 머리가 충돌하면 게임 종료
        }
    }

    if (x == fruitX && y == fruitY)
    {
        score += 10;  // 과일을 먹을 때마다 점수 증가
        fruitX = rand() % WIDTH_easy;  // 과일 위치 재설정
        fruitY = rand() % HEIGHT_easy;
        bombX = rand() % WIDTH_easy;  // 폭탄 위치 재설정
        bombY = rand() % HEIGHT_easy;
        nTail++;  // 뱀의 꼬리 길이 증가
    }

    if (x == bombX && y == bombY)
    {
        gameOver = 1;  // 폭탄을 먹으면 게임 종료
    }
}

void Logic_hard()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
    case LEFT:
        x--;  // 왼쪽으로 이동
        break;
    case RIGHT:
        x++;  // 오른쪽으로 이동
        break;
    case UP:
        y--;  // 위쪽으로 이동
        break;
    case DOWN:
        y++;  // 아래쪽으로 이동
        break;
    }

    if (x < 0)
        x = WIDTH_hard - 1;  // 벽을 통과하여 반대쪽으로 나타나도록 설정
    else if (x >= WIDTH_hard)
        x = 0;

    if (y < 0)
        y = HEIGHT_hard - 1;  // 벽을 통과하여 반대쪽으로 나타나도록 설정
    else if (y >= HEIGHT_hard)
        y = 0;

    for (int i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y) {
            nTail = 0;

            gameOver = 1;  // 뱀의 꼬리와 머리가 충돌하면 게임 종료
        }
    }

    for (int i = 0; i < BOMB_COUNT; i++)
    {
        if (x == bombX_hard[i] && y == bombY_hard[i])
            //gameend = true;
            gameOver = 1;  // 폭탄을 먹으면 게임 종료
    }

    if (x == fruitX && y == fruitY)
    {
        score += 10;  // 과일을 먹을 때마다 점수 증가
        fruitX = rand() % WIDTH_hard;  // 과일 위치 재설정
        fruitY = rand() % HEIGHT_hard;

        for (int i = 0; i < BOMB_COUNT; i++)
        {
            bombX_hard[i] = rand() % WIDTH_hard;  // 폭탄 위치 재설정
            bombY_hard[i] = rand() % HEIGHT_hard;
        }

        nTail++;  // 뱀의 꼬리 길이 증가
    }
}




int getkeydown() {
    if (_kbhit() != 0) {
        return _getch();
    }
    return 0;
}

int keycontrol() {
    char temp = _getch();

    if (temp == 'w' || temp == 'W') {
        return C_UP;
    }
    else if (temp == 'a' || temp == 'A') {
        return C_LEFT;
    }
    else if (temp == 's' || temp == 'S') {
        return C_DOWN;
    }
    else if (temp == 'd' || temp == 'D') {
        return C_RIGHT;
    }
    else if (temp == ' ') {
        return C_SUBMIT;
    }
}


int menudraw() {
    int x = 75;
    int y = 35;
    gotoxy(x - 2, y);
    printf("> 게임시작");
    gotoxy(x, y + 2);
    printf("게임정보");
    gotoxy(x, y + 4);
    printf("   종료   ");

    while (1) {
        int n = keycontrol();
        switch (n)
        {
        case C_UP: {
            if (y > 35) {
                gotoxy(x - 2, y);
                printf(" ");
                y -= 2;
                gotoxy(x - 2, y);
                printf(">");
            }
            break;
        }
        case C_DOWN: {
            if (y < 39) {
                gotoxy(x - 2, y);
                printf(" ");
                y += 2;
                gotoxy(x - 2, y);
                printf(">");
            }
            break;
        }
        case C_SUBMIT: {
            return y - 35;
        }

        }
    }
}

void title() {
    printf("다락방 종강총회 프로젝트\n\n\n");

    printf("         ███████╗███╗   ██╗ █████╗ ██╗  ██╗███████╗     ██████╗  █████╗ ███╗   ███╗███████╗\n");
    printf("         ██╔════╝████╗  ██║██╔══██╗██║ ██╔╝██╔════╝    ██╔════╝ ██╔══██╗████╗ ████║██╔════╝\n");
    printf("         ███████╗██╔██╗ ██║███████║█████╔╝ █████╗      ██║  ███╗███████║██╔████╔██║█████╗  \n");
    printf("         ╚════██║██║╚██╗██║██╔══██║██╔═██╗ ██╔══╝      ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  \n");
    printf("         ███████║██║ ╚████║██║  ██║██║  ██╗███████╗    ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗\n");
    printf("         ╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝     ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝\n");
    printf("\n");



    printf("                                                                ██████  ██    ██      ██████  ██    ██ ██    ██ ██   ██  █████  ███    ██\n");
    printf("                                                                ██   ██  ██  ██      ██        ██  ██  ██    ██ ██   ██ ██   ██ ████   ██\n");
    printf("                                                                ██████    ████       ██   ███   ████   ██    ██ ███████ ███████ ██ ██  ██\n");
    printf("                                                                ██   ██    ██        ██    ██    ██    ██    ██ ██   ██ ██   ██ ██  ██ ██\n");
    printf("                                                                ██████     ██         ██████     ██     ██████  ██   ██ ██   ██ ██   ████\n");
}

void infodraw() {
    system("cls");
    int x = 70;
    int y = 15;
    gotoxy(x - 2, y);
    printf("                [조작법] \n\n\n\n\n");
    printf("                SNAKE 이동 방법 : W, A, S, D \n");
    printf("                인게임 중 종료 : x \n");
    printf("                선택 : 스페이스바 \n\n\n\n\n\n\n");
    printf("                개발자 : 이규한 \n\n\n\n");
    printf("               스페이스바를 누르면 메인화면으로 이동합니다."); \

        while (1) {
            if (keycontrol() == C_SUBMIT) {
                break;
            }
        }
}

int maplistdraw() {
    int x = 75;
    int y = 20;
    system("cls");
    printf("\n\n\n\n\n\n\n");
    gotoxy(75, 15);
    printf("[맵 선택] \n\n");

    gotoxy(x - 2, y);
    printf("> 쉬움");
    gotoxy(x - 2, y + 2);
    printf("  어려움");
    gotoxy(x - 2, y + 4);
    printf("  뒤로");

    while (1) {
        int n = keycontrol();
        switch (n)
        {
        case C_UP: {
            if (y > 20) {
                gotoxy(x - 2, y);
                printf(" ");
                y -= 2;
                gotoxy(x - 2, y);
                printf(">");
            }
            break;
        }
        case C_DOWN: {
            if (y < 24) {
                gotoxy(x - 2, y);
                printf(" ");
                y += 2;
                gotoxy(x - 2, y);
                printf(">");
            }
            break;
        }
        case C_SUBMIT: {
            return y - 20;
        }

        }
    }
}


void drawgameover() {
    system("cls");
    int x = 43;
    int y = 20;
    gotoxy(x, y);     printf(" ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ██╗   ██╗███████╗██████╗\n");
    gotoxy(x, y + 1); printf("██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██║   ██║██╔════╝██╔══██╗\n");
    gotoxy(x, y + 2); printf("██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║██║   ██║█████╗  ██████╔╝\n");
    gotoxy(x, y + 3); printf("██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗\n");
    gotoxy(x, y + 4); printf("╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║\n");
    gotoxy(x, y + 5); printf(" ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝\n");
    system("pause");
    
}

