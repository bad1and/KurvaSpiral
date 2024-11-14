#include <locale.h>
#include <stdio.h>
#include <ncurses.h>


int position = 0;
int n_button;

void menu() {
    printw("%s", "Spiralka by Tikhanov Oleg\n");
    printw("%s", "ver 1.0\n");
    printw("%s", "\n");
    printw("%s", "Перед использованием прочитайте инструкцию 6 п.\n");
    printw("%s", "-----------------\n");
    printw("%s", "\n");

    char screen[8][70] = {
        "1. Играть",
        "2. Спираль по часовой стрелке",
        "3. Спираль против часовой",
        "4. Спираль изнутри по часовой",
        "5. Спираль изнутри против часовой",
        "6. Инструкция",
        "7. Выход",
        "",
    };

    for (int i = 0; i <= 7; ++i) {
        if (i == position) {
            printw("%s  %s\n", screen[i], "<---");
        } else {
            printw("%s\n", screen[i]);
        }
    }
}

void instruction (){
    printw("%s", "Spiralka by Tikhanov Oleg\n");
    printw("%s", "ver 0.3\n");
    printw("%s", "\n");
    printw("%s", "Перед использованием прочитайте инструкцию 6 п.\n");
    printw("%s", "-------------------------------------------------------\n");
    printw("%s", "\n");
    printw("%s", "Используйте стрелки для перемещения по меню.\n");
    printw("%s", "Вы - $\n");
    printw("%s", "Введите значения (ширину и высоту спирали)\n");
    printw("%s", "Выберите пункт интересующий вас.\n");
}

//по часовой стрелке снаружи
void po_chas(int m, int n, int matrix[11][11]) {
    int top = 0, bottom = m - 1, left = 0, right = n - 1;
    int num = 1;

    while (top <= bottom && left <= right) {
        for (int i = left; i <= right; i++) matrix[top][i] = num++;
        top++;
        for (int i = top; i <= bottom; i++) matrix[i][right] = num++;
        right--;
        if (top <= bottom) for (int i = right; i >= left; i--) matrix[bottom][i] = num++;
        bottom--;
        if (left <= right) for (int i = bottom; i >= top; i--) matrix[i][left] = num++;
        left++;
    }
}

//против часовой стрелке снаружи
void prot_chas(int m, int n, int matrix[11][11]) {
    int top = 0, bottom = m - 1, left = 0, right = n - 1;
    int num = 1;

    while (top <= bottom && left <= right) {
        for (int i = top; i <= bottom; i++) matrix[i][left] = num++;
        left++;
        for (int i = left; i <= right; i++) matrix[bottom][i] = num++;
        bottom--;
        if (left <= right) for (int i = bottom; i >= top; i--) matrix[i][right] = num++;
        right--;
        if (top <= bottom) for (int i = right; i >= left; i--) matrix[top][i] = num++;
        top++;
    }
}

//по часовой стрелке внутри
void in_po_chas(int m, int n, int matrix[11][11]) {
    int top = 0, bottom = m - 1, left = 0, right = n - 1;
    int maxis = m*n;

    while (top <= bottom && left <= right) {
        for (int i = top; i <= bottom; i++) matrix[i][left] = maxis--;
        left++;
        for (int i = left; i <= right; i++) matrix[bottom][i] = maxis--;
        bottom--;
        if (left <= right) for (int i = bottom; i >= top; i--) matrix[i][right] = maxis--;
        right--;
        if (top <= bottom) for (int i = right; i >= left; i--) matrix[top][i] = maxis--;
        top++;
    }
}

//против часовой стрелке снаружи
void in_prot_chas(int m, int n, int matrix[11][11]) {
    int maxis = m*n;
    int top = 0, bottom = m - 1, left = 0, right = n - 1;

    while (top <= bottom && left <= right) {
        for (int i = left; i <= right; i++) matrix[top][i] = maxis--;
        top++;
        for (int i = top; i <= bottom; i++) matrix[i][right] = maxis--;
        right--;
        if (top <= bottom) for (int i = right; i >= left; i--) matrix[bottom][i] = maxis--;
        bottom--;
        if (left <= right) for (int i = bottom; i >= top; i--) matrix[i][left] = maxis--;
        left++;
    }
}

//вывод
void print_done(int m, int n, int matrix[11][11]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printw("%4d", matrix[i][j]);
        }
        printw("\n");
    }
}



int main() {
    setlocale(LC_ALL, "");
    initscr();
    int m = 0, n = 0;
    int matrix[11][11] = {0};


    while (true) {
        menu();
        n_button = getch();

        //buttonЫ
        if (n_button == 27) {
            n_button = getch();
            if (n_button == 91) {
                n_button = getch();
                if (n_button == 65) {
                    position = position - 1;
                    if (position < 0) {
                        position = 6;
                    }
                } else if (n_button == 66) {
                    position = position + 1;
                    if (position > 6) {
                        position = 0;
                    }
                }
            }
        }

       //MAIN_Ы
        if ((position == 0 && n_button == 10) || n_button == 49) {
            clear();
            while (true) {
                printw("Введите количество столбцов (1-11): ");
                scanw("%d", &m);
                if (m < 1 || m > 11) {
                    clear();
                    printw("Неверные значения!\n");
                } else {
                    break;
                }
            }

            clear();
            while (true) {
                printw("Введите количество строк (1-11): ");
                scanw("%d", &n);
                if (n < 1 || n > 11) {
                    clear();
                    printw("Неверные значения!\n");
                } else {
                    break;
                }
            }
        }

        //По часовой
        if ((position == 1 && n_button == 10) || n_button == 50) {
            clear();
            if (m == 0 || n == 0 || (m == 0 && n == 0)) {
                printw("\nВы ничего не ввели...");
                getch();
            }else {
                po_chas(m, n, matrix);
                print_done(m, n, matrix);
                printw("\nДля выхода нажмите любую кнопку...");
                getch();
            }
        }

        //Против часовой
        if ((position == 2 && n_button == 10) || n_button == 51) {
            clear();
            if (m == 0 || n == 0 || (m == 0 && n == 0)) {
                printw("\nВы ничего не ввели...");
                getch();
            }else {
                prot_chas(m, n, matrix);
                print_done(m, n, matrix);
                printw("\nДля выхода нажмите любую кнопку...");
                getch();
            }
        }

        //По часовой внутри
        if ((position == 3 && n_button == 10) || n_button == 52) {
            clear();
            if (m == 0 || n == 0 || (m == 0 && n == 0)) {
                printw("\nВы ничего не ввели...");
                getch();
            }else {
                in_po_chas(m, n, matrix);
                print_done(m, n, matrix);
                printw("\nДля выхода нажмите любую кнопку...");
                getch();
            }
        }

        //Против часовой внутри
        if ((position == 4 && n_button == 10) || n_button == 53) {
            clear();
            if (m == 0 || n == 0 || (m == 0 && n == 0)) {
                printw("\nВы ничего не ввели...");
                getch();
            }else {
                in_prot_chas(m, n, matrix);
                print_done(m, n, matrix);
                printw("\nДля выхода нажмите любую кнопку...");
                getch();
            }
        }

        //Instruction
        if ((position == 5 && n_button == 10) || n_button == 54) {
            clear();
            instruction();
            n_button = getch();
            if (n_button != 27) {
                clear();
                menu();
            }
        }


        if ((position == 6 && n_button == 10) || n_button == 55) {
            break;
        }

        clear();
        endwin();
    }
    return 0;
}