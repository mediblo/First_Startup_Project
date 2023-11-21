// ���������� �Լ�

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <string.h>

#include "source.h"
#include "word_define.h"

int my_page(short UID);
void change_prof(short UID);
void recharge_money(short UID);
bool ac_closing(short UID);

int my_page(short UID) {
	char* eng_my[5] = { "CHANGE PROFILE", "RECHARGE MONEY","ACCOUNT DELETE", "LOGOUT","QUIT" };
	char* kor_my[5] = { "ȸ����������","�ݾ�����","ȸ��Ż��", "�α׾ƿ�", "����" };
	unsigned char key[2] = { 0,0 };
	int select = 0;
	int page = 0;
	User* temp = get_data(UID);
	
	Point p = { 0,0 };
	
	draw_page();
	draw_box();
	if (set_language) draw_title("���� ������");
	else draw_title("MY PAGE");

	while(page == 0){
		p.x = X_MAX / 8, p.y = Y_MAX / 4;
		// �г��� ī��Ʈ ��� ��
		gotoxy(p.x, p.y++);
		if (set_language) printf("�г��� : %s", temp->nickname);
		else printf("Nickname : %s", temp->nickname);
		gotoxy(p.x, p.y++);
		printf("UID : %d", UID);
		gotoxy(p.x, p.y++);
		if (set_language) printf("�رݵ� ���α׷� ���� : %d", temp->prog_count);
		else printf("Number of Programs : %d", temp->prog_count);
		gotoxy(p.x, p.y++);
		if (set_language) printf("���� �ڻ� : %d", temp->money);
		else printf("Money : %d", temp->money);

		p.y++;
		for (int i = 0; i < 5; i++, p.y+=2) {
			gotoxy(p.x, p.y);
			if (set_language)
				if (i == select) select_color(kor_my[i]);
				else printf("%s", kor_my[i]);
			else
				if (i == select) select_color(eng_my[i]);
				else printf("%s", eng_my[i]);
		}

		// Ű �Է� �̺�Ʈ ó��
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
					select = select == 4 ? 4 : select + 1;
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
					select = select == 4 ? 4 : select + 1;
					break;
				case 'w':
				case 'W':
					select = select == 0 ? 0 : select - 1;
					break;
				case K_ENTER:
					switch (select) {
						case 0: // ȸ����������
							change_prof(UID);
							draw_page();
							draw_box();
							if (set_language) draw_title("���� ������");
							else draw_title("MY PAGE");
							break;
						case 1: // �ݾ� ����
							recharge_money(UID);
							draw_page();
							draw_box();
							if (set_language) draw_title("���� ������");
							else draw_title("MY PAGE");
							break;
						case 2: // ȸ�� Ż��
							if (ac_closing(UID)) {
								page = -1;
								break;
							}
							draw_page();
							draw_box();
							if (set_language) draw_title("���� ������");
							else draw_title("MY PAGE");
							break;
						case 3: // �α׾ƿ�
							page = -1;
							break;
						case 4: // ����
							page = -10;
							break;
					}
					break;
			}
		}
	}
	return page;
}

void change_prof(short UID) {
	char temp_pw[20] = "";
	User* temp = get_data(UID);
	input_some(set_language ? "��й�ȣ" : "PASSWORD", temp_pw);

	if (check_pw(UID, temp_pw) == 0)
		draw_message(set_language ? "����ġ!" : "NOT EQUAL!!");
	else {
		draw_message(set_language ? "��ġ!" : "Success");

		char* kor_prof[6] = { "�г���","����","�亯","��� ����", "�ڷΰ���", "����" };
		char* eng_prof[6] = { "NICKNAME","QUESTION","ANSWER","LANGUAGE SETTING", "BACK", "SAVE" };
		char* lang_str[2] = { "KOR", "ENG" };
		short lang_len = 6;
		char temp_n_name[20] = "";
		short temp_question = temp->question;
		char temp_answer[20] = "";
		bool temp_lang = temp->lang;
		unsigned char key[2] = { 0,0 };
		int select = 0, result = 0;
		Point p = { 0,0 };

		strcpy(temp_n_name, temp->nickname);
		strcpy(temp_answer, temp->answer);

		draw_box();
		draw_title(set_language ? "ȸ������ ����" : "CHANGE PROFILE");

		while (result == 0) {
			p.x= X_MAX / 8, p.y = Y_MAX / 3;

			for (int i = 0; i < lang_len; i++, p.y+=2) {
				if (i == 5) {
					p.x += 10;
					p.y -= 2;
				}
				gotoxy(p.x, p.y);
				if(set_language)
					if (select == i) select_color(kor_prof[i]);
					else printf("%s", kor_prof[i]);
				else 
					if (select == i) select_color(eng_prof[i]);
					else printf("%s", eng_prof[i]);
				switch (i) {
					case 0:
						printf(" : %s", temp_n_name);
						break;
					case 1:
						printf(" : No.%d", temp_question+1);
						break;
					case 2:
						printf(" : %s", temp_answer);
						break;
					case 3:
						printf(" : [");
						if (temp_lang) {
							select_color("KOR");
							printf(" %s", "ENG");
						}
						else {
							printf("%s ", "KOR");
							select_color("ENG");
						}
						printf("]");
						break;
				}
			}

			// Ű �Է� �̺�Ʈ ó��
			key[0] = _getch();
			if (key[0] == K_ARROW) {
				key[1] = _getch();
				switch (key[1]) {
					case K_DOWN:
						select = select == lang_len - 1 ? lang_len - 1 : select + 1;
						break;
					case K_UP:
						select = select == 0 ? 0 : select - 1;
						break;
					case K_LEFT:
						if (select == 5) select = 4;
						break;
					case K_RIGHT:
						if (select == 4) select = 5;
						break;
				}
			}
			else {
				switch (key[0]) {
				case 's':
				case 'S':
					select = select == lang_len - 1 ? lang_len - 1 : select + 1;
					break;
				case 'w':
				case 'W':
					select = select == 0 ? 0 : select - 1;
					break;
				case 'a':
				case 'A':
					if (select == 5) select = 4;
					break;
				case 'd':
				case 'D':
					if (select == 4) select = 5;
					break;
				case K_ENTER:
					switch (select) {
						case 0: // �г���
							input_some(set_language ? kor_prof[select] : eng_prof[select], temp_n_name);
							draw_box();
							draw_title(set_language ? "ȸ������ ����" : "CHANGE PROFILE");
							break;
						case 1: // ����
							temp_question = select_question(temp_question);
							draw_box();
							draw_title(set_language ? "ȸ������ ����" : "CHANGE PROFILE");
							break;
						case 2: // �亯
							input_some(set_language ? kor_prof[select] : eng_prof[select], temp_answer);
							draw_box();
							draw_title(set_language ? "ȸ������ ����" : "CHANGE PROFILE");
							break;
						case 3: // ��� ����
							temp_lang = !temp_lang;
							break;
						case 4:
							result = 1;
							break;
						case 5:
							result = 1;
							set_language = temp_lang;
							update_user(UID, temp_n_name, temp_question, temp_answer, temp_lang);
							break;
					}
						break;
				}
			}
		}
	}
	system("cls");
}

