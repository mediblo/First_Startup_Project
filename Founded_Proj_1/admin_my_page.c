#include <stdio.h>
#include <Windows.h>

#include "source.h"
#include "word_define.h"

int admin_page();
void report_page();

int admin_page() {
	char* kor_my[3] = { "���α׷� �Ű� ����", "�α׾ƿ�", "����" };
	unsigned char key[2] = { 0,0 };
	int select = 0, page = 0;


	Point p = { 0,0 };

	draw_box();
	draw_title("���� ������");

	while (page == 0) {
		p.x = X_MAX / 8, p.y = Y_MAX / 4;
		gotoxy(p.x, p.y++);
		printf("���� �� : %d", get_num_who(0));
		gotoxy(p.x, p.y++);
		printf("�Ǹ��� �� : %d", get_num_who(1));
		gotoxy(p.x, p.y++);
		printf("��ϵ� ���α׷� ���� : %d", get_num_who(2));

		p.y++;
		for (int i = 0; i < 3; i++, p.y += 2) {
			gotoxy(p.x, p.y);
			print_choice_lang(kor_my[i], NULL, i == select);
		}

		// Ű �Է� �̺�Ʈ ó��
		key[0] = _getch();
		if (key[0] == K_ARROW || key[0] == 0) {
			key[1] = _getch();
			switch (key[1]) {
			case K_DOWN:
				select = select == 2 ? 2 : select + 1;
				break;
			case K_UP:
				select = select == 0 ? 0 : select - 1;
				break;
			}
		}
		else {
			switch (key[0]) {
			case 's':
			case 'S':
				select = select == 2 ? 2 : select + 1;
				break;
			case 'w':
			case 'W':
				select = select == 0 ? 0 : select - 1;
				break;
			case K_ENTER:
				switch (select) {
				case 0: // �Ű� ����
					system("cls");
					report_page();
					draw_box();
					draw_title("���� ������");
					break;
				case 1: // �α׾ƿ�
					page = -1;

					break;
				case 2: // ����
					page = -10;
					break;
				}
				break;
			}
		}
	}
	return page;
}

void report_page() {
	Point p = { 0, 0 };
	draw_box();
	if(!chk_report()){
		p.x = X_MAX / 2.8, p.y = Y_MAX / 2 - 1;
		draw_box();
		draw_button(p, "�Ű���� ���α׷��� �����ϴ�.");
		Sleep(1000);
		system("cls");
		return 0; // ������������ ���ư��Ŷ�
	}
	else {
		// ����Ʈ �������� ó��
	}
}