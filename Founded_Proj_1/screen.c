﻿// 큰 범위로 그리는 함수들
// Ex ) 프로그램 틀, 타이틀, 메시지 등

#include <stdio.h>
#include <Windows.h>
#include <conio.h>

#include "source.h"
#include "word_define.h"

#pragma warning(disable:4244) // double -> int 변환 손실 에러 처리
#pragma warning(disable:4267) // size_t -> int 변환 손실 에러 처리

void draw_box();
void draw_title(const char title_name[]);
void draw_message(char* message);
void draw_page();
void draw_seller_page();
void draw_button(Point p, char* str);
void draw_quit();
int popup_Explantion(char* msg);

void draw_box() {
	for (int y = 0; y < Y_MAX; y++) {
		for (int x = 1; x < X_MAX; x++) {
			gotoxy(x, y);
			if (x == 1 && y == 0) printf("┌");
			else if (x == X_MAX - 1 && y == 0) printf("┐");
			else if (x == 1 && y == Y_MAX - 1) printf("└");
			else if (x == X_MAX - 1 && y == Y_MAX - 1) printf("┘");
			else if (y == 0 || y == Y_MAX - 1) printf("─");
			else if (x == 1 || x == X_MAX - 1) printf("│");
		}
	}
}

void draw_title(const char title_name[]) {
	int title_len = strlen(title_name);
	Point p = { 0,0 };
	p.x += X_MAX / 2 - title_len / 2;
	p.y += 3;

	for (int y = 0; y < 3; y++) {
		gotoxy(p.x, p.y + y);
		switch (y) {
		case 0:
			printf("┌");
			for (int i = 0; i < title_len; i++) printf("─");
			printf("┐");
			break;
		case 1:
			printf("│%s│", title_name);
			break;
		case 2:
			printf("└");
			for (int i = 0; i < title_len; i++) printf("─");
			printf("┘");
			break;
		}
	}
}

void draw_message(char* message) {
	system("cls");
	draw_box();
	Point p = { 0,0 };
	p.x = X_MAX / 2 - strlen(message) / 2 - 1;
	p.y = Y_MAX / 2 - 1;

	for (int y = 0; y < 3; y++) {
		gotoxy(p.x, p.y + y);
		switch (y) {
			case 0:
				printf("┌");
				for (int i = 0; i < strlen(message); i++) printf("─");
				printf("┐");
				break;
			case 1:
				printf("│%s│", message);
				break;
			case 2:
				printf("└");
				for (int i = 0; i < strlen(message); i++) printf("─");
				printf("┘");
				break;
		}
	}
	Sleep(1000);
	system("cls");
}

void draw_page() {
	char* eng_page[3] = { "MY PAGE","LIBRARY","STORE" };
	char* kor_page[3] = { "마이 페이지","라이브러리","상점" };

	char num_page[3][3] = { "F1", "F2","F3" };
	Point p = { 2,1 };
	gotoxy(p.x, p.y);

	for (int i = 0; i < 3; i++) {
		choice_color(lightRed, lightGray, num_page[i]);
		choice_color(black, lightGray, " ");
		if (set_language) choice_color(black, lightGray, kor_page[i]);
		else choice_color(black, lightGray, eng_page[i]);
		if (i != 2) choice_color(black, lightGray, "  ");
	}
}

void draw_seller_page() {
	char* eng_page[2] = { "MY PAGE","LIBRARY" };
	char* kor_page[2] = { "마이 페이지","라이브러리" };

	char num_page[2][3] = { "F1", "F2" };
	Point p = { 2,1 };
	gotoxy(p.x, p.y);

	for (int i = 0; i < 2; i++) {
		choice_color(lightRed, lightGray, num_page[i]);
		choice_color(black, lightGray, " ");
		if (set_language) choice_color(black, lightGray, kor_page[i]);
		else choice_color(black, lightGray, eng_page[i]);
		if (i != 2) choice_color(black, lightGray, "  ");
	}
}

void draw_button(Point p, char* str) {
	short len_str = strlen(str);

	for (int y = 0; y < 3; y++) {
		gotoxy(p.x, p.y + y);
		switch (y) {
		case 0:
			printf("┌");
			for (int i = 0; i < len_str; i++) printf("─");
			printf("┐");
			break;
		case 1:
			printf("│%s│", str);
			break;
		case 2:
			printf("└");
			for (int i = 0; i < len_str; i++) printf("─");
			printf("┘");
			break;
		}
	}
}

void draw_quit() {
	char* kor_message = "정상 종료 되었습니다.";
	char* eng_message = "Program has exited successfully";
	system("cls");
	Point p = { 0,0 };
	int len_msg = strlen(set_language ? kor_message : eng_message);
	p.x = X_MAX / 2 - len_msg / 2 - 1;
	p.y = Y_MAX / 2 - 1;

	for (int y = 0; y < 3; y++) {
		gotoxy(p.x, p.y + y);
		switch (y) {
		case 0:
			printf("┌");
			for (int i = 0; i < len_msg; i++) printf("─");
			printf("┐");
			break;
		case 1:
			printf("│%s│", set_language ? kor_message : eng_message);
			break;
		case 2:
			printf("└");
			for (int i = 0; i < len_msg; i++) printf("─");
			printf("┘");
			break;
		}
	}
	gotoxy(0,Y_MAX - 3);
}

int popup_Explantion(char* msg) {
	system("cls");
	draw_box();
	draw_title(set_language ? "확인 팝업" : "Check Popup");
	char* str_k[2] = {"뒤로", "변경"};
	char* str_e[2] = { "Back", "Change" };
	Point p = { 0, 0 };
	int len_msg = strlen(msg);

	unsigned char key[2] = { 0, 0 };
	int select = 0;

	p.x = X_MAX / 2.5;
	p.y = Y_MAX / 2 - 6;
	
	gotoxy(p.x, p.y);
	for (int i = 0; msg[i] !='\0'; i++) {
		printf("%c", msg[i]);
		if ((i + 1) % 20 == 0) {
			p.x = X_MAX / 2.5;
			p.y++;
			gotoxy(p.x, p.y);
		}
	}
	while (1) {
		p.x = X_MAX / 2.2 - 4;
		p.y = Y_MAX / 1.6;
		for (int i = 0; i < 2; i++, p.x+=8) {
			gotoxy(p.x, p.y);
			print_choice_lang(str_k[i], str_e[i], select == i);
		}

		key[0] = _getch();
		if (key[0] == K_ARROW) {
			key[1] = _getch();
			switch (key[1]) {
				case K_LEFT:
					select = 0;
					break;
				case K_RIGHT:
					select = 1;
					break;
			}
		}
		switch (key[0]) {
			case 'a':
			case 'A':
				select = 0;
				break;
			case 'd':
			case 'D':
				select = 1;
				break;
			case K_ENTER:
				system("cls");
				return select ? 1 : 0;
		}
	}
	error(7);
}