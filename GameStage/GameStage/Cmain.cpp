#include <stdio.h>
#include <Windows.h>

#pragma region Define

#define MAP_WIDTH 20
#define MAP_HEIGHT 20

#pragma endregion

#pragma region MAP

int map[MAP_HEIGHT][MAP_WIDTH] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,},
	{1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1,},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1,},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 1,},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
};

#pragma endregion


#pragma region Enum
enum Color
{
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHTGRAY,
	DARKGRAY,
	LIGHTBLUE,
	LIGHTGREEN,
	LIGHTCYAN,
	LIGHTRED,
	LIGHTMAGENTA,
	YELLOW,
	WHITE,

};

#pragma endregion
struct Obj {
	int x;
	int y;
	Color color;
	const char* shape;
	int hp;
	int mp;

};
Obj* player;
Obj* enemy;
#pragma region WIN API
void MoveXY(int x, int y);
void ChangeColor(int color);
void HideCursor();
#pragma endregion

#pragma region Game 
void StageInitialize();
void StageProgress();
void StageRender();
void StageRelease();
#pragma endregion


int main()
{
	HideCursor();
	StageInitialize();

	while (true)
	{
		system("cls");
		StageProgress();
		StageRender();

		Sleep(10);
	}

	StageRelease();
	return 0;
}

#pragma region Stage
void StageInitialize()
{
	player = (Obj*)malloc(sizeof(Obj));
	player->x = 10;
	player->y = 10;
	player->color = YELLOW;
	player->shape = "¿Ê";
	player->hp = 5;
	player->mp = 3;

	enemy = (Obj*)malloc(sizeof(Obj));
	enemy->x = 3;
	enemy->y = 3;
	enemy->color = MAGENTA;
	enemy->shape = "º¿";
	enemy->hp = 3;

}
void StageProgress()
{
	if (GetAsyncKeyState(VK_LEFT)) {
		player->x--;
		if (map[player->y][player->x] == 1) {
			player->x++;
		}
	}
	if (GetAsyncKeyState(VK_RIGHT)) {
		player->x++;
		if (map[player->y][player->x] == 1) {
			player->x--;
		}
	}
	if (GetAsyncKeyState(VK_UP)) {
		player->y--;
		if (map[player->y][player->x] == 1) {
			player->y++;
		}
	}
	if (GetAsyncKeyState(VK_DOWN)) {
		player->y++;
		if (map[player->y][player->x] == 1) {
			player->y--;
		}
	}
	if (map[player->y][player->x] == 2) {
		map[player->y][player->x] = 0;
		player->hp++;
	}
}
void StageRender()
{
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			switch (map[y][x]) {
			case 0:
				break;
			case 1:
				MoveXY(x, y);
				ChangeColor(WHITE);
				printf("¡á");
				break;
			case 2:
				MoveXY(x, y);
				ChangeColor(RED);
				printf("¢¾");
				break;
			}
		}
	}
	MoveXY(1, 21);
	ChangeColor(RED);
	printf("HP ");
	for (int i = 0; i < player->hp; i++) {
		MoveXY(3 + i, 21);
		printf("¢¾");
	}
	MoveXY(1, 22);
	ChangeColor(BLUE);
	printf("MP ");
	for (int i = 0; i < player->mp; i++) {
		MoveXY(3 + i, 22);
		printf("¡ß");
	}
	MoveXY(player->x, player->y);
	ChangeColor(player->color);
	printf(player->shape);

	MoveXY(enemy->x, enemy->y);
	ChangeColor(enemy->color);
	printf(enemy->shape);

}
void StageRelease()
{
	free(player);
}
#pragma endregion

#pragma region Win API 
void MoveXY(int x, int y)
{
	COORD pos;
	pos.X = x * 2;
	pos.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void ChangeColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void HideCursor()
{
	CONSOLE_CURSOR_INFO Info;
	Info.dwSize = 1;
	Info.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

#pragma endregion

