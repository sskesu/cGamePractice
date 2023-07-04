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
typedef struct Block {
	int x;
	int y;
	const char* shape[4][4];
	Color color;
};
Block* blocks[1];

#define BufferWidth 140
#define BufferHeight 40
HANDLE hBuffer[2];
int screenIndex;
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
int main() {
	blocks[0] = (Block*)malloc(sizeof(Block));
	blocks[0]->x = 0;
	blocks[0]->y = 0;
	blocks[0]->shape[0][0] = "        ";
	blocks[0]->shape[0][1] = "        ";
	blocks[0]->shape[0][2] = "бсбсбсбс";
	blocks[0]->shape[0][3] = "        ";
	blocks[0]->shape[1][0] = "  бс    ";
	blocks[0]->shape[1][1] = "  бс    ";
	blocks[0]->shape[1][2] = "  бс    ";
	blocks[0]->shape[1][3] = "  бс    ";
	blocks[0]->color = LIGHTCYAN;
	while (true) {
		for (int i = 0; i < 4; i++) {
			WriteBuffer(blocks[0]->x, blocks[0]->y, blocks[0]->shape[0][i], blocks[0]->color);
		}
	}
	return 0;
}