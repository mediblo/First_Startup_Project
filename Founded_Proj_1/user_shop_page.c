#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>

#include "source.h"
#include "word_define.h"

void shop_page_setting();
int shop_page(short UID) {
	AData temp_AD[5];
	temp_AD[0].AID = -1;
	Point p = { 20, 10 };
	short page_num = 0, page = 2;
	unsigned char key[2] = { 0,0 };
	bool flag = false, page_flag = true;
	int i = 0, temp_num = 0;
	int sel = 0;
	int user_money = get_money(UID);

	char* sel_arrow[2] = { "<--", "-->" };

	shop_page_setting();
	
	while (page == 2) {
		if (page_flag) {
			temp_num = 0;
			i = 0;
			flag = false;
			// 5개 앱을 하나의 페이지에 있을 수 있도록 프로그램 아이디 및 AID 추출
			// 페이지 인식은 어떻게?
			for (App* temp = root_app; temp != NULL; temp = temp->next, i++) {
				if (page_num * 5 == i) flag = true;
				if (flag) {
					if (temp->lang_set == 0) {
						strcpy(temp_AD[temp_num].name, set_language ? temp->kor_name : temp->eng_name);
						strcpy(temp_AD[temp_num].explanation, set_language ? temp->kor_explanation : temp->eng_explanation);
					}
					else {
						strcpy(temp_AD[temp_num].name, temp->lang_set == 1 ? temp->kor_name : temp->eng_name);
						strcpy(temp_AD[temp_num].explanation, temp->lang_set == 1 ? temp->kor_explanation : temp->eng_explanation);
					}
					temp_AD[temp_num].AID = temp->AID;
					temp_AD[temp_num++].price = temp->price;
				}
				if (temp_num == 5) break;
			}
			if (temp_num != 5) for (int j = temp_num; j < 5; j++) temp_AD[j].AID = -1;
			page_flag = false;

			if (temp_num - 1 <= sel) sel = temp_num - 1;
		}

		// 출력 부분
		p.x = X_MAX - 1 - (strlen(set_language ? "F8 검색" : "F8 Search")), p.y = 1;
		gotoxy(p.x, p.y);
		choice_color(lightRed, lightGray, "F8 ");
		choice_color(black, lightGray, set_language ? "검색" : "Search");

		p.x = X_MAX / 7, p.y = Y_MAX / 4;
		for (int i = 0; i < 5; i++, p.y += 2) {
			gotoxy(p.x, p.y);
			if (temp_AD[i].AID == -1) continue;
			else
				i == sel ? select_color(temp_AD[i].name) : printf("%s",temp_AD[i].name);
		}

		p.y += 4;
		for (int i = 0; i < 2; i++, p.x += 4) {
			gotoxy(p.x, p.y);
			if((page_num != 0 && i == 0) || ( temp_num == 5 && i == 1))
				printf("%s", sel_arrow[i]);
		}
		p.x = X_MAX / 8, p.y += 2;
		gotoxy(p.x, p.y);
		printf("[ %03d/%03d ]", page_num + 1, (AID_count / 5) + 1);

		// 설명창 인식
		// 기존 설명창 제거
		p.x = X_MAX / 1.7, p.y = Y_MAX / 2.3;
		gotoxy(p.x, p.y);
		for (int i = 0; i < 100; i++) {
			printf(" ");
			if ((i + 1) % 20 == 0) gotoxy(p.x, ++p.y);
		}
		p.x = X_MAX / 1.7, p.y = Y_MAX / 2.3;
		gotoxy(p.x, p.y); // sel -> 무언가로 변경해야함 [ 그대로 하기로 함 ]
		for (int i = 0; temp_AD[sel].explanation[i] != '\0'; i++) {
			printf("%c", temp_AD[sel].explanation[i]);
			if ((i + 1) % 20 == 0) gotoxy(p.x, ++p.y);
		}
		p.x = X_MAX / 1.7, p.y = Y_MAX / 1.5;
		gotoxy(p.x, p.y++);
		printf("%s :%10d", set_language ? "가격" : "Price", temp_AD[sel].price);
		gotoxy(p.x, ++p.y);
		printf("%s :%10d", set_language ? "보유 자산" : "Money", user_money);

		// 입력 부분	
		// 키 입력 이벤트 처리
		// <- -> 는 페이지 처리로 알아서 하도록
		key[0] = _getch();
		if (key[0] == K_ARROW || key[0] == 0) {
			key[1] = _getch();
			switch (key[1]) {
			case K_F1:
			case K_F2:
			case K_F3:
				page = key[1] - K_F1;
				break;
			case K_DOWN:
				sel = sel == temp_num - 1 ? temp_num - 1 : sel + 1;
				break;
			case K_UP:
				sel = sel == 0 ? 0 : sel - 1;
				break;
			case K_LEFT:
				if (page_num != 0) {
					page_num--;
					page_flag = true;
					system("cls");
					shop_page_setting();
				}
				break;
			case K_RIGHT:
				if (temp_num == 5) {
					page_num++;
					page_flag = true;
					system("cls");
					shop_page_setting();
				}
				break;
			}
		}
		else {
			switch (key[0]) {
			case 's':
			case 'S':
				sel = sel == temp_num - 1 ? temp_num - 1 : sel + 1;
				break;
			case 'w':
			case 'W':
				sel = sel == 0 ? 0 : sel - 1;
				break;
			case 'a':
			case 'A':
				if (page_num != 0) {
					page_num--;
					page_flag = true;
					system("cls");
					shop_page_setting();
				}
				break;
			case 'd':
			case 'D':
				if (temp_num == 5) {
					page_num++;
					page_flag = true;
					system("cls");
					shop_page_setting();
				}
				break;
			case K_ENTER:
				if (user_money < temp_AD[sel].price)
					draw_message(set_language ? "돈이 부족합니다!" : "Not Enough Money!");
				else {

				}
				return -10;
			}
		}
	}

	return -10;
}
// 기본 UI 출력
void shop_page_setting() {
	Point p;
	draw_page();
	draw_box();
	if (set_language) draw_title("상점 페이지");
	else draw_title("SHOP PAGE");
	p.x = X_MAX / 1.7, p.y = Y_MAX / 2.3;
	Point p2 = { p.x + 19, p.y + 4 };
	draw_lil_box(p, p2);
}