#include<conio.h>
#include<easyx.h>
#include<math.h>
#include<stdio.h>
#define PI 3.14
#define ROW 8
#define COL 8
void getoriginmap(int map[ROW][COL]);
void graphmap(int map[ROW][COL]);
void setfigure(int x, int y);
void setrock(int x, int y);
int gaming(int map[ROW][COL]);
int begingame();