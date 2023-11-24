#include <stdio.h>
#include <Windows.h>

#include "source.h"
#include "word_define.h"

int admin_page();
void report_page();
void disable_page();
void disable_app(short AID);
void able_app(short AID);

int admin_page() {
	char* kor_my[4] = { "�Ű� ���� ���α׷� ��Ȱ��ȭ", "���α׷� Ȱ��ȭ", "�α׾ƿ�", "����" };
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
		for (int i = 0; i < 4; i++, p.y += 2) {
			gotoxy(p.x, p.y);
			print_choice_lang(kor_my[i], NULL, i == select);
		}

		// Ű �Է� �̺�Ʈ ó��
		key[0] = _getch();
		if (key[0] == K_ARROW || key[0] == 0) {
			key[1] = _getch();
			switch (key[1]) {
			case K_DOWN:
				select = select == 3 ? 3 : select + 1;
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
				select = select == 3 ? 3 : select + 1;
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
				case 1:
					system("cls");
					disable_page();
					draw_box();
					draw_title("���� ������");
					break;
				case 2: // �α׾ƿ�
					page = -1;

					break;
				case 3: // ����
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
	if(!chk_report(true)){
		p.x = X_MAX / 2.8, p.y = Y_MAX / 2 - 1;
		draw_box();
		draw_button(p, "�Ű���� ���α׷��� �����ϴ�.");
		Sleep(1000);
		system("cls");
		return 0; // ������������ ���ư��Ŷ�
	}
	else {
		short AID_list[12]; // AID ��ϵ�
		char aNameList[12][20];
		get_AID_list(AID_list, true);
		get_aNameList(AID_list, aNameList);

		char* str[2] = { "�Ű� Ȯ��", "ó��" };
		int select = 0, i, choice = 0;
		bool flag = true, chk_flag= false;
		unsigned char key[2] = { 0,0 };
		Point p = { 0,0 };

		draw_box();
		draw_title("��� ���� ���α׷���");
		
		while(flag){
			p.x = X_MAX * 0.15, p.y = Y_MAX * 0.27;
			
			for (i = 0; i < 12 && AID_list[i] != -1; i++, p.x+=36) {
				if (i == 6) p.x += 22, p.y = Y_MAX * 0.27;
				gotoxy(p.x, p.y);
				print_choice_lang(aNameList[i], NULL, i == select);
				if (chk_flag && i == select) {
					printf(" [ ");
					for (int j = 0; j < 2; j++) {
						print_choice_lang(str[j], NULL, j == choice);
						printf(" ");
					}
					printf("]");
				}
				else printf("                    ");
			}
			i--;
			// Ű �Է� �̺�Ʈ ó��
			key[0] = _getch();
			if (key[0] == K_ARROW || key[0] == 0) {
				key[1] = _getch();
				switch (key[1]) {
				case K_DOWN:
					if (!chk_flag) select = select == i ? i : select + 1;
					break;
				case K_UP:
					if (!chk_flag) select = select == 0 ? 0 : select - 1;
					break;
				case K_LEFT:
					if (chk_flag) choice = 0;
					else select = select - 6 < 0 ? select : select - 6;
					break;
				case K_RIGHT:
					if (chk_flag) choice = 1;
					else select = i < select + 6 ? select : select + 6;
					break;
				}
			}
			else {
				switch (key[0]) {
				case 's':
				case 'S':
					if (!chk_flag) select = select == i ? i : select + 1;
					break;
				case 'w':
				case 'W':
					if (!chk_flag) select = select == 0 ? 0 : select - 1;
					break;
				case 'a':
				case 'A':
					if (chk_flag) choice = 0;
					else select = select - 6 < 0 ? select : select - 6;
					break;
				case 'd':
				case 'D':
					if (chk_flag) choice = 1;
					else select = i < select + 6 ? select : select + 6;
					break;
				case K_ESC:
					if (chk_flag) chk_flag = false, choice = 0;
					else flag = false;
					break;
				case K_ENTER:
					if (!chk_flag) chk_flag = true;
					else{
						if (choice == 0) report_view_page(AID_list[select], aNameList[select]);
						else disable_app(AID_list[select]); // ó��
						flag = false;
					}
					break;
				}
			}
		}
	}
	system("cls");
}

// ���� ���� �Ű� ��� �� ��Ȱ��ȭ �Ұ��� �����
void disable_app(short AID) {
	system("cls");
	draw_box();
	draw_title("¡��");
	draw_ESC();

	short rep_count[8];
	Point p = { 0,0 };
	unsigned char key = 0;
	bool flag = true;
	char* msg = { "���� �� �ش� ���α׷��� ��Ȱ��ȭ �˴ϴ�." };
	char* str[8] = { "���", "������", "�Ƶ� �д�", "���� ����",
					"�� �Ѽ�", "���ι�", "�طο�", "��Ÿ" };
	for (int i = 0; i < 8; i++) rep_count[i] = 0;
	get_rep_count(rep_count, AID);


	p.x = X_MAX * 0.5 - strlen(msg)/2, p.y = 7;

	textcolor(red, black);
	draw_button(p, msg);
	textcolor(white, black);

	p.x = X_MAX * 0.30, p.y = Y_MAX * 0.40;
	for (int i = 0; i < 8; i++, p.y +=2) {
		if (i == 4) p.x += 22, p.y = Y_MAX * 0.40;
		gotoxy(p.x, p.y);
		printf("%s : %d", str[i], rep_count[i]);
	}

	p.x = X_MAX * 0.47, p.y = Y_MAX - 7;
	textcolor(red, black);
	draw_button(p, ">����<");
	textcolor(white, black);

	while(flag){
		key = _getch();
		switch (key) {
			case K_ESC:
				flag = false;
				break;
			case K_ENTER:
				update_app_disable(AID, true);
				flag =false;
				break;
		}
	}
}

void disable_page() {
	Point p = { 0, 0 };
	draw_box();
	if (!chk_report(false)) {
		p.x = X_MAX / 2.8, p.y = Y_MAX / 2 - 1;
		draw_box();
		draw_button(p, "��Ȱ��ȭ ���α׷��� �����ϴ�.");
		Sleep(1000);
		system("cls");
		return 0; // ������������ ���ư��Ŷ�
	}
	else {
		short AID_list[12]; // AID ��ϵ�
		char aNameList[12][20];
		get_AID_list(AID_list, false);
		get_aNameList(AID_list, aNameList);

		int select = 0, i;
		bool flag = true;
		unsigned char key[2] = { 0,0 };
		Point p = { 0,0 };

		draw_box();
		draw_title("��Ȱ��ȭ ���α׷���");

		while (flag) {
			p.x = X_MAX * 0.15, p.y = Y_MAX * 0.27;

			for (i = 0; i < 12 && AID_list[i] != -1; i++, p.x += 36) {
				if (i == 6) p.x += 22, p.y = Y_MAX * 0.27;
				gotoxy(p.x, p.y);
				print_choice_lang(aNameList[i], NULL, i == select);
			}
			i--;
			// Ű �Է� �̺�Ʈ ó��
			key[0] = _getch();
			if (key[0] == K_ARROW || key[0] == 0) {
				key[1] = _getch();
				switch (key[1]) {
				case K_DOWN:
					select = select == i ? i : select + 1;
					break;
				case K_UP:
					select = select == 0 ? 0 : select - 1;
					break;
				case K_LEFT:
					select = select - 6 < 0 ? select : select - 6;
					break;
				case K_RIGHT:
					select = i < select + 6 ? select : select + 6;
					break;
				}
			}
			else {
				switch (key[0]) {
				case 's':
				case 'S':
					select = select == i ? i : select + 1;
					break;
				case 'w':
				case 'W':
					select = select == 0 ? 0 : select - 1;
					break;
				case 'a':
				case 'A':
					select = select - 6 < 0 ? select : select - 6;
					break;
				case 'd':
				case 'D':
					select = i < select + 6 ? select : select + 6;
					break;
				case K_ESC:
					flag = false;
					break;
				case K_ENTER:
					able_app(AID_list[select]); // ó��
					flag = false;
					break;
				}
			}
		}
	}
	system("cls");
}

void able_app(short AID) {
	system("cls");
	draw_box();
	draw_title("¡��");
	draw_ESC();

	short rep_count[8];
	Point p = { 0,0 };
	unsigned char key = 0;
	bool flag = true;
	char* msg = { "���� �� �ش� ���α׷��� Ȱ��ȭ �˴ϴ�." };
	for (int i = 0; i < 8; i++) rep_count[i] = 0;
	get_rep_count(rep_count, AID);


	p.x = X_MAX * 0.5 - strlen(msg) / 2, p.y = 7;

	textcolor(red, black);
	draw_button(p, msg);
	textcolor(white, black);

	p.x = X_MAX * 0.47, p.y = Y_MAX - 7;
	textcolor(red, black);
	draw_button(p, ">����<");
	textcolor(white, black);

	while (flag) {
		key = _getch();
		switch (key) {
		case K_ESC:
			flag = false;
			break;
		case K_ENTER:
			update_app_disable(AID, false);
			flag = false;
			break;
		}
	}
}
