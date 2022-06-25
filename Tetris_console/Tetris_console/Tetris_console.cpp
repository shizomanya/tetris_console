#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <ctime>

class Screen {
public:
    int score = 0;
    char OutLine[1000] = "", OutLine1[1000] = "", OutLine2[1000] = "";
    int Cash[20][10] = { {0,0,0,0,0,0,0,0,0,0}, //Экран консоли
                         {0 ,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
    };

    void Draw() { //Верхние раницы рамки
        printf("\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF  SCORE:%d\n", score);
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 10; j++) {
                if (Cash[i][j] > 0) { //Границы фигуры
                    strcat_s(OutLine, "\xC9\xCD\xCD\xCD\xBB");
                    strcat_s(OutLine1, "\xBA\xB0\xB0\xB0\xBA");
                    strcat_s(OutLine2, "\xC8\xCD\xCD\xCD\xBC");
                }
                else {
                    strcat_s(OutLine, "     ");
                    strcat_s(OutLine1, "     ");
                    strcat_s(OutLine2, "     ");
                }
            }
            printf("\xB3%s\xB3\n\xB3%s\xB3\n\xB3%s\xB3\n", OutLine, OutLine1, OutLine2);

            OutLine[0] = 0; OutLine1[0] = 0; OutLine2[0] = 0;
        }
        printf("\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9"); 
    } //Нижние раницы рамки

    void SetFig(int mass[4][2]) { //создаем фигуру
        for (int i = 0; i < 4; i++)
        {
            Cash[mass[i][1]][mass[i][0]] = 1;
        }
    }

    void DeleteFig(int mass[4][2]) { //удаляем фигуру
        for (int i = 0; i < 4; i++)
        {
            Cash[mass[i][1]][mass[i][0]] = 0;
        }
    }

    void MoveFig(int mass[4][2], int dx = 0, int dy = 0) {
        int massiv2[4][2];

        //границы движения фигуры
        for (int i = 0; i < 4; i++) {
            if (mass[i][0] + dx >= 10 || mass[i][0] + dx < 0) {
                return;
            }
            if (mass[i][1] + dy >= 20) {
                return;
            }
        }

        //если не вышел то пробуем удалить
        DeleteFig(mass);
        //проверяем есть ли на новых координатах место
        for (int i = 0; i < 4; i++) {

            if (Cash[mass[i][1] + dy][mass[i][0] + dx] == 1) {
                SetFig(mass);
                return;
            }
        }

        //ставим новые координаты
        for (int i = 0; i < 4; i++)
        {
            mass[i][0] = dx + mass[i][0];
            mass[i][1] = dy + mass[i][1];
        }
        //рисуем
        SetFig(mass);
    }


    bool MoveDown(int mass[4][2]) { 
        DeleteFig(mass);
        //границы
        for (int i = 0; i < 4; i++) {
            if (mass[i][1] + 1 >= 20) {
                SetFig(mass);
                return false;
            }
            else if (Cash[mass[i][1] + 1][mass[i][0]] == 1) {
                SetFig(mass);
                return false;
            }
        }
        SetFig(mass);
        return true;
    }

    void Rotaite(int mass[4][2]) { //разворот фигуры
        DeleteFig(mass);
        int RotateX = mass[1][0]; // указываем центр вращения для X
        int RotateY = mass[1][1]; // указываем центр вращения для Y

        for (int i = 0; i < 4; i++)
        {
            int x = mass[i][1] - RotateY; // y - y0
            int y = mass[i][0] - RotateX; // x - x0
            if (Cash[RotateY + y][RotateX - x] == 1) {
                SetFig(mass);
                return;
            }
            //границы
            for (int i = 0; i < 4; i++) {
                if (RotateX - x >= 10 || RotateX - x < 0) {
                    return;
                }
                if (RotateY + y >= 20) {
                    return;
                }
            }
        }

        for (int i = 0; i < 4; i++)
        {
            int x = mass[i][1] - RotateY; // y - y0
            int y = mass[i][0] - RotateX; // x - x0
            mass[i][1] = RotateY + y;
            mass[i][0] = RotateX - x;
        }
    }

    bool CheckLine(int mass[4][2]) { //удаление заполненной линии 

        for (int i = 0; i < 4; i++) {
            if (Cash[mass[i][1]][mass[i][0]] == 1) {
                return false;
            }
        }


        int lineF = 0;

        for (int i = 0; i < 20; i++) {
            lineF = 0;

            for (int j = 0; j < 10; j++) {
                if (Cash[i][j] == 1) {
                    lineF += 1;
                }
            }

            if (lineF == 10) {
                score += 100;
                for (int g = 0; g < 10; g++) { //занулили линию
                    Cash[i][g] = 1;
                }

                for (int a = i; a > 1; a--) { //смещаем на 1
                    for (int f = 0; f < 10; f++) {
                        Cash[a][f] = Cash[a - 1][f];
                        Cash[a - 1][f] = 0;
                    }
                }
            }
        }
        return true;
    }


    bool EndGame() { //конец игры

        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 10; j++) {
                Cash[i][j] = 0;
            }
        }
        system("cls");
        int i = 6;
        while (i > 0) {
            printf("\n");
            i--;
        }
        printf("        GAME OVER\n");
        printf("        SCORE: %d", score);
        Sleep(4000);
        score = 0;
        system("cls");
        return true;
    }
};

class Figure {
    int figures[7][4] =
    {
        1,3,5,7, // I
        2,4,5,7, // S
        3,5,4,6, // Z
        3,5,4,7, // T
        2,3,5,7, // L
        3,5,7,6, // J
        2,3,4,5, // O
    };

public:
    void NewFig(int massi[4][2]) { // спавн случайной фигуры
        int n = rand() % 7;
        for (int i = 0; i < 4; i++)
        {
            massi[i][0] = 3 + figures[n][i] % 2;
            massi[i][1] = -1 + figures[n][i] / 2;
        }
    }
};

class GameLogic {
    int dx = 0, dy = 0;
    Screen* scn = new Screen;
    Figure* figura = new Figure;
    int massi[4][2] = { 0 };
    int start = 0;

public:

    GameLogic() {
        figura->NewFig(massi);//создаем новую фигуру
        start = clock();
    }

    bool Game() {
        while (1) {
            //управление
            if (GetAsyncKeyState(VK_LEFT)) { 
                dx += -1; 
            }
            if (GetAsyncKeyState(VK_RIGHT)) { 
                dx += 1; 
            }
            if (GetAsyncKeyState(VK_DOWN)) { 
                dy += 1; 
            }

            scn->MoveFig(massi, dx, dy);
            scn->Draw();
            Sleep(100);
            if (GetAsyncKeyState(VK_UP)) { 
                scn->Rotaite(massi); 
            }

            system("cls"); //очищаем экран консоли
            dx = 0;
            dy = 0;

            if (!scn->MoveDown(massi) && (clock() - start) >= 550) { //проверка на проигрыш
                figura->NewFig(massi);

                if (!scn->CheckLine(massi)) {
                    scn->EndGame();
                }
            }

            if ((clock() - start) >= 550) { //таймер на новую фигуру

                start = clock();
                scn->MoveFig(massi, dx, dy + 1);
            }

            if (GetAsyncKeyState(VK_ESCAPE)) { //офф игры
                return false;
            }
        }
    }
};

int main()
{
    system("mode con cols=67 lines=63");
    system("TITLE Сonsole tetris in С++");

    GameLogic* game = new GameLogic();
    game->Game();
}