#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ncurses.h>

///////////////////////////////////////////////// MAP
const int WIDHT = 29, HEIGHT = 20;

const char MAP[20][30] =
{
	"#############################",
	"#                           #",
	"#                           #",
	"#                           #",
	"#                           #",
	"#                           #",
	"#                           #",
	"#                           #",
	"#                           #",
	"#                           #",
	"#                           #",
	"#                           #",
	"#                           #",
	"#                           #",
	"#                           #",
	"#                           #",
	"#                           #",
	"#                           #",
	"#                           #",
	"#############################"
};

char map[20][30];

///////////////////////////////////////////////// GLOBAL VARIABLES
bool isWork;

struct position
{
	int x, y;
};

const int STEP = 1;

int dx, dy;

int size;

int sizeApple;

struct position p[27 * 18];
struct position apple;

///////////////////////////////////////////////// FUNCTIONS PROTOTYPES
void initialization();
void updatePlayer();
void updateKey();

///////////////////////////////////////////////// MAIN FUNCTION
int main()
{
	initscr();
	raw();
	noecho();
	nodelay(stdscr, true);

	initialization();

	///////////////////////////////////////////// MAIN LOOP
	while (isWork)
	{
		memcpy(map, MAP, sizeof(map));

		updateKey();

		updatePlayer();

		if (apple.x < 0 && apple.y < 0)
		{
			apple.x = rand() % (WIDHT - 2) + 1;
			apple.y = rand() % (HEIGHT - 2) + 1;

			sizeApple = rand() % 3 + 1;
		}

		if (sizeApple == 1)
			map[apple.y][apple.x] = '1';
		else if (sizeApple == 2)
			map[apple.y][apple.x] = '2';
		else if (sizeApple == 3)
			map[apple.y][apple.x] = '3';

		map[p[0].y][p[0].x] = 'O';

		for (int i = 1; i < size; i++)
			map[p[i].y][p[i].x] = 'o';

		///////////////////////////////////// CLEAR
		clear();

		///////////////////////////////////// OUTPUT

		for (int i = 0; i < HEIGHT; i++)
		{
			for (int j = 0; j < WIDHT; j++)
				printw("%c", map[i][j]);

			printw("\n");
		}

		usleep(200000);
	}
	/////////////////////////////////////////////	

	endwin();
}
///////////////////////////////////////////////// FUNCTIONS
void initialization()
{
	isWork = true;

	p[0].x = 15;
	p[0].y = 10;

	p[1].x = 14;
	p[1].y = 10;

	p[2].x = 13;
	p[2].y = 10;

	size = 3;

	dx = STEP;

	apple.x = apple.y = -1;

	/////////////////////////////////////////////
	memcpy(map, MAP, sizeof(map));

	map[p[0].y][p[0].x] = 'O';

	///////////////////////////////////////////// CLEAR
	clear();

	for (int i = 0; i < HEIGHT; i++)
		puts(map[i]);
}

void updatePlayer()
{
	int x = p[0].x + dx, y = p[0].y + dy;

	for (int i = size - 1; i > 0; i--)
	{
		p[i].x = p[i - 1].x;
		p[i].y = p[i - 1].y;

		if (x == p[i].x && y == p[i].y)
			isWork = false;
	}

	p[0].x += dx;
	p[0].y += dy;

	if (p[0].x == WIDHT - 1)
		p[0].x = 1;
	else if (p[0].x == 0)
		p[0].x = WIDHT - 2;
	
	if (p[0].y == HEIGHT - 1)
		p[0].y = 1;
	else if (p[0].y == 0)
		p[0].y = HEIGHT - 2;

	if (p[0].x == apple.x && p[0].y == apple.y)
	{
		apple.x = apple.y = -1;

		size += sizeApple;

		for (int i = 0; i < sizeApple; i++)
		{
			p[size - 1 - i].x = p[size - 1 - sizeApple].x;
			p[size - 1 - i].y = p[size - 1 - sizeApple].y;
		}
	}
}

void updateKey()
{
	char key = getch();

	if (key == 'w' && dy == 0)
	{
		dx = 0;
		dy = -STEP;
	}
	else if (key == 's' && dy == 0)
	{
		dx = 0;
		dy = STEP;
	}
	else if (key == 'a' && dx == 0)
	{
		dx = -STEP;
		dy = 0;
	}
	else if (key == 'd' && dx == 0)
	{
		dx = STEP;
		dy = 0;
	}
}
/////////////////////////////////////////////////
