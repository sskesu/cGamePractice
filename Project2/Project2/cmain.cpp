#include<stdio.h>
#include<windows.h>
#include<time.h>

#define BlockCount 7 // 네모, 막대기, 지그재그2, 티스핀 7, 7거꾸로 (7개)

int map[21][25] = {
	{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,},
	{1,0,3,3,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,},
	{1,0,3,3,0,1,0,0,0,0,0,0,0,0,0,0,1,2,2,2,2,1,0,0,0,},
	{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,},
	{1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,4,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,4,4,4,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,},

};

#pragma region enum
enum Color {
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

enum Scene {
	START,
	GAME,
	HELP,
	QUIT
} scene;
#pragma endregion

typedef struct Obj {
	int x;
	int y;
	const char* shape;
	Color color;
} *Start, *Mark;

typedef struct Block {
	int x;
	int y;
	const char* shape[4][4];
	Color color;
};
#pragma region Winapi
void MoveXY(int x, int y);
void ChangeColor(int color);
void HideCursor();
#pragma endregion
#pragma region DoubleBuffer
#define BufferWidth 140
#define BufferHeight 40

HANDLE hBuffer[2];
int screenIndex;

void InitBuffer();
void WriteBuffer(int x, int y, const char* shape, int color);
void FlipBuffer();
void ClearBuffer();
void DestroyBuffer();
#pragma endregion
#pragma region Start
Start StartImg[7] = {};
Start StartMenu[4] = {};
Mark PlayerMark;
int StartIndex = 0;
void StartInitialize();
void StartRender();
void StartRelease();
void StartProgress();
#pragma endregion
void StartBackground() {
	
}
#pragma region Help
void HelpProgress();
void HelpRender();
#pragma endregion
Block* blocks[BlockCount];
int mainIndex = 0;
int nextIndex = 0;
int nextblock, mainblock, holdblock;
int holdIndex = 0;
void GameInitialize() {
	for (int i = 0; i < BlockCount; i++) {
		blocks[i] = (Block*)malloc(sizeof(Block));
	}
	blocks[0]->shape[0][0] = "        ";
	blocks[0]->shape[0][1] = "        ";
	blocks[0]->shape[0][2] = "■■■■";
	blocks[0]->shape[0][3] = "        ";
	blocks[0]->shape[1][0] = "  ■    ";
	blocks[0]->shape[1][1] = "  ■    ";
	blocks[0]->shape[1][2] = "  ■    ";
	blocks[0]->shape[1][3] = "  ■    ";
	blocks[0]->color = LIGHTCYAN;

	blocks[1]->shape[0][0] = "        ";
	blocks[1]->shape[0][1] = "  ■■  ";
	blocks[1]->shape[0][2] = "  ■■  ";
	blocks[1]->shape[0][3] = "        ";
	blocks[1]->color = YELLOW;

	blocks[2]->shape[0][0] = "        ";
	blocks[2]->shape[0][1] = "  ■    ";
	blocks[2]->shape[0][2] = "■■■  ";
	blocks[2]->shape[0][3] = "        ";
	blocks[2]->shape[1][0] = "  ■    ";
	blocks[2]->shape[1][1] = "■■    ";
	blocks[2]->shape[1][2] = "  ■    ";
	blocks[2]->shape[1][3] = "        ";
	blocks[2]->shape[2][0] = "        ";
	blocks[2]->shape[2][1] = "■■■  ";
	blocks[2]->shape[2][2] = "  ■    ";
	blocks[2]->shape[2][3] = "        ";
	blocks[2]->shape[3][0] = "  ■    ";
	blocks[2]->shape[3][1] = "  ■■  ";
	blocks[2]->shape[3][2] = "  ■    ";
	blocks[2]->shape[3][3] = "        ";
	blocks[2]->color = LIGHTMAGENTA;

	blocks[3]->shape[0][0] = "        ";
	blocks[3]->shape[0][1] = "■■    ";
	blocks[3]->shape[0][2] = "  ■■  ";
	blocks[3]->shape[0][3] = "        ";
	blocks[3]->shape[1][0] = "        ";
	blocks[3]->shape[1][1] = "  ■    ";
	blocks[3]->shape[1][2] = "■■    ";
	blocks[3]->shape[1][3] = "■      ";
	blocks[3]->color = RED;

	blocks[4]->shape[0][0] = "        ";
	blocks[4]->shape[0][1] = "  ■■  ";
	blocks[4]->shape[0][2] = "■■    ";
	blocks[4]->shape[0][3] = "        ";
	blocks[4]->shape[1][0] = "        ";
	blocks[4]->shape[1][1] = "■      ";
	blocks[4]->shape[1][2] = "■■    ";
	blocks[4]->shape[1][3] = "  ■    ";
	blocks[4]->color = GREEN;

	blocks[5]->shape[0][0] = "        ";
	blocks[5]->shape[0][1] = "■■    ";
	blocks[5]->shape[0][2] = "  ■    ";
	blocks[5]->shape[0][3] = "  ■    ";
	blocks[5]->shape[1][0] = "        ";
	blocks[5]->shape[1][1] = "■■■  ";
	blocks[5]->shape[1][2] = "■      ";
	blocks[5]->shape[1][3] = "        ";
	blocks[5]->shape[2][0] = "        ";
	blocks[5]->shape[2][1] = "■      ";
	blocks[5]->shape[2][2] = "■      ";
	blocks[5]->shape[2][3] = "■■    ";
	blocks[5]->shape[3][0] = "        ";
	blocks[5]->shape[3][1] = "    ■  ";
	blocks[5]->shape[3][2] = "■■■  ";
	blocks[5]->shape[3][3] = "        ";
	blocks[5]->color = BROWN;

	blocks[6]->shape[0][0] = "        ";
	blocks[6]->shape[0][1] = "■■    ";
	blocks[6]->shape[0][2] = "■      ";
	blocks[6]->shape[0][3] = "■      ";
	blocks[6]->shape[1][0] = "        ";
	blocks[6]->shape[1][1] = "■      ";
	blocks[6]->shape[1][2] = "■■■  ";
	blocks[6]->shape[1][3] = "        ";
	blocks[6]->shape[2][0] = "        ";
	blocks[6]->shape[2][1] = "  ■    ";
	blocks[6]->shape[2][2] = "  ■    ";
	blocks[6]->shape[2][3] = "■■    ";
	blocks[6]->shape[3][0] = "        ";
	blocks[6]->shape[3][1] = "■■■  ";
	blocks[6]->shape[3][2] = "    ■  ";
	blocks[6]->shape[3][3] = "        ";
	blocks[6]->color = BLUE;
}
void GameBlock() {
	//WriteBuffer(30, 10, blocks[]->shape[][], blocks[]->color);
	
}
void GameRender() {
	if (holdIndex != 0) {
		for (int i = 0; i < 4; i++) {
			WriteBuffer(22, 10 + i, blocks[holdblock]->shape[0][i], blocks[holdblock]->color);
		}
	}
	if (mainIndex != 0) {
		for (int i = 0; i < 4; i++) {
			WriteBuffer(30, 10 + i, blocks[mainblock]->shape[0][i], blocks[mainblock]->color);
		}
	}
	if (nextIndex != 0) {
		for (int i = 0; i < 4; i++) {
			WriteBuffer(38, 10 + i, blocks[nextblock]->shape[0][i], blocks[nextblock]->color);
		}
	}
	for (int y = 0; y < 21; y++) {
		for (int x = 0; x < 25; x++) {
			switch (map[y][x]) {
			case 1:
				WriteBuffer(x + 20, y + 10, "■", DARKGRAY);
				break;
			default:
				break;
			}
		}
	}
}
void GameProgress() {
	srand((unsigned)time(NULL));
	if (nextIndex == 0) {
		nextblock = rand() % 7;
		nextIndex++;
	}
	if (mainIndex == 0) {
		mainblock = nextblock;
		mainIndex++;
		nextIndex--;
	}
	if (GetAsyncKeyState(VK_SHIFT)) {
		if (holdIndex == 0) {
			holdblock = mainblock;
			holdIndex++;
			mainIndex--;
		}
		else {
			int dump;
			dump = holdblock;
			holdblock = mainblock;
			mainblock = dump;
		}
	}
	if (GetAsyncKeyState(VK_BACK)) {
		scene = START;
	}
}
void GameRelease() {
	for (int i = 0; i < BlockCount; i++) {
		free(blocks[i]);
		blocks[i] = nullptr;
	}
}


int main() {

	StartInitialize();
	GameInitialize();
	InitBuffer();

	ULONGLONG time = GetTickCount64();
	while (true) {
		switch (scene) {
		case START:
			if (time + 50 <= GetTickCount64()) {
				StartRender();
				StartProgress();

				FlipBuffer();
				ClearBuffer();
				time = GetTickCount64();
			}
			break;
		case GAME:
			if (time + 50 <= GetTickCount64()) {
				GameProgress();     //<<--
				GameRender();


				FlipBuffer();
				ClearBuffer();
				time = GetTickCount64();
			}
			break;
		case HELP:
			if (time + 50 <= GetTickCount64()) {
				HelpProgress();
				HelpRender();
				FlipBuffer();
				ClearBuffer();
				time = GetTickCount64();
			}
			break;
		case QUIT:
			return 0;
			break;
		default:
			break;
		}
		
	}

	StartRelease();
	GameRelease();
	DestroyBuffer();

	return 0;
}


#pragma region DoubleBuffer
void InitBuffer()
{
	screenIndex = 0;

	COORD size = { BufferWidth, BufferHeight };
	SMALL_RECT rect = { 0, 0, BufferWidth, BufferHeight };

	hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(hBuffer[0], size);
	SetConsoleWindowInfo(hBuffer[0], TRUE, &rect);

	hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(hBuffer[1], size);
	SetConsoleWindowInfo(hBuffer[1], TRUE, &rect);

	CONSOLE_CURSOR_INFO Info;
	Info.dwSize = 1;
	Info.bVisible = FALSE;

	SetConsoleCursorInfo(hBuffer[0], &Info);
	SetConsoleCursorInfo(hBuffer[1], &Info);


}

void WriteBuffer(int x, int y, const char* shape, int color)
{
	COORD pos = { x * 2, y };

	SetConsoleCursorPosition(hBuffer[screenIndex], pos);
	SetConsoleTextAttribute(hBuffer[screenIndex], color);

	DWORD dw;
	WriteFile(hBuffer[screenIndex], shape, strlen(shape), &dw, NULL);


}

void FlipBuffer()
{
	SetConsoleActiveScreenBuffer(hBuffer[screenIndex]);
	screenIndex = screenIndex == 1 ? 0 : 1;
}


void ClearBuffer()
{
	COORD pos = { 0,0 };
	DWORD dw;
	FillConsoleOutputCharacter(hBuffer[screenIndex], ' ', BufferWidth * BufferHeight, pos, &dw);
}

void DestroyBuffer()
{
	CloseHandle(hBuffer[0]);
	CloseHandle(hBuffer[1]);
}

#pragma endregion
#pragma region Winapi
void MoveXY(int x, int y) {
	COORD pos;
	pos.X = x * 2;
	pos.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void ChangeColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void HideCursor() {
	CONSOLE_CURSOR_INFO Info;
	Info.dwSize = 1;
	Info.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
#pragma endregion
#pragma region Start
void StartInitialize() {

	srand((unsigned)time(NULL));

	for (int i = 0; i < 7; i++) {
		StartImg[i] = (Start)malloc(sizeof(Obj));
		StartImg[i]->x = 20;
		StartImg[i]->y = 10 + i;
		StartImg[i]->color = LIGHTBLUE;
	}

	StartImg[0]->shape = " ######   #######  ######   ######    ####     #####  ";
	StartImg[1]->shape = " # ## #    ##   #  # ## #    ##  ##    ##     ##   ## ";
	StartImg[2]->shape = "   ##      ## #      ##      ##  ##    ##     #       ";
	StartImg[3]->shape = "   ##      ####      ##      #####     ##      #####  ";
	StartImg[4]->shape = "   ##      ## #      ##      ## ##     ##          ## ";
	StartImg[5]->shape = "   ##      ##   #    ##      ##  ##    ##     ##   ## ";
	StartImg[6]->shape = "  ####    #######   ####    #### ##   ####     #####  ";

	for (int i = 0; i < 4; i++) {
		StartMenu[i] = (Start)malloc(sizeof(Obj));
		StartMenu[i]->x = 31;
		StartMenu[i]->y = 22 + i*2;
		StartMenu[i]->color = LIGHTGRAY;
	}

	StartMenu[0]->shape = "  Start ";
	StartMenu[1]->shape = "Continue";
	StartMenu[2]->shape = "  Help  ";
	StartMenu[3]->shape = "  Quit  ";

	PlayerMark = (Mark)malloc(sizeof(Obj));
	PlayerMark->x = 28;
	PlayerMark->y = 22;
	PlayerMark->shape = "▶";
	PlayerMark->color = YELLOW;

}
void StartRender() {
	for (int i = 0; i < 7; i++) {
		WriteBuffer(StartImg[i]->x, StartImg[i]->y, StartImg[i]->shape, StartImg[i]->color);
	}
	for (int i = 0; i < 4; i++) {
		WriteBuffer(StartMenu[i]->x, StartMenu[i]->y, StartMenu[i]->shape, StartMenu[i]->color);
	}
	WriteBuffer(PlayerMark->x, PlayerMark->y + StartIndex * 2, PlayerMark->shape, PlayerMark->color);
	WriteBuffer(StartMenu[StartIndex]->x, StartMenu[StartIndex]->y, StartMenu[StartIndex]->shape, YELLOW);
}

void StartRelease() {
	for (int i = 0; i < 7; i++) {
		free(StartImg[i]);
		StartImg[i] = nullptr;
	}
	for (int i = 0; i < 4; i++) {
		free(StartMenu[i]);
		StartMenu[i] = nullptr;
	}
	free(PlayerMark);
	PlayerMark = nullptr;
}

void StartProgress() {
	if (GetAsyncKeyState(VK_DOWN)) {
		StartIndex++;
		if (StartIndex > 3) {
			StartIndex--;
		}
	}
	if (GetAsyncKeyState(VK_UP)) {
		StartIndex--;
		if (StartIndex < 0) {
			StartIndex++;
		}
	}
	if (GetAsyncKeyState(VK_RETURN)) {
		switch (StartIndex) {
		case 0:
			scene = GAME;
			break;
		case 1:
			// game continue
			break;
		case 2:
			scene = HELP;
			break;
		case 3:
			scene = QUIT;
			break;
		}
	}
}
#pragma endregion
#pragma region Help
void HelpProgress() {
	if (GetAsyncKeyState(VK_BACK)) {
		scene = START;
	}
}
void HelpRender() {
	for (int y = 0; y < 21; y++) {
		for (int x = 0; x < 25; x++) {
			switch (map[y][x]) {
			case 1:
				WriteBuffer(x + 20, y + 10, "■", DARKGRAY);
				break;
			case 2:
				WriteBuffer(x + 20, y + 10, "■", CYAN);
				break;
			case 3:
				WriteBuffer(x + 20, y + 10, "■", YELLOW);
				break;
			case 4:
				WriteBuffer(x + 20, y + 10, "■", LIGHTMAGENTA);
				break;
			default:
				break;
			}
		}
	}

	WriteBuffer(20, 6, "Hold Block", YELLOW);
	WriteBuffer(22, 8, "▽", YELLOW);

	WriteBuffer(36, 6, "Next Block", YELLOW);
	WriteBuffer(38, 8, "▽", YELLOW);

	WriteBuffer(45, 18, "Change  :     ↑   ", YELLOW);
	WriteBuffer(45, 20, "Move    :  ← ↓ →", YELLOW);
	WriteBuffer(45, 22, "Hold    :   Shift  ", YELLOW);
	WriteBuffer(45, 24, "Decide  :   Space  ", YELLOW);
	WriteBuffer(45, 28, "Back to menu", YELLOW);
	WriteBuffer(45, 30, ": backspace", YELLOW);
}
#pragma endregion