#include<stdio.h>
#include<windows.h>
#include<time.h>

#define BlockCount 7 // 네모, 막대기, 지그재그2, 티스핀 7, 7거꾸로 (7개)
#pragma region map
int map[21][25] = {  // [+10][+20] [0][5]= [10][25], [1][5]  16
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},//
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},  // 5 
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},//
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},//
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},   // 10
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},//
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},//   // 15
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},   // [19][6+x] ~ 
	{0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,},

};
int helpmap[21][25] = {  // [+10][+20] [0][5]= [10][25], [1][5]  16
	{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,},
	{1,0,3,3,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,},
	{1,0,3,3,0,1,0,0,0,0,0,0,0,0,0,0,1,2,2,2,2,1,0,0,0,},
	{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,},
	{1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,},  // 5 
	{0,0,0,0,0,1,0,0,0,0,4,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,4,4,4,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},   // 10
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},   // 15
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,},   // [19][6+x] ~ 
	{0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,},

};
#pragma endregion
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
	QUIT,
	PAUSE
} scene;
#pragma endregion
#pragma region struct
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
#pragma endregion
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
#pragma region Game
Block* blocks[BlockCount];
int mainIndex = 0;
int nextblock[5];
int nextIndex = 0;
int mainblock, holdblock;
int holdIndex = 0, holduse = 0;
int blockX = 0, blockY = 0, blockShape = 0, madeline = 0;
char showtimeMS[10], showtimeS[10], showtimeM[10], showline[10], showlevel[10];
char showtimeMS10[10], showtimeS10[10];
int gametimeMS = 0, gametimeS = 0, gametimeM = 0, gamelevel = 1, gamespeed = 0, blockspeed = 0;
int gametimeMS10 = 0, gametimeS10 = 0;
int gameover = 0;
void GameInitialize();
void GameRender();
void GameDecision();
void GameLeftWall();
void GameRightWall();
void GameProgress();
void GameRelease();
#pragma endregion

