#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>

#include "source.h"
#include "word_define.h"

void app_page_setting(AData AD);

void app_page(short UID, AData AD) {
	Point p = { 0,0 };
	bool review_flag = is_write_review(UID, AD.AID);
	bool report_flag = is_report_write(AD.AID, UID);
	bool flag = true, chk_url = false, chk_review = true;
	unsigned char key[2] = { 0,0 };
	int sel = 0;
	char rate = 0;
	char temp_review[101] = "";
	char temp_report = 0;

	if (review_flag) {
		rate = get_rate(UID, AD.AID);
		strcpy(temp_review, get_comment(UID, AD.AID));
	}
	if (report_flag) temp_report = get_report_reason(AD.AID, UID);

	system("cls");
	app_page_setting(AD);

	while(flag){
		p.x = X_MAX / 8, p.y = Y_MAX / 3.5+6;
		for(int i=0; i<4; i++, p.y+=2){
			gotoxy(p.x, p.y);
			switch(i){
				case 0:
					print_choice_lang("다운로드", "Download", i == sel);
					break;
				case 1:
					print_choice_lang("리뷰 보기", "View Reviews", i == sel);
					break;
				case 2:
					print_choice_lang("리뷰 달기", "Write a Review", i == sel);
					break;
				case 3:
					print_choice_lang("신고하기", "Report", i == sel);
					break;
			}
		}

		key[0] = _getch();
		if (key[0] == K_ARROW) {
			key[1] = _getch();
			switch (key[1]) {
				case K_DOWN:
					sel = sel == 3 ? 3 : sel + 1;
					break;
				case K_UP:
					sel = sel == 0 ? 0 : sel - 1;
					break;
			}
		}
		else {
			switch (key[0]) {
			case 's':
			case 'S':
				sel = sel == 3 ? 3 : sel + 1;
				break;
			case 'w':
			case 'W':
				sel = sel == 0 ? 0 : sel - 1;
				break;
			case K_ESC:
				flag = false;
				break;
			case K_ENTER:
				switch (sel) {
					case 0: // 다운로드
						if (is_hav_file(get_extension(AD.AID), AD.name))
							draw_message(set_language ? "이미 파일이 존재합니다!" : "The file already exists!");
						else {
							update_AID_D_count(UID, AD.AID, false);
							if (AD.price == 0) delete_AID_D(UID, AD.AID);
							chk_url = check_url(
								get_URL(AD.AID), get_extension(AD.AID), AD.name);
							if (chk_url == 1) // 성공
								draw_message(set_language ? "다운로드 완료." : "Download Complete");
							else // 나머진 실패
								draw_message(set_language ? "다운로드 실패." : "Download Fail");
						}
						break;
					case 1: // 리뷰 보기
						review_view_page(AD);
						break;
					case 2: // 리뷰 달기
 						if (review_flag) chk_review = popup_review(temp_review, rate);
						if (chk_review) {
							input_blank_some(set_language ? "리뷰" : "Review", temp_review, sizeof(temp_review));
							rate = set_rate();
							if (review_flag)
								update_review(UID, AD.AID, temp_review, rate);
							else
								insert_review(UID, AD.AID, temp_review, rate);
						}
						review_flag = true;
						break;
					case 3: // 신고 하기
						temp_report = input_report(temp_report, UID, AD.AID, report_flag);
						report_flag = true;
						break;
				}
				app_page_setting(AD);
				break;
			}
		}
	}
	system("cls");
}

void app_page_setting(AData AD) {
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
	printf("%s : %d", set_language ? "다운 가능 횟수" : "Download Limit", AD.price);

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