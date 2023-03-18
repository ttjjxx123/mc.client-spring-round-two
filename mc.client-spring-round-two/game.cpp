#include<easyx.h>
#include<math.h>
#include<iostream>
#include<stdio.h>
#include<conio.h>
#define ROW 8
#define COL 8
#define SIDE 50;
void getoriginmap(int map[ROW][COL])
{
	int originmap[ROW][COL] =
	{
		{0,0,0,0,0,0,0,0 },
		{0,0,0,0,0,0,0,0 },
		{0,0,0,0,0,0,0,0 },
		{0,0,0,0,0,0,0,0 },
		{0,0,0,0,0,0,0,1 },
		{2,0,0,0,0,0,1,1 },
		{2,0,0,0,0,1,1,1 },
		{1,1,1,1,1,1,1,1 }
	};
	for (int x = 0; x < ROW; x++)
	{
		for (int y = 0; y < COL; y++)
		{
			map[x][y] = originmap[x][y];
		}
	}
}

void setrock(int x, int y) {
	setfillcolor(BROWN);
	setlinecolor(BLACK);
	fillrectangle(x, y, x + 50, y + 50);
}
void setfigure(int x, int y)
{
	setfillcolor(BLACK);
	solidrectangle(x + 10, y, x + 40, y + 10);//hair
	setfillcolor(BROWN);
	setlinecolor(BLACK);
	fillrectangle(x + 10, y + 10, x + 40, y + 30);//face
	setfillcolor(WHITE);
	fillrectangle(x + 13, y + 12, x + 17, y + 15);
	fillrectangle(x + 23, y + 12, x + 27, y + 15);//eyes
	line(x + 13, y + 25, x + 27, y + 25);
	setfillcolor(BLUE);
	setlinecolor(GREEN);
	fillrectangle(x + 5, y + 30, x + 45, y + 60);//body
	setfillcolor(BROWN);
	setlinecolor(BLACK);
	fillrectangle(x, y + 30, x + 5, y + 60);
	fillrectangle(x + 45, y + 30, x + 50, y + 60);//arms
	fillrectangle(x + 5, y + 60, x + 24, y + 100);
	fillrectangle(x + 26, y + 60, x + 45, y + 100);//legs
}

void graphmap(int map[ROW][COL]) {
	initgraph(400, 400);
	setbkcolor(RGB(134, 172, 242));
	cleardevice();
}

int gaming(int map[ROW][COL])
{
	char ch;
	int x, y;
	BeginBatchDraw();
	while (1)
	{
		cleardevice();
		for (int j = 0; j < COL; j++)
		{
			for (int i = 0; i < ROW; i++)
			{
				if (j < ROW - 1 && map[j][i] == 2 && map[j + 1][i] == 2)
				{
					y = j; x = i;
					setfigure(x * 50, y * 50);
				}
				else if (map[j][i] == 1)
					setrock(i * 50, j * 50);
			}
		}
		FlushBatchDraw();
		Sleep(40);
		if (_kbhit() != 0)
		{
			ch = _getch();
			if (ch == 'd' && map[y][x + 1] == 0 && map[y + 1][x + 1] == 0)
			{
				map[y][x + 1] = map[y + 1][x + 1] = 2;
				map[y][x] = map[y + 1][x] = 0;
			}
			else if ((ch == 'a' && map[y][x - 1] == 0 && map[y + 1][x - 1] == 0))
			{
				map[y][x - 1] = map[y + 1][x - 1] = 2;
				map[y][x] = map[y + 1][x] = 0;
			}
			else if (ch == 'w' && y >= 1)
			{
				map[y - 1][x] = 2;
				map[y + 1][x] = 0;
			}
			else if (ch == 's' && map[y + 2][x] == 0)
			{
				map[y][x] = 0;
				map[y + 2][x] = 2;
			}
			else if (ch == 'b')
			{
				EndBatchDraw();
				return 1;
			}
		}
	}
	EndBatchDraw();
}
int begingame()
{
	int map[ROW][COL];
	printf("use--wsad--to move\n"
		"printf \'b\'to end\n"
		"put any button to begin\n");
	getchar();
	getoriginmap(map);
	graphmap(map);
	gaming(map);
	closegraph();
	return 0;
}