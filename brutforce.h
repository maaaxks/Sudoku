#include <stdio.h>
#include <unistd.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//Цвета для чисел, визуализация все-таки
void set_text_color(int color) {
    printf("\033[%dm", color);  
}

void reset_text_color() {
    printf("\033[0m");  
}

void display_number(int num, int is_initial) {
    if (is_initial) {
        set_text_color(34); //Синий для начальных
    } else {
        set_text_color(32); //Зеленый для добавляемых
    }
    printf("%d ", num);
    reset_text_color(); 
}


//Проверка на уникальность для числа  
int is_uniqueb(int** field, int row, int col, int num, int sizef) {
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
//Перемещение курсора по ячейкам судоку
void set_matrix_position(int row, int col) {
    printf("\033[%d;%dH", row + 1 , (col + 1) * 2 - 1 );
}


//Основная функ
int brutforce(int** field, int size){
    int row = -1, col = -1;
    int empty_found = 0;
    
    //Поиск первой пустой ячейки судоко для замены ее числом
    for (int i = 0; i < size && !empty_found; i++) {
        for (int j = 0; j < size && !empty_found; j++) {
            if (field[i][j] == 0) {
                row = i;
                col = j;
                empty_found = 1;
            }
        }
    }

    //Если нет пустых ячеек значит судоку решено
    if (!empty_found) return 1;

    //Надо пробовать все возможные варианты, используется рекурсия для возможного отката, если прога защла у тупик
    for (int num = 1; num <= size; num++) {
        if (is_uniqueb(field, row, col, num, size)) {
            *(*(field+row)+col) = num; 
            set_matrix_position(row, col);
            display_number(num, 0);
            fflush(stdout);
            sleep(1);
            if (brutforce(field, size)) {
                return 1;  
            }

            //Если тупик, откатываемся
            *(*(field+row)+col) = 0;
            set_matrix_position(row, col);
            printf(". "); 
            fflush(stdout);
            sleep(1);
        }
    }
    return 0; system("cls"); printf("Unreal sudoku,bro, sry. Rerun code"); 
}
/*  //Фунция для определения числа, которое будет заспиано в пустую ячейку
    int brutnum(int** field, int size, int row, int col) {
        if (*(*(field + row) + col) != 0) {  
            return *(*(field + row) + col);}
        else{
            for (int num = 1; num <= size; num++) { 
                if (is_uniqueb(field, row, col, num, size)) {  
                    return num;  
                }
            }}
        return 0;
    } 
    for (int i=0;i<size;i++){
        for (int j=0;j<size;j++){
            *(*(field+i)+j) =brutnum(field, size, i, j);
            if (*(*(field+i)+j)==0){break;break;printf("Unreal sudoku, rerun code(");}
            set_matrix_position(i, j);
            printf("%d", *(*(field+i)+j));
            fflush(stdout);
            sleep(1);
        }
        }
}
*/
