#include <stdio.h>
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
	"#           #####           #",
	"#           #   #           #",
	"#  ######## #   # ########  #",
	"#  #      #x#   #x#      #  #",
	"#  #####  ###   ###  #####  #",
	"#      #             #      #",
	"#      ####       ####      #",
	"#         #       #         #",
	"#         #  ###  #         #",
	"#         #  #x#  #         #",
	"#         #  # #  #         #",
	"#         #  # #  #         #",
	"#         #### ####         #",
	"# x                       x #",
	"#                           #",
	"#############################"
};

char map[20][30];

///////////////////////////////////////////////// GLOBAL VARIABLES
bool isWork;
bool isVictory;
bool isDead;

int x, y;
int dx, dy;

const int STEP = 1;

const int numberBoxes = 5;

int boxes[5][2];

int fin[5][2];

///////////////////////////////////////////////// FUNCTIONS PROTOTYPES
void initialization();
void updatePlayer();
void checkBoxes();
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

		for (int i = 0; i < numberBoxes; i++)
			map[boxes[i][1]][boxes[i][0]] = 'O';

		dx = dy = 0;

		checkBoxes();

		updateKey();

		updatePlayer();

		///////////////////////////////////// CLEAR
		clear();

		///////////////////////////////////// OUTPUT
		puts("1 - Restart	2 - Exit\n");

		isVictory = true;

		for (int i = 0; i < HEIGHT; i++)
			for (int j = 0; j < WIDHT; j++)
				if (map[i][j] == 'x')
				{
					isVictory = false;

					i = HEIGHT;
					j = WIDHT;
				}

		if (isVictory == true)
			printw("%s", "\tVICTORY\n");
		
		if (isDead == true)
			printw("%s", "\tGAME OVER\n");

		for (int i = 0; i < HEIGHT; i++)
		{
			for (int j = 0; j < WIDHT; j++)
				printw("%c", map[i][j]);

			printw("\n");
		}
	}
	/////////////////////////////////////////////	

	endwin();
}
///////////////////////////////////////////////// FUNCTIONS
void initialization()
{
	isWork = true;
	isVictory = false;
	isDead = false;

	x = 14;
	y = 1;

	boxes[0][0] = 2;  boxes[0][1] = 2;
	boxes[1][0] = 5;  boxes[1][1] = 10;
	boxes[2][0] = 25; boxes[2][1] = 4;
	boxes[3][0] = 3;  boxes[3][1] = 15;
	boxes[4][0] = 20; boxes[4][1] = 12;

	fin[0][0] = 2;  fin[0][1] = 17;
	fin[1][0] = 11; fin[1][1] = 7;
	fin[2][0] = 17; fin[2][1] = 7;
	fin[3][0] = 14; fin[3][1] = 13;
	fin[4][0] = 26; fin[4][1] = 17;

	/////////////////////////////////////////////
	memcpy(map, MAP, sizeof(map));

	for (int i = 0; i < numberBoxes; i++)
		map[boxes[i][1]][boxes[i][0]] = 'O';

	map[y][x] = '$';

	///////////////////////////////////////////// CLEAR
	clear();

	puts("1 - Restart	2 - Exit\n");

	for (int i = 0; i < HEIGHT; i++)
		puts(map[i]);
}

void updatePlayer()
{
	if (map[y + dy][x + dx] == ' ' || map[y + dy][x + dx] == 'x')
	{
		x += dx;
		y += dy;
	}
	else if (map[y + dy][x + dx] == 'O' && (map[y + 2 * dy][x + 2 * dx] == ' ' || map[y + 2 * dy][x + 2 * dx] == 'x'))
	{
		x += dx;
		y += dy;

		for (int i = 0; i < numberBoxes; i++)
			if (boxes[i][0] == x && boxes[i][1] == y)
			{
				boxes[i][0] += dx;
				boxes[i][1] += dy;

				map[boxes[i][1]][boxes[i][0]] = 'O';

				i = numberBoxes;
			}
	}

	map[y][x] = '$';
}

void checkBoxes()
{
	for (int i = 0; i < numberBoxes; i++)
	{
		bool isFin = false;

		for (int j = 0; j < numberBoxes; j++)
			if (boxes[i][0] == fin[j][0] && boxes[i][1] == fin[j][1])
				isFin = true;

		if (isFin == false)
			if (map[boxes[i][1] + STEP][boxes[i][0]] == '#' && map[boxes[i][1]][boxes[i][0] + STEP] == '#' ||
				map[boxes[i][1] + STEP][boxes[i][0]] == 'O' && map[boxes[i][1]][boxes[i][0] + STEP] == '#' ||
				map[boxes[i][1] + STEP][boxes[i][0]] == '#' && map[boxes[i][1]][boxes[i][0] + STEP] == 'O' ||

				map[boxes[i][1] + STEP][boxes[i][0]] == '#' && map[boxes[i][1]][boxes[i][0] - STEP] == '#' ||
				map[boxes[i][1] + STEP][boxes[i][0]] == 'O' && map[boxes[i][1]][boxes[i][0] - STEP] == '#' ||
				map[boxes[i][1] + STEP][boxes[i][0]] == '#' && map[boxes[i][1]][boxes[i][0] - STEP] == 'O' ||

				map[boxes[i][1] - STEP][boxes[i][0]] == '#' && map[boxes[i][1]][boxes[i][0] + STEP] == '#' ||
				map[boxes[i][1] - STEP][boxes[i][0]] == 'O' && map[boxes[i][1]][boxes[i][0] + STEP] == '#' ||
				map[boxes[i][1] - STEP][boxes[i][0]] == '#' && map[boxes[i][1]][boxes[i][0] + STEP] == 'O' ||

				map[boxes[i][1] - STEP][boxes[i][0]] == '#' && map[boxes[i][1]][boxes[i][0] - STEP] == '#' ||
				map[boxes[i][1] - STEP][boxes[i][0]] == 'O' && map[boxes[i][1]][boxes[i][0] - STEP] == '#' ||
				map[boxes[i][1] - STEP][boxes[i][0]] == '#' && map[boxes[i][1]][boxes[i][0] - STEP] == 'O')
			{
				isDead = true;

				break;
			}
	}
}

void updateKey()
{
	char key = getch();

	if (key == 'w')
	{
		dx = 0;
		dy = -STEP;
	}
	else if (key == 's')
	{
		dx = 0;
		dy = STEP;
	}
	else if (key == 'a')
	{
		dx = -STEP;
		dy = 0;
	}
	else if (key == 'd')
	{
		dx = STEP;
		dy = 0;
	}
	else if (key == '1')
		initialization();
	else if (key == '2')
		isWork = false;
}
/////////////////////////////////////////////////
