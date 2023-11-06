#include <stdio.h>
#include <Windows.h>

#include "source.h"
#include "word_define.h"

int seller_page(short SID);
void upload_app(short SID);

int seller_page(short SID) {
	char* eng_my[3] = { "UPLOAD APPLICATION", "LOGOUT","QUIT" };
	char* kor_my[3] = { "���α׷� ���", "�α׾ƿ�", "����" };
	unsigned char key[2] = { 0,0 };
	int select = 0;
	int page = 0;
	Seller* temp = get_data_seller(SID);

	Point p = { 0,0 };

	draw_seller_page();
	draw_box();
	if (set_language) draw_title("���� ������");
	else draw_title("MY PAGE");

	while (page == 0) {
		p.x = X_MAX / 8, p.y = Y_MAX / 4;
		// �г��� ī��Ʈ ��� ��
		gotoxy(p.x, p.y++);
		printf("%s : %s",set_language ? "�г���" : "NickName", temp->nickname);
		gotoxy(p.x, p.y++);
		printf("SID : %d", SID);
		gotoxy(p.x, p.y++);
		if (set_language) printf("����� ���α׷� ���� : %d", temp->prog_count);
		else printf("Number of Application Uploaded : %d", temp->prog_count);
		gotoxy(p.x, p.y++);
		if (set_language) printf("��� Ƚ�� : %d", temp->report_count);
		else printf("Number of Reports : %d", temp->report_count);
		gotoxy(p.x, p.y++);
		if (set_language) printf("���� ���� : %d", temp->money);
		else printf("Money : %d", temp->money);

		p.y++;
		for (int i = 0; i < 3; i++, p.y += 2) {
			gotoxy(p.x, p.y);
			print_choice_lang(kor_my[i], eng_my[i], i == select);
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
				case 0: // ���α׷� ���
					upload_app(SID);
					draw_seller_page();
					draw_box();
					if (set_language) draw_title("���� ������");
					else draw_title("MY PAGE");
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

void upload_app(short SID) {
	char* kor_str[11] = {"���� ���", "����[Kor]", "����[Eng]", "�Ұ���[Kor]", "�Ұ���[ENG]",
						"URL", "�帣", "Ȯ����", "����", "���", "���"};
	char* eng_str[11] = {"Support Language", "Name[Kor]", "Name[Eng],", "Explantion[Kor]",
						"Explanation[Eng]", "URL", "Genre", "Extension", "Price", "Back", "Upload"};

	char str_len = 11;
	char* kor_sel_lang[3] = { "�� ��", "�ѱ��", "���" };
	char* eng_sel_lang[3] = { "Both", "Korean Only", "English Only" };

	bool flag_NK = false, flag_NE = false, flag_EK = false, flag_EE = false;
	short temp_NL = 0;
	unsigned char key[2] = { 0,0 };
	int select = 0;
	int sel_lang = 0;
	char temp_NK[20], temp_NE[20], temp_EK[101], temp_EE[101];
	wchar_t url[200];
	bool flag = true;
	int chk_explan_K = 1, chk_explan_E = 1;

	Point p = { 0,0 };
	
	system("cls");
	draw_box();

	if (set_language) draw_title("���α׷� ���");
	else draw_title("Application Upload");

	while (flag) {
		p.x = (int)X_MAX / 4, p.y = ((int)Y_MAX / 4);
		for (int i = 0; i < str_len; i++, p.y += 2) {
			if (i == 9) p.x += 10, p.y -= 2;
			gotoxy(p.x, p.y);
			print_choice_lang(kor_str[i], eng_str[i], i == select);
			switch (i) {
				case 0:
					for (int j = 0, px = p.x+11; j < 3; j++, px += 6) {
						gotoxy(j == 2 ? px + 8 : px, p.y);
						print_choice_lang(kor_sel_lang[j], eng_sel_lang[j], j == sel_lang);
					}
					break;
				case 1:
					if (flag_NK) printf(" : %s", temp_NK);
					break;
				case 2:
					if (flag_NE) printf(" : %s", temp_NE);
					break;
				case 5:
					break;
			}
		}
		// ����� �� ���ۿ�
		/*
		if (set_language)
				if (i == select) select_color(kor_my[i]);
				else printf("%s", kor_my[i]);
			else
				if (i == select) select_color(eng_my[i]);
				else printf("%s", eng_my[i]);
		*/
		// Ű �Է� �̺�Ʈ ó��
		key[0] = _getch();
		if (key[0] == K_ARROW || key[0] == 0) {
			key[1] = _getch();
			switch (key[1]) {
			case K_DOWN:
				select = select == str_len - 1 ? str_len - 1 : select + 1;
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
				select = select == str_len - 1 ? str_len - 1 : select + 1;
				break;
			case 'w':
			case 'W':
				select = select == 0 ? 0 : select - 1;
				break;
			case K_ENTER:
				switch (select) {
					case 0:
						if (sel_lang == 2) sel_lang = 0;
						else sel_lang++;
						break;
					case 1: // �ѱ��� ����
						input_some(set_language ? kor_str[select] : eng_str[select], temp_NK);
						flag_NK = true;
						draw_box();
						if (set_language) draw_title("���α׷� ���");
						else draw_title("Application Upload");
						break;
					case 2: // ���� ����
						input_some(set_language ? kor_str[select] : eng_str[select], temp_NE);
						flag_NE = true;
						draw_box();
						if (set_language) draw_title("���α׷� ���");
						else draw_title("Application Upload");
						break;
					case 3: // �ѱ��� �Ұ���
						if (flag_EK) chk_explan_K = popup_Explantion(temp_EK);
						if (chk_explan_K)input_blank_some(set_language ? kor_str[select] : eng_str[select], temp_EK, sizeof(temp_EK)/sizeof(char));
						flag_EK = true;
						draw_box();
						if (set_language) draw_title("���α׷� ���");
						else draw_title("Application Upload");
						break;
					case 4: // ���� �Ұ���
						if (flag_EE) chk_explan_E = popup_Explantion(temp_EE);
						if(chk_explan_E) input_blank_some(set_language ? kor_str[select] : eng_str[select], temp_EE, sizeof(temp_EE) / sizeof(char));
						flag_EE = true;
						draw_box();
						if (set_language) draw_title("���α׷� ���");
						else draw_title("Application Upload");
						break;
					case 5: // URL
						input_blank_some(set_language ? kor_str[select] : eng_str[select], url, sizeof(url) / sizeof(char));
						draw_box();
						if (set_language) draw_title("���α׷� ���");
						else draw_title("Application Upload");
						break;
					case 6: // �帣
						break;
					case 7: // Ȯ����
						break;
					case 8: // ����
						break;
					case 9:
						flag = false;
						break;
					case 10: 
						flag = false;
						break;
				}
			}
		}
	}
	system("cls");
}