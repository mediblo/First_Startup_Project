#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>

#include "source.h"
#include "word_define.h"

int library_page(short UID);

int library_page(short UID) {
	AData temp_AD[5];
	temp_AD[0].AID = -1;
	Point p = { 20, 10 };
	short page_num = 0;
	bool flag = false;
	int i = 0, temp_num = 0;

	draw_page();
	draw_box();
	if (set_language) draw_title("라이브러리 페이지");
	else draw_title("LIBRARY PAGE");

	// 5개 페이지에 있는 프로그램 아이디 및 AID 추출
	for (App * temp = root_app; temp != NULL; temp = temp->next, i++) {
		if (page_num * 5 == i) flag = true;
		if (flag) {
			if (temp->lang_set == 0) {
			strcpy(temp_AD[temp_num++].name, set_language ? temp->kor_name : temp->eng_name);
			temp_AD->AID = temp->AID;
		}
		else {
			strcpy(temp_AD[temp_num++].name, temp->lang_set == 1 ? temp->kor_name : temp->eng_name);
			temp_AD->AID = temp->AID;
		}

		}
		if (temp_num == 5) break;
	}
	if (temp_num != 5) temp_AD[temp_num].AID = -1;

	return 0;
}