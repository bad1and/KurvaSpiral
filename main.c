#include <locale.h>
#include <stdio.h>
#include <ncurses.h>

#define MAX_SIZE 11


int position = 0;
int n_button;
int choice;

void instruction (){
    printw("%s", "-------------------------------------------------------\n");
    printw("%s", "Используйте стрелки для перемещения\n");
    printw("%s", "Вы - $\n");
    printw("%s", "Игра начинается с крестика (Х)\n");
    printw("%s", "X - установка крестика, O - установка нолика\n");
    printw("%s", "DELETE - удалить значение в клетке\n");
}

void menu() {
    printw("%s", "KrestikiNoliki by Tikhanov Oleg\n");
    printw("%s", "ver 0.1\n");
    printw("%s", "\n");
    printw("%s", "Перед использованием прочитайте инструкцию 2 п.\n");
    printw("%s", "-----------------\n");
    printw("%s", "\n");

    char screen[4][35] = {
        "1. Играть",
        "2. Инструкция",
        "3. Выход",
        "",
    };

    for (int i = 0; i <= 3; ++i) {
        if (i == position) {
            printw("%s  %s\n", screen[i], "<---");
        } else {
            printw("%s\n", screen[i]);
        }
    }
}


// Заполнение по часовой стрелке снаружи
void po_chas(int m, int n, int matrix[MAX_SIZE][MAX_SIZE]) {
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

// Заполнение против часовой стрелки снаружи
void prot_chas(int m, int n, int matrix[MAX_SIZE][MAX_SIZE]) {
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

// Заполнение по часовой стрелке из центра
void in_po_chas(int m, int n, int matrix[MAX_SIZE][MAX_SIZE]) {
    int centerRow = m / 2, centerCol = n / 2;
    int top = centerRow, bottom = centerRow, left = centerCol, right = centerCol;
    int num = 1;

    while (top >= 0 && bottom < m && left >= 0 && right < n) {
        for (int i = left; i <= right; i++) matrix[top][i] = num++;  // вправо
        for (int i = top + 1; i <= bottom; i++) matrix[i][right] = num++;  // вниз
        for (int i = right - 1; i >= left; i--) matrix[bottom][i] = num++;  // влево
        for (int i = bottom - 1; i > top; i--) matrix[i][left] = num++;  // вверх

        // Расширяем границы для следующего витка спирали
        top--; bottom++; left--; right++;
    }
}

// Заполнение против часовой стрелки из центра
void in_prot_chas(int m, int n, int matrix[MAX_SIZE][MAX_SIZE]) {
    int centerRow = m / 2, centerCol = n / 2;
    int top = centerRow, bottom = centerRow, left = centerCol, right = centerCol;
    int num = 1;

    while (top >= 0 && bottom < m && left >= 0 && right < n) {
        for (int i = top; i <= bottom; i++) matrix[i][left] = num++;  // вниз
        for (int i = left + 1; i <= right; i++) matrix[bottom][i] = num++;  // вправо
        for (int i = bottom - 1; i >= top; i--) matrix[i][right] = num++;  // вверх
        for (int i = right - 1; i > left; i--) matrix[top][i] = num++;  // влево

        // Расширяем границы для следующего витка спирали
        top--; bottom++; left--; right++;
    }
}

void print_done(int m, int n, int matrix[MAX_SIZE][MAX_SIZE]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printw("%4d", matrix[i][j]);
        }
        printw("\n");
    }
}


void mini_instruction() {
    printw("Выберите тип спирали spiral:\n");
    printw("1 - Снаружи по часовой\n");
    printw("2 - Снаружи против часовой\n");
    printw("3 - Изнутри по часовой\n");
    printw("4 - Изнутри против часовой\n");
    scanw("%d", &choice);
    clear();
}


int main() {
    setlocale(LC_ALL, "");
    initscr();
    int m, n;

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
                        position = 2;
                    }
                } else if (n_button == 66) {
                    position = position + 1;
                    if (position > 2) {
                        position = 0;
                    }
                }
            }
        }

       //MAIN_Ы
        if ((position == 0 && n_button == 10)) {
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

            clear();
            mini_instruction();

            int matrix[MAX_SIZE][MAX_SIZE] = {0};

            switch (choice) {
                case 1:
                    po_chas(m, n, matrix);
                break;
                case 2:
                    prot_chas(m, n, matrix);
                break;
                case 3:
                    in_po_chas(m, n, matrix);
                break;
                case 4:
                    in_prot_chas(m, n, matrix);
                break;
                default:
                    printw("Invalid choice.\n");
                getch();
                endwin();
                return 1;
            }

            print_done(m, n, matrix);
            getch();
        }

        //Instruction
        if ((position == 1 && n_button == 10)) {
            clear();
            instruction();
            n_button = getch();
            if (n_button != 27) {
                clear();
                menu();
            }
        }


        if ((position == 2 && n_button == 10) || n_button == 27) {
            break;
        }

        clear();
        endwin();
    }
    return 0;
}