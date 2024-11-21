#include <stdio.h>
#include <unistd.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#define EMPTY_CELL 0

void set_matrix_positionh(int row, int col) {
    printf("\033[%d;%dH", row + 1, (col * 3) + 2);  // Каретка между [ и ]
}

//Проверка на уникальность для числа  
int is_uniqueh(int** field, int row, int col, int num, int sizef) {
    for (int i = 0; i < sizef; ++i) {
        if (*(*(field + i) + col) == num) return 0;
    }
    for (int j = 0; j < sizef; ++j) {
        if (*(*(field + row) + j) == num) return 0;
    }
    int sqrtSize = (int)sqrt(sizef);
    int boxRow = row - row % sqrtSize;
    int boxCol = col - col % sqrtSize;
    for (int i = 0; i < sqrtSize; i++) {
        for (int j = 0; j < sqrtSize; j++) {
            if (*(*(field + i + boxRow) + j + boxCol) == num) return 0;
        }
    }
    return 1;
}



// Перемещение курсора в конец терминала
void move_to_bottom(int size) {
    printf("\033[%d;1H", size + 2);  // Переместить курсор под поле
}

// Отображение клетки (с курсором или без)
void display_cell(int** field, int row, int col, int is_cursor) {
    if (col == 0) {
        printf(" ");  // Добавляем пробел перед первой клеткой строки
    }
    set_matrix_positionh(row, col);

    if (is_cursor) {
        if (*(*(field+row)+col) == 0) {
            printf("[ ]");
            // Установить каретку между квадратными скобками
            printf("\033[%d;%dH", row + 1, (col * 3) + 3);  
        } else {
            printf("[%d]", *(*(field+row)+col));
            // Установить каретку между квадратными скобками
            printf("\033[%d;%dH", row + 1, (col * 3) + 3);
        }
    } else {
        if (*(*(field+row)+col) == 0) {
            printf(".  ");
        } else {
            printf("%d  ", *(*(field+row)+col));
        }
    }
    fflush(stdout);  // Обновляем вывод
}


// Очистка клетки от курсора
void clear_cell(int** field, int row, int col) {
    set_matrix_positionh(row, col);  // Устанавливаем каретку на начало клетки
    if (*(*(field+row)+col) == 0) {
        printf(" . ");  // Замещаем на пустую клетку
    } else {
        printf(" %d ", *(*(field+row)+col));  // Замещаем на число
    }
    fflush(stdout);  // Обновляем вывод
}


// Отображение всего поля (для инициализации или обновления)
void display_field(int** field, int size, int cursor_row, int cursor_col) {
    for (int i = 0; i < size; i++) {
        printf(" ");  // Пробел перед каждой строкой
        for (int j = 0; j < size; j++) {
            if (i == cursor_row && j == cursor_col) {
                display_cell(field, i, j, 1);  // Отображение клетки с курсором
            } else {
                display_cell(field, i, j, 0);  // Обычная клетка
            }
        }
        printf("\n");
    }
}

// Перемещение курсора
void move_cursor(int** field, int size, int* cursor_row, int* cursor_col, char direction) {
    clear_cell(field, *cursor_row, *cursor_col);  // Очистить текущую клетку от курсора

    if (direction == 'w' && *cursor_row > 0) (*cursor_row)--;  // Вверх
    if (direction == 's' && *cursor_row < size - 1) (*cursor_row)++;  // Вниз
    if (direction == 'a' && *cursor_col > 0) (*cursor_col)--;  // Влево
    if (direction == 'd' && *cursor_col < size - 1) (*cursor_col)++;  // Вправо
    display_cell(field, *cursor_row, *cursor_col, 1);  // Отобразить новую позицию курсора
}

// Проверка завершенности судоку
int is_sudoku_solved(int** field, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (*(*(field+i)+j) == 0 || !is_uniqueh(field, i, j, field[i][j], size)) {
                return 0;  // Найдена пустая клетка или некорректное значение
            }
        }
    }
    return 1;  // Судоку решено
}

// Изменение значения клетки (+проверка уникальности)
void change_value(int** field, int cursor_row, int cursor_col, int value, int size) {
    if (is_uniqueh(field, cursor_row, cursor_col, value, size)) {
        *(*(field+cursor_row)+cursor_col) = value;
        clear_cell(field, cursor_row, cursor_col);  // Очистить старую клетку
        display_cell(field, cursor_row, cursor_col, 1);  // Отобразить новую клетку
    } else {
        move_to_bottom(size);  // Переместить курсор вниз
        printf("Invalid move!");  // Сообщение об ошибке
        set_matrix_positionh(cursor_row, cursor_col);  // Вернуть курсор
    }
}

void clear_symbol_at(int row, int col) {
    printf("\033[%d;%dH ", row + 1, col + 1);  // Переместить каретку в указанное место и вывести пробел
    fflush(stdout);
}

// Ручной режим
void handmode(int** field, int size) {
    int cursor_row = 0, cursor_col = 0;  // Начальная позиция курсора
    display_field(field, size, cursor_row, cursor_col);  
    clear_symbol_at(0, 0);  // Удаляем лишний символ в первой строке, костыль
    char input;
    while (1) {
        input = getch();  // Получить ввод пользователя

        if (is_sudoku_solved(field, size)) {
            // Очистить экран
            system("cls");  // Windows
            printf("🎉 Congratulations! You solved the Sudoku! 🎉\n");
            break;
        }
        if (input == 'q') {
            break;  // Выход из ручного режима
        }
        if (input == 'w' || input == 'a' || input == 's' || input == 'd') {
            move_cursor(field, size, &cursor_row, &cursor_col, input);  // Переместить курсор
        }
        if (input >= '1' && input <= '9') {
            change_value(field, cursor_row, cursor_col, input - '0', size);  // Изменить значение клетки
        }
        if (input == 'r') {  // Сброс клетки
            *(*(field+cursor_row)+cursor_col)= 0;  // Установить значение 0
            clear_cell(field, cursor_row, cursor_col);  // Очистить клетку
            display_cell(field, cursor_row, cursor_col, 1);  // Отобразить клетку с курсором
        }
        move_to_bottom(size);  // Переместить курсор вниз
        printf("\033[2K");  // Очистить строку
        printf("Use 'w', 'a', 's', 'd' to move, numbers to input, 'r' to reset, 'q' to quit.");
    }
}
