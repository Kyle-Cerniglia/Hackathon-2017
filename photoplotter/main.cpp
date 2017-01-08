#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <math.h>

#define RAD 0.01745

using namespace std;

FILE* read = NULL;
FILE* write = NULL;

int x = 0;
int y = 0;
int degree = 0;
int range = 0;
int range_a[4][142];//x, y, degree, range
int photogrid[400][200];
int i = 0;

int main()
{
    //File open
    read = fopen("rangdata.txt", "r");
    if(read == NULL){
        printf("Read error");
        return 0;
    }

    //File read
    i = 0;
    while(i < 142){
        fscanf(read, "%d", &range_a[0][i]);
        fscanf(read, ":%d", &range_a[1][i]);
        fscanf(read, ":%d", &range_a[2][i]);
        fscanf(read, ":%d", &range_a[3][i]);
        fscanf(read, ";\n");
        i++;
    }
    i = 0;
    fclose(read);

    //Point generation
    while(i < 71){
    printf("ID: %d\n", i);
        range_a[2][i] = 71 - range_a[2][i];
        x = range_a[3][i] * sin(RAD * range_a[2][i]);
        y = range_a[3][i] * cos(RAD * range_a[2][i]);
        photogrid[x + 200][200 - y] = 1;
        i++;
    }
    i = 0;

    photogrid[400][200 - range_a[2][71]] = 1;

    i = 72;
    while(i < 142){
        range_a[2][i] = range_a[2][i] - 71;
        x = range_a[3][i] * sin(RAD * range_a[2][i]);
        y = range_a[3][i] * cos(RAD * range_a[2][i]);
        photogrid[200 - x][200 - y] = 1;
        i++;
    }
    i = 0;
/*
    //Photo print
    x = 0;
    y = 0;
    while(y < 300){
        while(x < 300){
            if(photogrid[x][y] == 1){
                printf(".");
                i++;
            }
            else{
                printf(" ");
            }
            x++;
        }
        x = 0;
        printf("\n");
        y++;
    }
    y = 0;
*/

    //Photo write

    write = fopen("processed.txt", "w");
    if(write == NULL){
        printf("Write error\n");
        return 0;
    }

    x = 0;
    y = 0;
    while(y < 200){
        while(x < 400){
            if(photogrid[x][y] == 1){
                fprintf(write, "O");
            }
            else{
                fprintf(write, " ");
            }
            x++;
        }
        x = 0;
        fprintf(write, "\n");
        y++;
    }
    y = 0;
    fclose(write);
    return 0;
}
