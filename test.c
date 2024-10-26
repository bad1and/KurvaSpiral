#include <stdio.h>
#include <ncurses.h>

#define MAX_SIZE 11

// Заполнение по часовой стрелке снаружи
void fillSpiralClockwise(int m, int n, int matrix[MAX_SIZE][MAX_SIZE]) {
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
void fillSpiralCounterClockwise(int m, int n, int matrix[MAX_SIZE][MAX_SIZE]) {
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
void fillSpiralInsideClockwise(int m, int n, int matrix[MAX_SIZE][MAX_SIZE]) {
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
void fillSpiralInsideCounterClockwise(int m, int n, int matrix[MAX_SIZE][MAX_SIZE]) {
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


void printMatrix(int m, int n, int matrix[MAX_SIZE][MAX_SIZE]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printw("%4d", matrix[i][j]);
        }
        printw("\n");
    }
}

int main() {
    initscr();
    int m, n, choice;
    clear();

    printw("Enter the number of rows (1-11): ");
    scanw("%d", &m);
    clear();
    printw("Enter the number of columns (1-11): ");
    scanw("%d", &n);
    clear();

    if (m < 1 || m > 11 || n < 1 || n > 11) {
        printw("Matrix size out of bounds.\n");
        getch();
        endwin();
        return 1;
    }

    printw("Choose the type of spiral:\n");
    printw("1 - Clockwise from outside\n");
    printw("2 - Counterclockwise from outside\n");
    printw("3 - Clockwise from inside\n");
    printw("4 - Counterclockwise from inside\n");
    scanw("%d", &choice);
    clear();

    int matrix[MAX_SIZE][MAX_SIZE] = {0};

    switch (choice) {
        case 1:
            fillSpiralClockwise(m, n, matrix);
            break;
        case 2:
            fillSpiralCounterClockwise(m, n, matrix);
            break;
        case 3:
            fillSpiralInsideClockwise(m, n, matrix);
            break;
        case 4:
            fillSpiralInsideCounterClockwise(m, n, matrix);
            break;
        default:
            printw("Invalid choice.\n");
            getch();
            endwin();
            return 1;
    }

    printMatrix(m, n, matrix);
    getch();
    endwin();

    return 0;
}