void PauseRender() {

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
			if (time + 10 <= GetTickCount64()) {
				GameProgress();
				GameRender();
				FlipBuffer();
				ClearBuffer();
				gametimeMS++;
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
		case PAUSE:
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
			switch (helpmap[y][x]) {
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

void GameInitialize() {
	for (int i = 0; i < BlockCount; i++) {
		blocks[i] = (Block*)malloc(sizeof(Block));
	}
	blocks[0]->shape[0][0] = "        ";
	blocks[0]->shape[0][1] = "        ";
	blocks[0]->shape[0][2] = "■■■■";          // *
	blocks[0]->shape[0][3] = "        ";
	blocks[0]->shape[1][0] = "  ■    ";
	blocks[0]->shape[1][1] = "  ■    ";
	blocks[0]->shape[1][2] = "  ■    ";
	blocks[0]->shape[1][3] = "  ■    ";          // *
	blocks[0]->shape[2][0] = "        ";
	blocks[0]->shape[2][1] = "        ";
	blocks[0]->shape[2][2] = "■■■■";
	blocks[0]->shape[2][3] = "        ";
	blocks[0]->shape[3][0] = "  ■    ";
	blocks[0]->shape[3][1] = "  ■    ";
	blocks[0]->shape[3][2] = "  ■    ";
	blocks[0]->shape[3][3] = "  ■    ";
	blocks[0]->color = LIGHTCYAN;

	blocks[1]->shape[0][0] = "        ";
	blocks[1]->shape[0][1] = "  ■■  ";
	blocks[1]->shape[0][2] = "  ■■  ";
	blocks[1]->shape[0][3] = "        ";
	blocks[1]->shape[1][0] = "        ";
	blocks[1]->shape[1][1] = "  ■■  ";
	blocks[1]->shape[1][2] = "  ■■  ";
	blocks[1]->shape[1][3] = "        ";
	blocks[1]->shape[2][0] = "        ";
	blocks[1]->shape[2][1] = "  ■■  ";
	blocks[1]->shape[2][2] = "  ■■  ";
	blocks[1]->shape[2][3] = "        ";
	blocks[1]->shape[3][0] = "        ";
	blocks[1]->shape[3][1] = "  ■■  ";
	blocks[1]->shape[3][2] = "  ■■  ";
	blocks[1]->shape[3][3] = "        ";
	blocks[1]->color = YELLOW;

	blocks[2]->shape[0][0] = "        ";
	blocks[2]->shape[0][1] = "  ■    ";
	blocks[2]->shape[0][2] = "■■■  ";
	blocks[2]->shape[0][3] = "        ";
	blocks[2]->shape[1][0] = "  ■    ";
	blocks[2]->shape[1][1] = "■■    ";
	blocks[2]->shape[1][2] = "  ■    ";          // *
	blocks[2]->shape[1][3] = "        ";
	blocks[2]->shape[2][0] = "        ";
	blocks[2]->shape[2][1] = "■■■  ";          // *
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
	blocks[3]->shape[2][0] = "        ";
	blocks[3]->shape[2][1] = "■■    ";
	blocks[3]->shape[2][2] = "  ■■  ";
	blocks[3]->shape[2][3] = "        ";
	blocks[3]->shape[3][0] = "        ";
	blocks[3]->shape[3][1] = "  ■    ";
	blocks[3]->shape[3][2] = "■■    ";
	blocks[3]->shape[3][3] = "■      ";
	blocks[3]->color = RED;

	blocks[4]->shape[0][0] = "        ";
	blocks[4]->shape[0][1] = "  ■■  ";
	blocks[4]->shape[0][2] = "■■    ";
	blocks[4]->shape[0][3] = "        ";
	blocks[4]->shape[1][0] = "        ";
	blocks[4]->shape[1][1] = "■      ";
	blocks[4]->shape[1][2] = "■■    ";
	blocks[4]->shape[1][3] = "  ■    ";
	blocks[4]->shape[2][0] = "        ";
	blocks[4]->shape[2][1] = "  ■■  ";
	blocks[4]->shape[2][2] = "■■    ";
	blocks[4]->shape[2][3] = "        ";
	blocks[4]->shape[3][0] = "        ";
	blocks[4]->shape[3][1] = "■      ";
	blocks[4]->shape[3][2] = "■■    ";
	blocks[4]->shape[3][3] = "  ■    ";
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
void GameRender() {
	if (holdIndex != 0) {
		for (int i = 0; i < 4; i++) {
			WriteBuffer(20, 10 + i, blocks[holdblock]->shape[0][i], blocks[holdblock]->color);
		}
	}
	if (mainIndex != 0) {
		for (int i = 0; i < 4; i++) {
			WriteBuffer(30 + blockX, 10 + blockY + i, blocks[mainblock]->shape[blockShape][i], blocks[mainblock]->color);
		}
	}
	if (nextIndex != 0) {
		for (int j = 0; j < 5; j++) {
			for (int i = 0; i < 4; i++) {
				WriteBuffer(38, 10 + i + j * 4, blocks[nextblock[j]]->shape[0][i], blocks[nextblock[j]]->color);
			}
		}
	}
	WriteBuffer(21, 8, "HOLD", WHITE);
	WriteBuffer(39, 8, "NEXT", WHITE);
	WriteBuffer(47, 14, "LINES", WHITE);
	if (madeline < 10) {
		WriteBuffer(60, 14, showline, WHITE);
	}
	else if (madeline >= 10 && madeline < 100) {
		WriteBuffer(59, 14, showline, WHITE);
	}
	else {
		WriteBuffer(58, 14, showline, WHITE);
	}

	WriteBuffer(47, 18, "LEVEL", WHITE);
	if (gamelevel >= 10) {
		WriteBuffer(59, 18, showlevel, WHITE);
	}
	else if (gamelevel < 10) {
		WriteBuffer(60, 18, showlevel, WHITE);
	}

	WriteBuffer(47, 22, "TIME               :   .", WHITE);
	
	WriteBuffer(60, 22, showtimeMS, WHITE);
	WriteBuffer(59, 22, showtimeMS10, WHITE);
	WriteBuffer(58, 22, showtimeS, WHITE);
	WriteBuffer(57, 22, showtimeS10, WHITE);
	if (gametimeM < 10) {
		WriteBuffer(56, 22, showtimeM, WHITE);
	}
	else if (gametimeM >= 10 && gametimeM < 100) {
		WriteBuffer(55, 22, showtimeM, WHITE);
	}
	else if (gametimeM > 100) {
		WriteBuffer(54, 22, showtimeM, WHITE);
	}

	for (int y = 0; y < 21; y++) {
		for (int x = 0; x < 25; x++) {
			switch (map[y][x]) {
			case 1:
				WriteBuffer(x + 20, y + 10, "■", DARKGRAY);
				break;
			case 2:
				WriteBuffer(x + 20, y + 10, "■", LIGHTCYAN);
				break;
			case 3:
				WriteBuffer(x + 20, y + 10, "■", YELLOW);
				break;
			case 4:
				WriteBuffer(x + 20, y + 10, "■", LIGHTMAGENTA);
				break;
			case 5:
				WriteBuffer(x + 20, y + 10, "■", RED);
				break;
			case 6:
				WriteBuffer(x + 20, y + 10, "■", GREEN);
				break;
			case 7:
				WriteBuffer(x + 20, y + 10, "■", BROWN);
				break;
			case 8:
				WriteBuffer(x + 20, y + 10, "■", BLUE);
				break;
			default:
				break;
			}
		}
	}
}
void GameDecision() {
	//block > map change
	switch (mainblock) { // 블럭종류
	case 0:
		switch (blockShape) { // 블럭방향
		case 0:
		case 2:
			if (map[2 + blockY][10 + blockX] != 0 || map[2 + blockY][11 + blockX] != 0 ||
				map[2 + blockY][12 + blockX] != 0 || map[2 + blockY][13 + blockX] != 0) {
				blockY--;
				map[2 + blockY][10 + blockX] = 2;
				map[2 + blockY][11 + blockX] = 2;
				map[2 + blockY][12 + blockX] = 2;
				map[2 + blockY][13 + blockX] = 2;
				blockX = 0, blockY = 0, blockShape = 0;
				mainIndex--;
				holduse = 0;
			}
			break;
		case 1:
		case 3:
			if (map[3 + blockY][11 + blockX] != 0) {
				blockY--;
				map[blockY][11 + blockX] = 2;
				map[1 + blockY][11 + blockX] = 2;
				map[2 + blockY][11 + blockX] = 2;
				map[3 + blockY][11 + blockX] = 2;
				blockX = 0, blockY = 0, blockShape = 0;
				mainIndex--;
				holduse = 0;
			}
			break;
		default:
			break;
		}
		break;
	case 1:  // 네모
		if (map[2 + blockY][11 + blockX] != 0 || map[2 + blockY][12 + blockX] != 0) {
			blockY--;
			map[1 + blockY][11 + blockX] = 3;
			map[1 + blockY][12 + blockX] = 3;
			map[2 + blockY][11 + blockX] = 3;
			map[2 + blockY][12 + blockX] = 3;
			blockX = 0, blockY = 0, blockShape = 0;
			mainIndex--;
			holduse = 0;
		}
		break;
	case 2:  // T
		switch (blockShape) {
		case 0:
			if (map[2 + blockY][10 + blockX] != 0 || map[2 + blockY][11 + blockX] != 0 || map[2 + blockY][12 + blockX] != 0) {
				blockY--;
				map[1 + blockY][11 + blockX] = 4;
				map[2 + blockY][10 + blockX] = 4;
				map[2 + blockY][11 + blockX] = 4;
				map[2 + blockY][12 + blockX] = 4;
				blockX = 0, blockY = 0, blockShape = 0;
				mainIndex--;
				holduse = 0;
			}
			break;
		case 1:
			if (map[1 + blockY][10 + blockX] != 0 || map[2 + blockY][11 + blockX] != 0) {
				blockY--;
				map[blockY][11 + blockX] = 4;
				map[1 + blockY][10 + blockX] = 4;
				map[1 + blockY][11 + blockX] = 4;
				map[2 + blockY][11 + blockX] = 4;
				blockX = 0, blockY = 0, blockShape = 0;
				mainIndex--;
				holduse = 0;
			}
			break;
		case 2:
			if (map[1 + blockY][10 + blockX] != 0 || map[2 + blockY][11 + blockX] != 0 || map[1 + blockY][12 + blockX] != 0) {
				blockY--;
				map[1 + blockY][10 + blockX] = 4;
				map[1 + blockY][11 + blockX] = 4;
				map[1 + blockY][12 + blockX] = 4;
				map[2 + blockY][11 + blockX] = 4;
				blockX = 0, blockY = 0, blockShape = 0;
				mainIndex--;
				holduse = 0;
			}
			break;
		case 3:
			if (map[2 + blockY][11 + blockX] != 0 || map[1 + blockY][12 + blockX] != 0) {
				blockY--;
				map[blockY][11 + blockX] = 4;
				map[1 + blockY][11 + blockX] = 4;
				map[1 + blockY][12 + blockX] = 4;
				map[2 + blockY][11 + blockX] = 4;
				blockX = 0, blockY = 0, blockShape = 0;
				mainIndex--;
				holduse = 0;
			}
			break;
		default:
			break;
		}
		break;
	case 3:  // 왼쪽지그
		switch (blockShape) {
		case 0:
		case 2:
			if (map[1 + blockY][10 + blockX] != 0 || map[2 + blockY][11 + blockX] != 0 || map[2 + blockY][12 + blockX] != 0) {
				blockY--;
				map[1 + blockY][10 + blockX] = 5;
				map[1 + blockY][11 + blockX] = 5;
				map[2 + blockY][11 + blockX] = 5;
				map[2 + blockY][12 + blockX] = 5;
				blockX = 0, blockY = 0, blockShape = 0;
				mainIndex--;
				holduse = 0;
			}
			break;
		case 1:
		case 3:
			if (map[3 + blockY][10 + blockX] != 0 || map[2 + blockY][11 + blockX] != 0) {
				blockY--;
				map[1 + blockY][11 + blockX] = 5;
				map[2 + blockY][10 + blockX] = 5;
				map[2 + blockY][11 + blockX] = 5;
				map[3 + blockY][10 + blockX] = 5;
				blockX = 0, blockY = 0, blockShape = 0;
				mainIndex--;
				holduse = 0;
			}
			break;
		default:
			break;
		}
		break;
	case 4:  // 오른쪽
		switch (blockShape) {
		case 0:
		case 2:
			if (map[2 + blockY][10 + blockX] != 0 || map[2 + blockY][11 + blockX] != 0 || map[1 + blockY][12 + blockX] != 0) {
				blockY--;
				map[1 + blockY][11 + blockX] = 6;
				map[1 + blockY][12 + blockX] = 6;
				map[2 + blockY][10 + blockX] = 6;
				map[2 + blockY][11 + blockX] = 6;
				blockX = 0, blockY = 0, blockShape = 0;
				mainIndex--;
				holduse = 0;
			}
			break;
		case 1:
		case 3:
			if (map[2 + blockY][10 + blockX] != 0 || map[3 + blockY][11 + blockX] != 0) {
				blockY--;
				map[1 + blockY][10 + blockX] = 6;
				map[2 + blockY][10 + blockX] = 6;
				map[2 + blockY][11 + blockX] = 6;
				map[3 + blockY][11 + blockX] = 6;
				blockX = 0, blockY = 0, blockShape = 0;
				mainIndex--;
				holduse = 0;
			}
			break;
		default:
			break;
		}
		break;
	case 5:  // 7 boom
		switch (blockShape) {
		case 0:
			if (map[1 + blockY][10 + blockX] != 0 || map[3 + blockY][11 + blockX] != 0) {
				blockY--;
				map[1 + blockY][10 + blockX] = 7;
				map[1 + blockY][11 + blockX] = 7;
				map[2 + blockY][11 + blockX] = 7;
				map[3 + blockY][11 + blockX] = 7;
				blockX = 0, blockY = 0, blockShape = 0;
				mainIndex--;
				holduse = 0;
			}
			break;
		case 1:
			if (map[2 + blockY][10 + blockX] != 0 || map[1 + blockY][11 + blockX] != 0 || map[1 + blockY][12 + blockX] != 0) {
				blockY--;
				map[1 + blockY][10 + blockX] = 7;
				map[1 + blockY][11 + blockX] = 7;
				map[1 + blockY][12 + blockX] = 7;
				map[2 + blockY][10 + blockX] = 7;
				blockX = 0, blockY = 0, blockShape = 0;
				mainIndex--;
				holduse = 0;
			}
			break;
		case 2:
			if (map[3 + blockY][10 + blockX] != 0 || map[3 + blockY][11 + blockX] != 0) {
				blockY--;
				map[1 + blockY][10 + blockX] = 7;
				map[2 + blockY][10 + blockX] = 7;
				map[3 + blockY][10 + blockX] = 7;
				map[3 + blockY][11 + blockX] = 7;
				blockX = 0, blockY = 0, blockShape = 0;
				mainIndex--;
				holduse = 0;
			}
			break;
		case 3:
			if (map[2 + blockY][10 + blockX] != 0 || map[2 + blockY][11 + blockX] != 0 || map[2 + blockY][12 + blockX] != 0) {
				blockY--;
				map[1 + blockY][12 + blockX] = 7;
				map[2 + blockY][10 + blockX] = 7;
				map[2 + blockY][11 + blockX] = 7;
				map[2 + blockY][12 + blockX] = 7;
				blockX = 0, blockY = 0, blockShape = 0;
				mainIndex--;
				holduse = 0;
			}
			break;
		default:
			break;
		}
		break;
	case 6:  // 7거꾸로
		switch (blockShape) {
		case 0:
			if (map[3 + blockY][10 + blockX] != 0 || map[1 + blockY][11 + blockX] != 0) {
				blockY--;
				map[1 + blockY][10 + blockX] = 8;
				map[1 + blockY][11 + blockX] = 8;
				map[2 + blockY][10 + blockX] = 8;
				map[3 + blockY][10 + blockX] = 8;
				blockX = 0, blockY = 0, blockShape = 0;
				mainIndex--;
				holduse = 0;
			}
			break;
		case 1:
			if (map[2 + blockY][10 + blockX] != 0 || map[2 + blockY][11 + blockX] != 0 || map[2 + blockY][12 + blockX] != 0) {
				blockY--;
				map[1 + blockY][10 + blockX] = 8;
				map[2 + blockY][10 + blockX] = 8;
				map[2 + blockY][11 + blockX] = 8;
				map[2 + blockY][12 + blockX] = 8;
				blockX = 0, blockY = 0, blockShape = 0;
				mainIndex--;
				holduse = 0;
			}
			break;
		case 2:
			if (map[3 + blockY][10 + blockX] != 0 || map[3 + blockY][11 + blockX] != 0) {
				blockY--;
				map[1 + blockY][11 + blockX] = 8;
				map[2 + blockY][11 + blockX] = 8;
				map[3 + blockY][10 + blockX] = 8;
				map[3 + blockY][11 + blockX] = 8;
				blockX = 0, blockY = 0, blockShape = 0;
				mainIndex--;
				holduse = 0;
			}
			break;
		case 3:
			if (map[1 + blockY][10 + blockX] != 0 || map[1 + blockY][11 + blockX] != 0 || map[2 + blockY][12 + blockX] != 0) {
				blockY--;
				map[1 + blockY][10 + blockX] = 8;
				map[1 + blockY][11 + blockX] = 8;
				map[1 + blockY][12 + blockX] = 8;
				map[2 + blockY][12 + blockX] = 8;
				blockX = 0, blockY = 0, blockShape = 0;
				mainIndex--;
				holduse = 0;
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}
void GameLeftWall() {
	switch (mainblock) { // 블럭종류
	case 0:
		switch (blockShape) { // 블럭방향
		case 0:
		case 2:
			if (map[2 + blockY][10 + blockX] != 0) {
				blockX++;
			}
			break;
		case 1:
		case 3:
			if (map[blockY][11 + blockX] != 0 || map[1 + blockY][11 + blockX] != 0 ||
				map[2 + blockY][11 + blockX] != 0 || map[3 + blockY][11 + blockX] != 0) {
				blockX++;
			}
			break;
		default:
			break;
		}
		break;
	case 1:  // 네모
		if (map[1 + blockY][11 + blockX] != 0 || map[2 + blockY][11 + blockX] != 0) {
			blockX++;
		}
		break;
	case 2:  // T
		switch (blockShape) {
		case 0:
			if (map[1 + blockY][11 + blockX] != 0 || map[2 + blockY][10 + blockX] != 0) {
				blockX++;
			}
			break;
		case 1:
			if (map[blockY][11 + blockX] != 0 || map[1 + blockY][10 + blockX] != 0 || map[2 + blockY][11 + blockX] != 0) {
				blockX++;
			}
			break;
		case 2:
			if (map[1 + blockY][10 + blockX] != 0 || map[2 + blockY][11 + blockX] != 0) {
				blockX++;
			}
			break;
		case 3:
			if (map[blockY][11 + blockX] != 0 || map[1 + blockY][11 + blockX] != 0 || map[2 + blockY][11 + blockX] != 0) {
				blockX++;
			}
			break;
		default:
			break;
		}
		break;
	case 3:  // 왼쪽지그
		switch (blockShape) {
		case 0:
		case 2:
			if (map[1 + blockY][10 + blockX] != 0 || map[2 + blockY][11 + blockX] != 0) {
				blockX++;
			}
			break;
		case 1:
		case 3:
			if (map[1 + blockY][11 + blockX] != 0 || map[2 + blockY][10 + blockX] != 0 || map[3 + blockY][10 + blockX] != 0) {
				blockX++;
			}
			break;
		default:
			break;
		}
		break;
	case 4:  // 오른쪽
		switch (blockShape) {
		case 0:
		case 2:
			if (map[1 + blockY][11 + blockX] != 0 || map[2 + blockY][10 + blockX] != 0) {
				blockX++;
			}
			break;
		case 1:
		case 3:
			if (map[1 + blockY][10 + blockX] != 0 || map[2 + blockY][10 + blockX] != 0 || map[3 + blockY][11 + blockX] != 0) {
				blockX++;
			}
			break;
		default:
			break;
		}
		break;
	case 5:  // 7
		switch (blockShape) {
		case 0:
			if (map[1 + blockY][10 + blockX] != 0 || map[2 + blockY][11 + blockX] != 0 || map[3 + blockY][11 + blockX] != 0) {
				blockX++;
			}
			break;
		case 1:
			if (map[1 + blockY][10 + blockX] != 0 || map[2 + blockY][10 + blockX] != 0) {
				blockX++;
			}
			break;
		case 2:
			if (map[1 + blockY][10 + blockX] != 0 || map[2 + blockY][10 + blockX] != 0 || map[3 + blockY][10 + blockX] != 0) {
				blockX++;
			}
			break;
		case 3:
			if (map[1 + blockY][12 + blockX] != 0 || map[2 + blockY][10 + blockX] != 0) {
				blockX++;
			}
			break;
		default:
			break;
		}
		break;
	case 6:  // 7거꾸로
		switch (blockShape) {
		case 0:
			if (map[1 + blockY][10 + blockX] != 0 || map[2 + blockY][10 + blockX] != 0 || map[3 + blockY][10 + blockX] != 0) {
				blockX++;
			}
			break;
		case 1:
			if (map[1 + blockY][10 + blockX] != 0 || map[2 + blockY][10 + blockX] != 0) {
				blockX++;
			}
			break;
		case 2:
			if (map[1 + blockY][11 + blockX] != 0 || map[2 + blockY][11 + blockX] != 0 || map[3 + blockY][10 + blockX] != 0) {
				blockX++;
			}
			break;
		case 3:
			if (map[1 + blockY][10 + blockX] != 0 || map[2 + blockY][12 + blockX] != 0) {
				blockX++;
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}
void GameRightWall() {
	switch (mainblock) { // 블럭종류
	case 0:
		switch (blockShape) { // 블럭방향
		case 0:
		case 2:
			if (map[2 + blockY][13 + blockX] != 0) {
				blockX--;
			}
			break;
		case 1:
		case 3:
			if (map[blockY][11 + blockX] != 0 || map[1 + blockY][11 + blockX] != 0 ||
				map[2 + blockY][11 + blockX] != 0 || map[3 + blockY][11 + blockX] != 0) {
				blockX--;
			}
			break;
		default:
			break;
		}
		break;
	case 1:  // 네모
		if (map[1 + blockY][12 + blockX] != 0 || map[2 + blockY][12 + blockX] != 0) {
			blockX--;
		}
		break;
	case 2:  // T
		switch (blockShape) {
		case 0:
			if (map[1 + blockY][11 + blockX] != 0 || map[2 + blockY][12 + blockX] != 0) {
				blockX--;
			}
			break;
		case 1:
			if (map[blockY][11 + blockX] != 0 || map[1 + blockY][11 + blockX] != 0 || map[2 + blockY][11 + blockX] != 0) {
				blockX--;
			}
			break;
		case 2:
			if (map[1 + blockY][12 + blockX] != 0 || map[2 + blockY][11 + blockX] != 0) {
				blockX--;
			}
			break;
		case 3:
			if (map[blockY][11 + blockX] != 0 || map[1 + blockY][12 + blockX] != 0 || map[2 + blockY][11 + blockX] != 0) {
				blockX--;
			}
			break;
		default:
			break;
		}
		break;
	case 3:  // 왼쪽지그
		switch (blockShape) {
		case 0:
		case 2:
			if (map[1 + blockY][11 + blockX] != 0 || map[2 + blockY][12 + blockX] != 0) {
				blockX--;
			}
			break;
		case 1:
		case 3:
			if (map[1 + blockY][11 + blockX] != 0 || map[2 + blockY][11 + blockX] != 0 || map[3 + blockY][10 + blockX] != 0) {
				blockX--;
			}
			break;
		default:
			break;
		}
		break;
	case 4:  // 오른쪽
		switch (blockShape) {
		case 0:
		case 2:
			if (map[1 + blockY][12 + blockX] != 0 || map[2 + blockY][11 + blockX] != 0) {
				blockX--;
			}
			break;
		case 1:
		case 3:
			if (map[1 + blockY][10 + blockX] != 0 || map[2 + blockY][11 + blockX] != 0 || map[3 + blockY][11 + blockX] != 0) {
				blockX--;
			}
			break;
		default:
			break;
		}
		break;
	case 5:  // 7
		switch (blockShape) {
		case 0:
			if (map[1 + blockY][11 + blockX] != 0 || map[2 + blockY][11 + blockX] != 0 || map[3 + blockY][11 + blockX] != 0) {
				blockX--;
			}
			break;
		case 1:
			if (map[1 + blockY][12 + blockX] != 0 || map[2 + blockY][10 + blockX] != 0) {
				blockX--;
			}
			break;
		case 2:
			if (map[1 + blockY][10 + blockX] != 0 || map[2 + blockY][10 + blockX] != 0 || map[3 + blockY][11 + blockX] != 0) {
				blockX--;
			}
			break;
		case 3:
			if (map[1 + blockY][12 + blockX] != 0 || map[2 + blockY][12 + blockX] != 0) {
				blockX--;
			}
			break;
		default:
			break;
		}
		break;
	case 6:  // 7거꾸로
		switch (blockShape) {
		case 0:
			if (map[1 + blockY][11 + blockX] != 0 || map[2 + blockY][10 + blockX] != 0 || map[3 + blockY][10 + blockX] != 0) {
				blockX--;
			}
			break;
		case 1:
			if (map[1 + blockY][10 + blockX] != 0 || map[2 + blockY][12 + blockX] != 0) {
				blockX--;
			}
			break;
		case 2:
			if (map[1 + blockY][11 + blockX] != 0 || map[2 + blockY][11 + blockX] != 0 || map[3 + blockY][11 + blockX] != 0) {
				blockX--;
			}
			break;
		case 3:
			if (map[1 + blockY][12 + blockX] != 0 || map[2 + blockY][12 + blockX] != 0) {
				blockX--;
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}
void GameProgress() {
	srand((unsigned)time(NULL));
	while (nextIndex != 4) {
		for (int i = 0; i < 4; i++) {
			nextblock[i] = nextblock[i + 1];
		}
		nextblock[4] = rand() % 7;
		nextIndex++;
		
	}
	if (mainIndex == 0) {
		mainblock = nextblock[0];
		mainIndex++;
		nextIndex--;
	}
	gamespeed++;
	if (gamespeed >= 3) {
		if (GetAsyncKeyState(VK_SHIFT) & 0x0001) {
			if (holdIndex == 0) {
				holdblock = mainblock;
				holdIndex++;
				mainIndex--;
			}
			else if (holduse == 0) {
				int dump;
				dump = holdblock;
				holdblock = mainblock;
				mainblock = dump;
				holduse++;
			}
		}
		if (GetAsyncKeyState(VK_BACK)) {
			scene = PAUSE;
		}
		if (GetAsyncKeyState(VK_LEFT)) {
			blockX--;
			GameLeftWall();
		}
		if (GetAsyncKeyState(VK_RIGHT)) {
			blockX++;
			GameRightWall();
		}
		if (GetAsyncKeyState(VK_DOWN)) {
			blockY++;
			GameDecision();
		}
		if (GetAsyncKeyState(VK_UP) & 0x0001) {
			blockShape++;
			if (blockShape > 3) {
				blockShape = 0;
			}
		}
		if (GetAsyncKeyState(VK_SPACE) & 0x0001) {
			while (mainIndex != 0) {
				blockY++;
				GameDecision();
			}
		}
		gamespeed = 0;
	}
	
	for (int y = 0; y < 20; y++) {
		if (map[y][7] != 0 && map[y][8] != 0 && map[y][9] != 0 && map[y][10] != 0 && map[y][11] != 0 &&
			map[y][12] != 0 && map[y][13] != 0 && map[y][14] != 0 && map[y][15] != 0 && map[y][6] != 0) {
			madeline++;
			for (int i = 0; i < y; i++) {
				for (int x = 6; x < 16; x++) {
					map[y - i][x] = map[y - i - 1][x];
				}
			}
		}
	}
	for (int y = 0; y < 20; y++) {
		if (map[y][7] != 0 || map[y][8] != 0 || map[y][9] != 0 || map[y][10] != 0 || map[y][11] != 0 ||
			map[y][12] != 0 || map[y][13] != 0 || map[y][14] != 0 || map[y][15] != 0 || map[y][6] != 0) {
			gameover++;
		}
	}
	for (int i = 0; i < 10; i++) {
		if (i == madeline / 20) {
			gamelevel = i + 1;
		}
	}
	sprintf_s(showline, "%d", madeline);
	sprintf_s(showlevel, "%d", gamelevel);
	if (gametimeMS >= 10) {
		gametimeMS10++;
		gametimeMS = 0;
	}
	if (gametimeMS10 >= 10) {
		gametimeS++;
		gametimeMS10 = 0;
	}
	if (gametimeS >= 10) {
		gametimeS10++;
		gametimeS = 0;
	}
	if (gametimeS10 >= 6) {
		gametimeM++;
		gametimeS10 = 0;
	}

	sprintf_s(showtimeMS, "%d", gametimeMS);
	sprintf_s(showtimeMS10, "%d", gametimeMS10);
	sprintf_s(showtimeS, "%d", gametimeS);
	sprintf_s(showtimeS10, "%d", gametimeS10);
	sprintf_s(showtimeM, "%d", gametimeM);

	blockspeed++;
	if (blockspeed >= 110 - (gamelevel * 10)) {
		blockY++;
		GameDecision();
		blockspeed = 0;
	}
}
void GameRelease() {
	for (int i = 0; i < BlockCount; i++) {
		free(blocks[i]);
		blocks[i] = nullptr;
	}
}