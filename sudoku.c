#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>
#include "brutforce.h"
#include "handsudoku.h"

#define MODE 1

int main() {
    int sizef;
    printf("Which size of field? Enter 4 or 6 or 9 \n");
    scanf("%d", &sizef);
    int** field = (int**)malloc(sizef * sizeof(int*)); 
    for (int i = 0; i<sizef; i++) 
        *(field+i) = (int*)calloc(sizef, sizeof(int));
    
    srand(time(NULL));

    int num_of_rand = (rand() % (sizef * sizef)/2)+1;
    int count = 0;
    while (count < num_of_rand) {
        int row = rand() % sizef;
        int col = rand() % sizef;
        int num = (rand() % sizef)+1;

        if (*(*(field+row)+col) == 0 && is_uniqueb(field, row, col, num, sizef)) {
            *(*(field+row)+col) = num;
            count++;
        }
    }

    system("cls"); 
    for (int i = 0; i<sizef; i++) {
        for (int j = 0; j<sizef; j++) {
            if (*(*(field+i)+j) == 0) {
                printf(". ");
            } else {
                display_number(*(*(field+i)+j), 1); ;
            }
        }
        printf("\n");
    }
    printf("\n");
    sleep(3);
    
    #if MODE==1
    printf("Your mode: hand, gl\n");
    handmode(field, sizef);
    for (int i=0;i<sizef;i++)
        free(*(field+i));
    free(field);
    #elif MODE==2
    printf("Your mode: brute-force, gl for me\n");
    if (brutforce(field, sizef) == 0) {
        system("cls");
        printf("Unreal sudoku, rerun code, please\n");}
    else {
    printf("\n Sudoku solved successfully!\n");
    }
    for (int i=0;i<sizef;i++)
        free(*(field+i));
    free(field);


    #endif
}
