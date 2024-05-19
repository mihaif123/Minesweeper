#include <stdio.h>
#include <stdlib.h>
#include "minesweeper.h"
#include <time.h>
#include <string.h>
#include <windows.h>


typedef struct
{
    char cmd;
    char col;
    int row;
} command;

int main()
{
    int h,w,nr_bombs;
    printf("h = ");
    scanf("%d",&h);
    printf("w = ");
    scanf("%d",&w);

    char* cols = calloc(h*w, sizeof(char));
    int* rows = calloc(h*w, sizeof(int));
    command* c = (command*)malloc(sizeof(command) * 100);

    char t[101][52];
    for(int i=0; i<h; i++)
        for(int j=0; j<w; j++)
            t[i][j]='.';

    

    printf("Nr bombe = ");
    scanf("%d",&nr_bombs);

    char** s = init_state(h,w);

    

    printf("\n");
    int game_over = 1;
    int k = 0;
    random_bombs(h,w,rows,cols,nr_bombs,c);

    create(nr_bombs,cols,rows,h,w,t);

    printf("\n");

    while(game_over)
    {
        player_view(h,w,t,s);
        if(comanda(h,w,t,s,c,k) == -1){
            puts("AI PIERDUT");
            break;}
            if(verificare_game_over(nr_bombs,h,w,t,s))
            game_over = 0;
            system("cls");
    }
 if(verificare_game_over(nr_bombs,h,w,t,s))
            puts("AI CASTIGAT");
            print(h,w,t);

    for(int i=0; i<h; i++)
        free(s[i]);
    free(s);
    free(cols);
    free(rows);

}
