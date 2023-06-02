#include "main.h"

#ifndef MAP_SIZE
#define MAPSIZE

#define WIDTH_easy 20
#define HEIGHT_easy 20
#define WIDTH_hard 75
#define HEIGHT_hard 50
#define BOMB_COUNT 6
#endif 

#ifndef KEY_CODE
#define KEY_CODE



#define C_UP 0
#define C_DOWN 1
#define C_LEFT 2
#define C_RIGHT 3
#define C_SUBMIT 4

#endif // !KEY_CODE

int gameOver;  // 게임 종료 여부
int x, y, fruitX, fruitY, bombX, bombY, score;  // 뱀, 과일, 폭탄의 위치 및 점수
int bombX_hard[BOMB_COUNT], bombY_hard[BOMB_COUNT]; // 폭탄 개수 조절
int tailX[100], tailY[100];  // 뱀의 꼬리 위치
int nTail;  // 뱀의 꼬리 길이


enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };  // 이동 방향
enum eDirection dir;  // 현재 이동 방향

void Setup_easy();
void Setup_hard();
void Draw_easy();
void Draw_hard();
void Input();
void Logic_easy();
void Logic_hard();
int getkeydown();
int keycontrol();
void title();
void infodraw();
int menudraw();
int maplistdraw();
void drawgameover();