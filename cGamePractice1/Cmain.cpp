#include <stdio.h>
#include <Windows.h>

enum Scene {
	LOGO,
	MENU,
	STAGE
};

Scene currentScene;
void Play();
void SetScene(Scene newScene);


const char* LogoImg[5];
void Logo();
void LogoRender();
void LogoInitialize();

void Menu();
void MenuInitialize();

void Stage();
void StageInitialize();


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
//커서숨기기
void HideCursor();
//좌표받고이동
void MoveXY(int x, int y);
//색전환
void ChangeColor(int color);


int main() {
	SetScene(LOGO);
	HideCursor();
	while (true) {
		system("cls");
		Play();
		Sleep(10);
	}
	return 0;
}

#pragma region WinAPI
void HideCursor()
{
	CONSOLE_CURSOR_INFO Info;
	Info.dwSize = 1;
	Info.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

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

#pragma endregion
void Play() {
	switch (currentScene) {
	case LOGO:
		Logo();
		LogoRender();
		break;
	case MENU:
		Menu();
		break;
	case STAGE:
		Stage();
		break;
	default:
		break;
	}
}
void SetScene(Scene newScene) {
	currentScene = newScene;
	switch (currentScene) {
	case LOGO:
		LogoInitialize();
		break;
	case MENU:
		MenuInitialize();
		break;
	case STAGE:
		StageInitialize();
		break;
	default:
		break;
	}
}
#pragma region Logo
void Logo() {
	if (GetAsyncKeyState(VK_RETURN)) {
		SetScene(MENU);
	}
}
void LogoRender() {
	for (int i = 0; i < 5; i++) {
		MoveXY(10, 3 + i);
		printf(LogoImg[i]);
	}
}
void LogoInitialize() {
	LogoImg[0] = "@@       @@";
	LogoImg[1] = "@ @     @ @";
	LogoImg[2] = "@  @   @  @";
	LogoImg[3] = "@   @ @   @";
	LogoImg[4] = "@    @    @";
}
#pragma endregion
#pragma region Menu
void Menu() {
	if (GetAsyncKeyState(VK_RETURN)) {
		SetScene(STAGE);
	}
	printf("MENU");
}
void MenuInitialize() {

}
#pragma endregion
#pragma region Stage
void Stage() {
	if (GetAsyncKeyState(VK_RETURN)) {
		SetScene(LOGO);
	}
	printf("STAGE");
}
void StageInitialize() {

}
#pragma endregion
