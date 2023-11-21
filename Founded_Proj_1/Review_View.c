#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>

#include "source.h"
#include "word_define.h"

void review_view_page(AData AD) {
	RData temp_RD[3];
	short sel = 0, i = 0, temp_num = 0, page_num = 0;
	bool page_flag = true, flag = false, view_flag = true;
	Point p = { 0,0 };
	short r_count = 0;
	float sum_rate = 0;
	char* sel_arrow[2] = { "<--", "-->" };
	unsigned char key[2] = { 0, 0 };

	while(view_flag){
		if (page_flag) {
			temp_num = 0;
			i = 0;
			flag = false;
			r_count = 0;
			sum_rate = 0;

			for (Review* temp = root_review; temp != NULL; temp = temp->next) {
				if (temp->AID == AD.AID) {
					r_count++;
					sum_rate += temp->rate;
					if (page_num * 3 == i) flag = true;
					i++;
					if (flag && temp_num < 3) {
						strcpy(temp_RD[temp_num].comment, temp->comment);
						strcpy(temp_RD[temp_num].name, get_name(temp->UID));
						temp_RD[temp_num++].rate = get_rate(temp->UID, temp->AID);
					}
				}
			}

			if (i == 0) { // 리뷰가 없을 때
				p.x = X_MAX / 2.8, p.y = Y_MAX / 2 - 1;
				system("cls");
				draw_box();
				draw_button(p, set_language ? "아무도 리뷰를 작성하지 않았습니다." : "No one has written a review.");
				Sleep(1000);
				system("cls");
				return 0; // 돌아가거라
			}
			if (temp_num != 3) for (int j = temp_num; j < 3; j++) temp_RD[j].rate = -1;
			page_flag = false;

			if (temp_num - 1 <= sel) sel = temp_num - 1;

			// 기본 출력
			system("cls");
			draw_box();
			draw_title(AD.name);
			p.x = 2, p.y = 1;
			gotoxy(p.x, p.y);
			choice_color(lightRed, lightGray, "ESC ");
			choice_color(black, lightGray, set_language ? "뒤로가기" : "Back");
			p.x = X_MAX * 0.46 , p.y = 6;
			gotoxy(p.x, p.y);
			printf("%.2f/10.00", sum_rate / (float)r_count);

			r_count = r_count % 3 == 0 ? r_count / 3 : r_count / 3 + 1;

			// 설명창 인식
			// 기존 설명창 제거
			for (int j = 0; j < 3; j++) {
				if (temp_RD[j].rate == -1) continue;

				p.x = X_MAX * (0.1 + (0.3 * j)), p.y = Y_MAX / 2.3 - 3;
				gotoxy(p.x, p.y++);
				printf("%s      ", temp_RD[j].name);
				gotoxy(p.x, p.y++);
				printf("%d/10      ", temp_RD[j].rate);
				p.y++;

				Point p2 = { p.x + 19, p.y + 4 };
				draw_lil_box(p, p2);

				gotoxy(p.x, p.y);
				for (int i = 0; i < 100; i++) {
					printf(" ");
					if ((i + 1) % 20 == 0) gotoxy(p.x, ++p.y);
				}
				p.x = X_MAX * (0.1 + (0.3 * j)), p.y = Y_MAX / 2.3;
				gotoxy(p.x, p.y);
				for (int i = 0; temp_RD[j].comment[i] != '\0'; i++) {
					printf("%c", temp_RD[j].comment[i]);
					if ((i + 1) % 20 == 0) gotoxy(p.x, ++p.y);
				}
			}

			p.x = X_MAX * 0.5 - 2, p.y = Y_MAX - 7;
			for (int i = 0; i < 2; i++, p.x += 4) {
				gotoxy(p.x, p.y);
				if ((page_num != 0 && i == 0) || (page_num + 1 != r_count && i == 1))
					printf("%s", sel_arrow[i]);
				else printf("   ");
			}

			p.x = X_MAX * 0.5 - 4, p.y += 2;
			gotoxy(p.x, p.y);
			printf("[ %03d/%03d ]", page_num + 1, r_count);
		}

		key[0] = _getch();
		if (key[0] == K_ARROW) {
			key[1] = _getch();
			switch (key[1]) {
				case K_LEFT:
					if (page_num != 0) {
						page_num--;
						page_flag = true;
					}
					break;
				case K_RIGHT:
					if (page_num + 1 != r_count) {
						page_num++;
						page_flag = true;
					}
					break;
			}
		}
		else {
			switch (key[0]) {
			case 'a':
			case 'A':
				if (page_num != 0) {
					page_num--;
					page_flag = true;
				}
				break;
			case 'd':
			case 'D':
				if (page_num + 1 != r_count) {
					page_num++;
					page_flag = true;
				}
				break;
			case K_ESC:
				view_flag = false;
				break;
			}
		}
	}
	system("cls");
}