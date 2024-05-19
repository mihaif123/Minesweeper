#include <stdio.h>
#include <stdlib.h>
#include "minesweeper.h"

typedef struct
{
    int row;
    char col;
} random;

typedef struct
{
    char cmd;
    char col;
    int row;
} command;

char** init_state(int h, int w)
{
    char** s = (char**)malloc(h * sizeof(char*));
    for(int i=0; i<h; i++)
    {
        s[i]=(char*)malloc(w * sizeof(char));
        for(int j=0; j<w; j++)
            s[i][j]='?';
    }
    return s;
}
int comanda(int h, int w,char t[101][52],char** s)
{
    char str[1000];
    command c[100];
    puts("Comanda: ");
    gets(str);
    str[strlen(str)  + 1] = '\0';

    str[strlen(str)] = ' ';

    int str_length = strlen(str)-1;
    int i = 0;
    int k = 0;
    while(i < str_length)
    {
        while(str[i] == ' ')    i++;

        if(str[i] != '!')
        {
            c[k].cmd = '.';
            c[k].col = str[i];
            i++;
        }
        else
        {
            c[k].cmd = '!';
            c[k].col = str[i+1];
            i+=2;
        }

        c[k].row = 0;

        while(i<str_length && isdigit(str[i]))
        {
            c[k].row = c[k].row * 10 + (str[i] - '0');

            i++;
        }

        k++;

    }


    int ret = 0;
    for(int i=0; i<k; i++)
        if(c[i].cmd == '.' && c[i].col >= 'A' && c[i].col <= 'Z')
            ret = discover(c[i].row-1,c[i].col-65,h,w,t,s);
        else if (c[i].cmd == '.' && c[i].col >= 'a' && c[i].col <= 'z')
            ret = discover(c[i].row-1,c[i].col-71,h,w,t,s);
        else if(c[i].cmd == '!' && c[i].col >= 'A' && c[i].col <= 'Z')
            mark(c[i].row-1,c[i].col-65,h,w,s);
        else if (c[i].cmd == '!' && c[i].col >= 'a' && c[i].col <= 'z')
            mark(c[i].row-1,c[i].col-71,h,w,s);
    return ret;

}

void random_bombs(int h,int w, int rows[],char cols[],int nr_bombs)
{
    srand(time(NULL));
    random r[101 * 51];
    int k=0;
    for(int i=0; i<nr_bombs; i++)
    {
        rows[i]=rand()%h+1;
        if(w<26)
            cols[i] = 'A' + rand()%(w-1);
        else
            cols[i] = 'A' +rand()%(w+5);
        if(cols[i]>90 && cols[i]<97)
            cols[i]= cols[i] + 7;

        for(int j=0; j<k; j++)
        {
            while(cols[i] == r[j].col && rows[i] == r[j].row)
            {
                j=0;
                rows[i]=rand()%h+1;
                if(w<26)
                    cols[i] = 'A' + rand()%w;
                else
                    cols[i] = 'A' +rand()%(w+6)+1;
                if(cols[i]>90 && cols[i]<97)
                    cols[i]= cols[i] + 7;

            }
        }
        r[k].col = cols[i];
        r[k].row = rows[i];
        k++;
    }

}

void mark(int i, int j, int h, int w, char** s)
{
    if(i>=0 && i<h && j>=0 && j<w)
    {
        if(s[i][j] == '?')
            s[i][j] = '!';
        else if (s[i][j] == '!')
            s[i][j] = '?';
    }
}

void print(int h, int w, char t[101][52])
{
    char k='A';
    int cnt=0;
    printf("   ");
    while(cnt<w)
    {
        printf("%c ",k);
        k++;
        if(k>'Z' && k<'a')
            k='a';
        cnt++;
    }
    printf("\n");
    for(int i=0; i<h; i++)
    {
        printf("%2d ",i+1);
        for(int j=0; j<w; j++)
            printf("%c ",t[i][j]);
        printf(" %d",i+1);
        printf("\n");
    }
    k='A';
    cnt=0;
    printf("   ");
    while(cnt<w)
    {
        printf("%c ",k);
        k++;
        if(k>'Z' && k<'a')
            k='a';
        cnt++;
    }

}

void create(int nr_bombs, char cols[], int rows[], int h, int w, char t[101][52])
{
    const int colj[] = {-1,-1,0,1,1,1,0,-1};
    const int rowi[] = {0,-1,-1,-1,0,1,1,1};

    for(int i=0; i<nr_bombs; i++)
    {
        if(cols[i]>='A' && cols[i]<='Z')
            t[rows[i]-1][cols[i]-65]='X';
        else if (cols[i]>='a' && cols[i]<='z')
            t[rows[i]-1][cols[i]-71]='X';
    }
    int nr_vecini;
    for(int i=0; i<h; i++)
    {
        for(int j=0; j<w; j++)
        {
            nr_vecini=0;
            if(t[i][j] != 'X')
            {
                for(int k=0; k<8; k++)
                    if(i+rowi[k] >= 0 && i+rowi[k] < h && j+colj[k] >=0 && j+colj[k] <w && t[i+rowi[k]][j+colj[k]] == 'X')
                        nr_vecini++;

            }
            if(nr_vecini != 0)
                t[i][j]='0'+nr_vecini;
        }
    }
}
void player_view(int h, int w, char t[101][52], char** s)
{
    char k='A';
    int cnt=0;
    printf("   ");
    while(cnt<w)
    {
        printf("%c ",k);
        k++;
        if(k>'Z' && k<'a')
            k='a';
        cnt++;
    }
    printf("\n");
    for(int i=0; i<h; i++)
    {
        printf("%2d ",i+1);
        for(int j=0; j<w; j++)
        {
            if(s[i][j] == '.' && isdigit(t[i][j]))
                printf("%c ",t[i][j]);
            else
                printf("%c ",s[i][j]);
        }
        printf(" %d",i+1);
        printf("\n");
    }
    k='A';
    cnt=0;
    printf("   ");
    while(cnt<w)
    {
        printf("%c ",k);
        k++;
        if(k>'Z' && k<'a')
            k='a';
        cnt++;
    }
    printf("\n");
}

int discover(int i, int j, int h, int w, char t[101][52], char** s)
{

    const int colj[]= {-1,-1,0,1,1,1,0,-1};
    const int rowi[]= {0,-1,-1,-1,0,1,1,1};

    if(i < 0 || i >= h || j < 0 || j >= w)
        return -2;
    if(t[i][j] == 'X')
        return -1;
    if(s[i][j] != '?')
        return 0;
    if(isdigit(t[i][j]))
    {
        s[i][j] = '.';
        return 1;
    }
    if(t[i][j] == '.')
    {
        s[i][j] = '.';
        for(int k=0; k<8; k++)
        {
            int i1= i + rowi[k];
            int j1= j + colj[k];
            discover(i1,j1,h,w,t,s);
        }
        return 2;
    }
}

int verificare_game_over(int nr_bombs,int h,int w,char t[101][52],char** s)
{
    int sum=0;
    for(int i=0; i<h; i++)
        for(int j=0; j<w; j++)
            if((s[i][j] == '?' || s[i][j]== '!'))
                sum++;
    return sum == nr_bombs;

}

