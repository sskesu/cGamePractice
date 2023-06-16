#include <stdio.h>
#include <Windows.h>

#define MENUCOUNT 4

enum Scene {
	LOGO,
	MENU,
	STAGE
};
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
enum Menu {
	START,
	Continue,
	OPTION,
	EXIT,
};
struct Obj {
	int x;
	int y;
	Color color;
	const char* shape;

};
Scene currentScene;
void Play();
void SetScene(Scene newScene);

const char* logoImg[5];
void LogoProgress();
void LogoRender();
void LogoInitialize();
void LogoRelease() {

}
Obj* menuImg[16];
Menu currentMENU;
Obj* arrow;
Obj* menu[MENUCOUNT];
void MenuSetup(int number);
void MenuProgress();
void MenuInitialize();
void MenuRender();
void MenuRelease();

void StageProgress();
void StageInitialize();


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
		Sleep(50);
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
#pragma region Play

void Play() {
	switch (currentScene) {
	case LOGO:
		LogoProgress();
		LogoRender();
		break;
	case MENU:
		MenuProgress();
		MenuRender();
		break;
	case STAGE:
		StageProgress();
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
#pragma endregion
#pragma region Logo
void LogoProgress() {
	if (GetAsyncKeyState(VK_RETURN)) {
		SetScene(MENU);
	}
}
void LogoRender() {
	for (int i = 0; i < 5; i++) {
		MoveXY(10, 3 + i);
		printf(logoImg[i]);
	}
}
void LogoInitialize() {
	logoImg[0] = "@@       @@";
	logoImg[1] = "@ @     @ @";
	logoImg[2] = "@  @   @  @";
	logoImg[3] = "@   @ @   @";
	logoImg[4] = "@    @    @";
}
#pragma endregion
#pragma region Menu
void MenuProgress() {
	if (GetAsyncKeyState(VK_UP)) {
		if (arrow->y > menu[0]->y) {
			arrow->y -= 2;
			MenuSetup(-1);
		}
	}
	if (GetAsyncKeyState(VK_DOWN)) {
		if (arrow->y < menu[3]->y) {
			arrow->y += 2;
			MenuSetup(1);
		}
	}

	if (GetAsyncKeyState(VK_SPACE)) {
		switch (currentMENU) {
		case START:
			SetScene(STAGE);
			break;
		case OPTION:
			break;
		case EXIT:
			break;
		default:
			break;
		}
	}

	//if (GetAsyncKeyState(VK_RETURN)) {
	//	SetScene(STAGE);
	//}
}
void MenuInitialize() {
	for (int i = 0; i < 16; i++) {
		menuImg[i] = (Obj*)malloc(sizeof(Obj));
		menuImg[i]->color = MAGENTA;
	}
	menuImg[0]->shape  = "MMMMMMMM               MMMMMMMMEEEEEEEEEEEEEEEEEEEEEENNNNNNNN        NNNNNNNNUUUUUUUU        UUUUUUUU";
	menuImg[1]->shape  = "M:::::::M             M:::::::ME::::::::::::::::::::EN:::::::N       N::::::NU::::::U        U::::::U";
	menuImg[2]->shape  = "M::::::::M           M::::::::ME::::::::::::::::::::EN::::::::N      N::::::NU::::::U        U::::::U";
	menuImg[3]->shape  = "M:::::::::M         M:::::::::MEE::::::EEEEEEEEE::::EN:::::::::N     N::::::NUU:::::U        U:::::UU";
	menuImg[4]->shape  = "M::::::::::M       M::::::::::M  E:::::E       EEEEEEN::::::::::N    N::::::N U:::::U        U:::::U ";
	menuImg[5]->shape  = "M:::::::::::M     M:::::::::::M  E:::::E             N:::::::::::N   N::::::N U:::::D        D:::::U ";
	menuImg[6]->shape  = "M:::::::M::::M   M::::M:::::::M  E::::::EEEEEEEEEE   N:::::::N::::N  N::::::N U:::::D        D:::::U ";
	menuImg[7]->shape  = "M::::::M M::::M M::::M M::::::M  E:::::::::::::::E   N::::::N N::::N N::::::N U:::::D        D:::::U ";
	menuImg[8]->shape  = "M::::::M  M::::M::::M  M::::::M  E:::::::::::::::E   N::::::N  N::::N:::::::N U:::::D        D:::::U ";
	menuImg[9]->shape  = "M::::::M   M:::::::M   M::::::M  E::::::EEEEEEEEEE   N::::::N   N:::::::::::N U:::::D        D:::::U ";
	menuImg[10]->shape = "M::::::M    M:::::M    M::::::M  E:::::E             N::::::N    N::::::::::N U:::::D        D:::::U ";
	menuImg[11]->shape = "M::::::M     MMMMM     M::::::M  E:::::E       EEEEEEN::::::N     N:::::::::N U::::::U      U::::::U ";
	menuImg[12]->shape = "M::::::M               M::::::MEE::::::EEEEEEEE:::::EN::::::N      N::::::::N U:::::::UUUUUU:::::::U ";
	menuImg[13]->shape = "M::::::M               M::::::ME::::::::::::::::::::EN::::::N       N:::::::N  UU::::::::::::::::UU  ";
	menuImg[14]->shape = "M::::::M               M::::::ME::::::::::::::::::::EN::::::N        N::::::N    UU::::::::::::UU    ";
	menuImg[15]->shape = "MMMMMMMM               MMMMMMMMEEEEEEEEEEEEEEEEEEEEEENNNNNNNN         NNNNNNN      UUUUUUUUUUUU     ";
	
	for (int i = 0; i < MENUCOUNT; i++) {
		menu[i] = (Obj*)malloc(sizeof(Obj));
		menu[i]->x = 25;
		menu[i]->y = 22 + i * 2;
		menu[i]->color = LIGHTGRAY;
	}
	menu[0]->shape = "   [ S T A R T ]";
	menu[1]->shape = "[ C O N T I N U E ]";
	menu[2]->shape = "  [ O P T I O N ]";
	menu[3]->shape = "    [ E X I T]";

	currentMENU = START;
	arrow = (Obj*)malloc(sizeof(Obj));
	arrow->x = 23;
	arrow->y = 22;
	arrow->color = LIGHTGRAY;
	arrow->shape = "▶";

	MenuSetup(0);
}
void MenuRender() {
	for (int i = 0; i < 16; i++) {
		MoveXY(5, 3 + i);
		ChangeColor(menuImg[i]->color);
		printf(menuImg[i]->shape);
	}

	for (int i = 0; i < MENUCOUNT; i++) {
		MoveXY(menu[i]->x, menu[i]->y);
		ChangeColor(menu[i]->color);
		printf(menu[i]->shape);
	}

	MoveXY(arrow->x, arrow->y);
	ChangeColor(arrow->color);
	printf(arrow->shape);

}
void MenuSetup(int number) {
	int index = currentMENU;
	menu[index]->color = LIGHTGRAY;
	index += number;
	currentMENU = (Menu)index;
	menu[index]->color = LIGHTGREEN;
}
void MenuRelease() {
	for (int i = 0; i < 16; i++) {
		free(menuImg[i]);
	}
	for (int i = 0; i < MENUCOUNT; i++) {
		free(menu[i]);
	}
	free(arrow);
}
#pragma endregion
#pragma region Stage
void StageProgress() {
	if (GetAsyncKeyState(VK_RETURN)) {
		SetScene(LOGO);
	}
	printf("STAGE");
}
void StageInitialize() {

}
#pragma endregion
