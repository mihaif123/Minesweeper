#ifndef MINESWEEPER_H_INCLUDED
#define MINESWEEPER_H_INCLUDED

void print(int h, int w, char t[101][52]);

void create(int nr_bombs, char cols[], int rows[], int h, int w, char t[101][52]);

char** init_state(int h, int w);

int discover(int i, int j, int h, int w, char t[101][52], char** s);

void mark(int i, int j, int h, int w, char** s);

#endif // MINESWEEPER_H_INCLUDED
