#include "main.h"
#include "game.h"
#include "util.h"

int main()
{
    HideCursor();
    while (1) {
        title();

        int menucode = menudraw();
        if (menucode == 0) {
            int n = maplistdraw();
            //쉬움 난이도
            if (n == 0) {
                system("cls");
                
                srand(time(NULL));  // 난수 초기화
                Setup_easy();  // 게임 설정 초기화
               
                    while (!gameOver)
                    {
                        Draw_easy();  // 화면 그리기
                        Input();  // 플레이어 입력 받기
                        Logic_easy();  // 게임 로직 처리
                        Sleep(70);  // 게임 속도 조절을 위한 딜레이 - 난이도 조절 (쉬움)

                    }
                

                drawgameover();

            }
            // 어려움 난이도
            else if (n == 2) {
                system("cls");
                srand(time(NULL));  // 난수 초기화
                Setup_hard();  // 게임 설정 초기화

                while (!gameOver)
                {
                    Draw_hard();  // 화면 그리기
                    Input();  // 플레이어 입력 받기
                    Logic_hard();  // 게임 로직 처리
                    Sleep(1);  // 게임 속도 조절을 위한 딜레이 - 난이도 조절 (어려움)

                } 

                drawgameover();
                
            }
        }
        else if (menucode == 2) {//게임정보
            infodraw();
        }
        else if (menucode == 4) {//종료
            return 0;
        }
        system("cls");

    }
    return 0;
}
