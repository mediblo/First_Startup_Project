// 스크랩해와서 사용하는 함수 또는 그것들을 이용해 제작한 함수들
// 대부분 windows UI 관련 함수

#include <stdio.h>
#include <windows.h>
#include <conio.h>

#include "word_define.h"

void textcolor(Color_num foreground, Color_num background);
void gotoxy(int x, int y);
void select_color(char* str);
void choice_color(Color_num t_color, Color_num bg_color, char* str);
void print_choice_lang(const char* kor, const char* eng, bool choice);
void disable_color(char* str);

void textcolor(Color_num foreground, Color_num background) {
    int color = foreground + (background << 4);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void select_color(char* str) {
	Color_num t_color = black, bg_color = white;
	textcolor(t_color, bg_color);
	printf("%s", str);
	t_color = white, bg_color = black;
	textcolor(t_color, bg_color);
}

void choice_color(Color_num t_color, Color_num bg_color, char* str) {
	textcolor(t_color, bg_color);
	printf("%s", str);
	t_color = white, bg_color = black;
	textcolor(t_color, bg_color);
}

void print_choice_lang(const char* kor, const char* eng, bool choice) {
	if (set_language) {
		if (choice) select_color(kor);
		else printf("%s", kor);
	}
	else {
		if (choice) select_color(eng);
		else printf("%s", eng);
	}
}

void disable_color(char* str) {
	Color_num t_color = darkGray, bg_color = black;
	textcolor(t_color, bg_color);
	printf("%s", str);
	t_color = white;
	textcolor(t_color, bg_color);
}