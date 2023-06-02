#include "game.h"
#include "main.h"

void HideCursor()
{
    system(" mode  con lines=65   cols=145 ");
    system("title SNAKE GMAE. By Lee Gyu Han");
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);  // 콘솔 창에서 커서 숨기기
}

void gotoxy(int x, int y) {
    HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); //콘솔 핸들 가져오기
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(ConsoleHandle, pos);
}