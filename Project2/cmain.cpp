#include<stdio.h>
#include<windows.h>
#include<time.h>

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

typedef struct Obj {
	int x;
	int y;
	const char* shape;
	Color color;
} *Start;
Start StartImg[7] = {};
Start StartMenu[3] = {};

#pragma region Winapi
void MoveXY(int x, int y);
void ChangeColor(int color);
void HideCursor();
#pragma endregion
#pragma region DoubleBuffer
#define BufferWidth 80
#define BufferHeight 60

HANDLE hBuffer[2];
int screenIndex;

void InitBuffer();
void WriteBuffer(int x, int y, const char* shape, int color);
void FlipBuffer();
void ClearBuffer();
void DestroyBuffer();
#pragma endregion


void StartInitialize();
void StartRender();
void StartRelease();




int main() {

	StartInitialize();
	InitBuffer();

	ULONGLONG time = GetTickCount64();
	while (true) {
		if (time + 50 <= GetTickCount64()) {
			StartRender();
		

			FlipBuffer();
			ClearBuffer();
			time = GetTickCount64();
		}
	}

	StartRelease();
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

void StartInitialize() {

	srand((unsigned)time(NULL));

	for (int i = 0; i < 7; i++) {
		StartImg[i] = (Start)malloc(sizeof(Obj));
		StartImg[i]->x = 10;
		StartImg[i]->y = 5 + i;
		StartImg[i]->color = LIGHTBLUE;
	}

	StartImg[0]->shape = " ######   #######  ######   ######    ####     #####  ";
	StartImg[1]->shape = " # ## #    ##   #  # ## #    ##  ##    ##     ##   ## ";
	StartImg[2]->shape = "   ##      ## #      ##      ##  ##    ##     #       ";
	StartImg[3]->shape = "   ##      ####      ##      #####     ##      #####  ";
	StartImg[4]->shape = "   ##      ## #      ##      ## ##     ##          ## ";
	StartImg[5]->shape = "   ##      ##   #    ##      ##  ##    ##     ##   ## ";
	StartImg[6]->shape = "  ####    #######   ####    #### ##   ####     #####  ";

	for (int i = 0; i < 3; i++) {
		StartMenu[i] = (Start)malloc(sizeof(Obj));
		StartMenu[i]->x = 30;
		StartMenu[i]->y = 15 + i;
		StartMenu[i]->color = LIGHTGRAY;
	}

	StartMenu[0]->shape = "  Start ";
	StartMenu[1]->shape = "Continue";
	StartMenu[2]->shape = "  Quit  ";

}
void StartRender() {
	for (int i = 0; i < 7; i++) {
		WriteBuffer(StartImg[i]->x, StartImg[i]->y, StartImg[i]->shape, StartImg[i]->color);
	}
	for (int i = 0; i < 3; i++) {
		WriteBuffer(StartMenu[i]->x, StartMenu[i]->y, StartMenu[i]->shape, StartMenu[i]->color);
	}
}

void StartRelease() {
	for (int i = 0; i < 7; i++) {
		free(StartImg[i]);
		StartImg[i] = nullptr;
	}
	for (int i = 0; i < 3; i++) {
		free(StartMenu[i]);
		StartMenu[i] = nullptr;
	}
}
//WriteBuffer(x, y, shape, color)