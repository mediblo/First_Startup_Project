#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>

#include "source.h"
#include "word_define.h"

int compare(const void* a, const void* b);
void library_page_setting();

int library_page(short UID) {
	AData temp_AD[5];
	Point p = { 20, 10 };
	short page_num = 0, page = 1;
	unsigned char key[2] = { 0,0 };
	bool flag = false, page_flag = true;
	int i = 0, l = 0, temp_num = 0;
	int sel = 0, chk_url = 0;
	int page_AID[5];

	char* sel_arrow[2] = { "<--", "-->" };

	while (page == 1) {
		if (page_flag) {
			temp_num = 0;
			i = 0;
			flag = false;

			for (AID_D* temp = root_AID_D; temp != NULL && temp_num < 5; temp = temp->next) {
				if (temp->UID == UID) {
					if (page_num * 5 == i) flag = true;
					i++;
					if(flag){
						strcpy(temp_AD[temp_num].name, temp->AD.name);
						strcpy(temp_AD[temp_num].explanation, temp->AD.explanation);
						temp_AD[temp_num].AID = temp->AD.AID;
						temp_AD[temp_num++].price = temp->AD.price;
					}
				}
			}

			if (i == 0) { // ������ ���α׷��� ���� ��
				p.x = X_MAX / 2.8, p.y = Y_MAX / 2 - 1;
				draw_box();
				draw_button(p, set_language ? "������ ���α׷��� �����ϴ�." : "No purchased programs");
				Sleep(1000);
				return 0; // ������������ ���ư��Ŷ�
			}
			if (temp_num != 5) for (int j = temp_num; j < 5; j++) temp_AD[j].AID = -1;
			page_flag = false;

			if (temp_num - 1 <= sel) sel = temp_num - 1;
		}

		// ��� �κ�
		library_page_setting();
		p.x = X_MAX - 1 - (strlen(set_language ? "F8 �˻�" : "F8 Search")), p.y = 1;
		gotoxy(p.x, p.y);
		choice_color(lightRed, lightGray, "F8 ");
		choice_color(black, lightGray, set_language ? "�˻�" : "Search");

		p.x = X_MAX / 7, p.y = Y_MAX / 4;
		for (int i = 0; i < 5; i++, p.y += 2) {
			gotoxy(p.x, p.y);
			if (temp_AD[i].AID == -1) continue;
			else
				i == sel ? select_color(temp_AD[i].name) : printf("%s", temp_AD[i].name);
		}

		p.y += 4;
		for (int i = 0; i < 2; i++, p.x += 4) {
			gotoxy(p.x, p.y);
			if ((page_num != 0 && i == 0) || (temp_num == 5 && i == 1))
				printf("%s", sel_arrow[i]);
		}
		p.x = X_MAX / 8, p.y += 2;
		gotoxy(p.x, p.y);
		printf("[ %03d/%03d ]", page_num + 1, (AID_count / 5) + 1);

		// ����â �ν�
		// ���� ����â ����
		p.x = X_MAX / 1.7, p.y = Y_MAX / 2.3;
		gotoxy(p.x, p.y);
		for (int i = 0; i < 100; i++) {
			printf(" ");
			if ((i + 1) % 20 == 0) gotoxy(p.x, ++p.y);
		}
		p.x = X_MAX / 1.7, p.y = Y_MAX / 2.3;
		gotoxy(p.x, p.y); // sel -> ���𰡷� �����ؾ��� [ �״�� �ϱ�� �� ]
		for (int i = 0; temp_AD[sel].explanation[i] != '\0'; i++) {
			printf("%c", temp_AD[sel].explanation[i]);
			if ((i + 1) % 20 == 0) gotoxy(p.x, ++p.y);
		}
		p.x = X_MAX / 1.7, p.y = Y_MAX / 1.5;
		gotoxy(p.x, p.y++); // �ٿ� ������ ī��Ʈ�� ������ ��
		printf("%s : %d", set_language ? "�ٿ� ���� Ƚ��" : "Download Limit", temp_AD[sel].price);

		// �Է� �κ�
		// Ű �Է� �̺�Ʈ ó��
		// <- -> �� ������ ó���� �˾Ƽ� �ϵ���
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
					library_page_setting();
				}
				break;
			case K_RIGHT:
				if (temp_num == 5) {
					page_num++;
					page_flag = true;
					system("cls");
					library_page_setting();
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
					library_page_setting();
				}
				break;
			case 'd':
			case 'D':
				if (temp_num == 5) {
					page_num++;
					page_flag = true;
					system("cls");
					library_page_setting();
				}
				break;
			case K_ENTER:
				if (is_hav_file(get_extension(temp_AD[sel].AID), temp_AD[sel].name))
					draw_message(set_language ? "�̹� ������ �����մϴ�!" : "The file already exists!");
				else {
					update_AID_D_count(UID, temp_AD[sel].AID, false);
					if (temp_AD[temp_num].price - 1 == 0) delete_AID_D(UID, temp_AD[sel].AID);
					chk_url = check_url(
						get_URL(temp_AD[sel].AID), get_extension(temp_AD[sel].AID), temp_AD[sel].name);
					if (chk_url == 1) // ����
						draw_message(set_language ? "�ٿ�ε� �Ϸ�." : "Download Complete");
					else // ������ ����
						draw_message(set_language ? "�ٿ�ε� ����." : "Download Fail");
					page_flag = true;
				}
				break;
			}
		}
	}
	return page;
}
// �⺻ UI ���
void library_page_setting() {
	Point p;
	draw_page();
	draw_box();
	if (set_language) draw_title("���̺귯�� ������");
	else draw_title("LIBRARY PAGE");
	p.x = X_MAX / 1.7, p.y = Y_MAX / 2.3;
	Point p2 = { p.x + 19, p.y + 4 };
	draw_lil_box(p, p2);
}

int compare(const void* a, const void* b) {
	int num1 = *(int*)a;
	int num2 = *(int*)b;
	if (num1 > num2)       // a�� b���� Ŭ ���
		return -1;
	if (num1 < num2)       // a�� b���� ���� ���
		return 1;
	return 0;              // a�� b�� ���� ���
}