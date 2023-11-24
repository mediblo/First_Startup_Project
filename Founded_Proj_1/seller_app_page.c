#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>

#include "source.h"
#include "word_define.h"

void seller_app_page_setting(AData AD);

void seller_app_page(short SID, AData AD) {
	Point p = { 0,0 };
	bool flag = true, chk_url = false, chk_review = true;
	unsigned char key[2] = { 0,0 };
	int sel = 0;

	system("cls");
	seller_app_page_setting(AD);

	while (flag) {
		p.x = X_MAX / 8, p.y = Y_MAX / 3.5 + 6;
		for (int i = 0; i < 4; i++, p.y += 2) {
			gotoxy(p.x, p.y);
			switch (i) {
			case 0:
				print_choice_lang("리뷰 보기", "View Reviews", i == sel);
				break;
			case 1:
				print_choice_lang("프로그램 수정", "Edit Program", i == sel);
				break;
			}
		}

		key[0] = _getch();
		if (key[0] == K_ARROW) {
			key[1] = _getch();
			switch (key[1]) {
			case K_DOWN:
				sel = 1;
				break;
			case K_UP:
				sel = 0;
				break;
			}
		}
		else {
			switch (key[0]) {
			case 's':
			case 'S':
				sel = 1;
				break;
			case 'w':
			case 'W':
				sel = 0;
				break;
			case K_ESC:
				flag = false;
				break;
			case K_ENTER:
				switch (sel) {
				case 0: // 다운로드
					review_view_page(AD);
					break;
				case 1: // 프로그램 수정
					break;
					seller_app_page_setting(AD);
					break;
				}
			}
		}
	}

	system("cls");
}

void seller_app_page_setting(AData AD) {
	char* ext_str = output_extension(get_extension(AD.AID));
	char* gen_str = output_genre(get_genre(AD.AID));
	Point p;
	draw_box();
	draw_title(AD.name);

	draw_ESC();

	p.x = X_MAX / 8, p.y = Y_MAX / 3.5;
	gotoxy(p.x, p.y);
	printf("%s : %s", set_language ? "장르" : "Genre", gen_str);
	p.y += 2;
	gotoxy(p.x, p.y);
	printf("%s : %s", set_language ? "확장자" : "Extension", ext_str);
	p.y += 2;
	gotoxy(p.x, p.y);
	printf("%s : %d", set_language ? "매출" : "Revenue", get_revenue(AD.AID));

	p.x = X_MAX / 1.7, p.y = Y_MAX / 2.6;
	Point p2 = { p.x + 19, p.y + 4 };
	draw_lil_box(p, p2);

	p.x = X_MAX / 1.7, p.y = Y_MAX / 2.6;
	gotoxy(p.x, p.y);
	for (int i = 0; AD.explanation[i] != '\0'; i++) {
		printf("%c", AD.explanation[i]);
		if ((i + 1) % 20 == 0) gotoxy(p.x, ++p.y);
	}
}