void recharge_money(short UID) {
	char* kor_money[5] = { "5,000��", "10,000��", "15,000��", "20,000��", "�ڷΰ���"};
	char* eng_money[5] = { "5,000Won", "10,000Won", "15,000Won", "20,000Won", "BACK"};
	unsigned short money[4] = { 5000,10000,15000,20000 };
	short len_str = 5;
	unsigned char key[2] = { 0, 0 };
	short select = 0;
	bool flag = true;
	Point p = { 0,0 };

	system("cls");
	draw_box();
	draw_title(set_language ? "�ݾ� ����" : "Recharge Money");

	while(flag){
		p.x = X_MAX / 2.2, p.y = Y_MAX / 4;
		for (int i = 0; i < len_str; i++,p.y+=4) {
			if (select == i){
				textcolor(black, white);
				if (set_language) draw_button(p, kor_money[i]);
				else draw_button(p, eng_money[i]);
				textcolor(white, black);
			}
			else
				if (set_language) draw_button(p, kor_money[i]);
				else draw_button(p, eng_money[i]);
		}
		key[0] = _getch();
		if (key[0] == K_ARROW) {
			key[1] = _getch();
			switch (key[1]) {
				case K_DOWN:
					select = select == 4 ? 4 : select + 1;
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
					select = select == 4 ? 4 : select + 1;
					break;
				case 'w':
				case 'W':
					select = select == 0 ? 0 : select - 1;
					break;
				case K_ENTER:
					if (select != 4) {
						update_user_money(UID, money[select], true);
					}
					flag = false;
					break;
			}
		}
	}
	system("cls");
}

bool ac_closing(short UID) {
	bool flag = true;
	int select = 0;
	unsigned char key[2] = { 0,0 };
	Point p = { 0,0 };
	char* kor_ac[2] = {"�ƴϿ�", "��"};
	char* eng_ac[2] = {"NO", "YES"};
	
	char* kor_str = "������ ������ ���ֽ� �̴ϱ�?";
	char* eng_str = "Are you sure to delete your account?";
	short len_str = 2;

	system("cls");
	draw_box();
	textcolor(red, black);
	draw_title(set_language ? "ȸ��Ż��" : "ACCOUNT DELETE");
	textcolor(white, black);

	p.x = X_MAX / 2 - strlen(set_language ? kor_str : eng_str) / 2;
	p.y = Y_MAX / 2;
	gotoxy(p.x, p.y);

	choice_color(red, black, set_language ? kor_str : eng_str);

	

	while (flag) {
		p.x = X_MAX / 2.2, p.y = Y_MAX / 1.5;

		for (int i = 0; i < len_str; i++, p.x += 8) {
			gotoxy(p.x, p.y);
			if (set_language)
				if (select == i) select_color(kor_ac[i]);
				else printf("%s", kor_ac[i]);
			else
				if (select == i) select_color(eng_ac[i]);
				else printf("%s", eng_ac[i]);

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
		else {
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
				if (select == 1) {
					delete_user(UID);
					system("cls");
					return true;
				}
				flag = false;
				break;
			}
		}
	}
	system("cls");
	return false;
}