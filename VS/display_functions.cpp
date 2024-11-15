#include "display_functions.h"
#include <iostream>
#include <windows.h>

using namespace std;


void centerText(const string text, bool endline, int add) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int consoleWidth;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	int padding = (consoleWidth - (text.length() + add)) / 2;

	cout << string(padding > 0 ? padding : 0, ' ') << text;
	if (endline) {
		cout << endl;
	}
}

void displayTitle() {
	centerText(" _____                                                                            _____ ", true, 0);
	centerText("( ___ )                                                                          ( ___ )", true, 0);
	centerText(" |   |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|   | ", true, 0);
	centerText(" |   |                                                                            |   | ", true, 0);
	centerText(" |   |           ____            __                  __                           |   | ", true, 0);
	centerText(" |   |          / __ \\___  _____/ /________  _______/ /____  __  _______          |   | ", true, 0);
	centerText(" |   |         / / / / _ \\/ ___/ __/ ___/ / / / ___/ __/ _ \\/ / / / ___/          |   | ", true, 0);
	centerText(" |   |        / /_/ /  __(__  / /_/ /  / /_/ / /__/ /_/  __/ /_/ / /              |   | ", true, 0);
	centerText(" |   |       /_____/\\___/____/\\__/_/   \\__,_/\\___/\\__/\\___/\\__,_/_/               |   | ", true, 0);
	centerText(" |   |    ____/ ( )___  _________  _______  _______/ /____  ____ ___  ___  _____  |   | ", true, 0);
	centerText(" |   |   / __  /|// _ \\/ ___/ __ \\/ ___/ / / / ___/ __/ _ \\/ __ `__ \\/ _ \\/ ___/  |   | ", true, 0);
	centerText(" |   |  / /_/ /  /  __/ /__/ /_/ (__  / /_/ (__  / /_/  __/ / / / / /  __(__  )   |   | ", true, 0);
	centerText(" |   |  \\__,_/   \\___/\\___/\\____/____/\\__, /____/\\__/\\___/_/ /_/ /_/\\___/____/    |   | ", true, 0);
	centerText(" |   |                               /____/                                       |   | ", true, 0);
	centerText(" |   |                                                                            |   |", true, 0);
	centerText(" |___|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|___| ", true, 0);
	centerText("(_____)                                                                          (_____)", true, 0);
}

void displayLittleTitle() {
	centerText(" ____            _                   _                        _ _                              _                           ", true, 0);
	centerText("|  _ \\  ___  ___| |_ _ __ _   _  ___| |_ ___ _   _ _ __    __| ( ) ___  ___ ___  ___ _   _ ___| |_ ___ _ __ ___   ___  ___ ", true, 0);
	centerText("| | | |/ _ \\/ __| __| '__| | | |/ __| __/ _ \\ | | | '__|  / _` |/ / _ \\/ __/ _ \\/ __| | | / __| __/ _ \\ '_ ` _ \\ / _ \\/ __|", true, 0);
	centerText("| |_| |  __/\\__ \\ |_| |  | |_| | (__| ||  __/ |_| | |    | (_| | |  __/ (_| (_) \\__ \\ |_| \\__ \\ ||  __/ | | | | |  __/\\__ \\", true, 0);
	centerText("|____/ \\___||___/\\__|_|   \\__,_|\\___|\\__\\___|\\__,_|_|     \\__,_|  \\___|\\___\\___/|___/\\__, |___/\\__\\___|_| |_| |_|\\___||___/", true, 0);
	centerText("                                                                                     |___/                                 ", true, 0);
}


void clearScreen() {
	system("cls");
}

void setColorText(int textColor) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	int color = (csbi.wAttributes & 0xF0) | textColor;
	SetConsoleTextAttribute(hConsole, color);
}

void setColorBg(int bgColor) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	int color = (csbi.wAttributes & 0x0F) | (bgColor << 4);
	SetConsoleTextAttribute(hConsole, color);
}