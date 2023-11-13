// �߿� �Է� ���� �Լ���
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#include "source.h"
#include "word_define.h"

void input_some(const char str[], char some[]);
void input_blank_some(const char str[], char some[], rsize_t len_str);
int select_question(int old_select);
int input_genre(int old_genre);
int input_extension(int old_extension);
int set_money();

void input_some(const char str[], char some[]) {
	system("cls");
	draw_box();
	draw_title(str);
	char temp;
	Point p = { (int)X_MAX / 3, (int)Y_MAX / 2 - 1 };

	gotoxy(p.x, p.y);
	if (set_language) {
		printf("���� �ִ� 19����");
		gotoxy(p.x, ++p.y);
		printf("�ѱ��� �ִ� 9��");
	}
	else{
		printf("MAX Eng = 19word");
		gotoxy(p.x, ++p.y);
		printf("MAX Kor = 9word");
	}

	gotoxy(p.x, ++p.y);
	if (set_language) printf("%s �Է� : ", str);
	else printf("Input your %s : ", str);
	temp = scanf("%[^\n]s", some);
	rewind(stdin);
	system("cls");
}

void input_blank_some(const char str[], char some[], rsize_t len_str) {
	system("cls");
	draw_box();
	draw_title(str);
	Point p = { (int)X_MAX / 3, (int)Y_MAX / 2 - 1 };

	gotoxy(p.x, p.y);
	textcolor(red, black);
	if (set_language) printf("�ִ� ���� : �ѱ��� %lld, ���� %lld", len_str / 2, len_str - 1);
	else printf("MAX syllable = Kor %lld, Eng %lld", len_str / 2, len_str);
	textcolor(white, black);
	gotoxy(p.x, ++p.y);

	rewind(stdin); // ���� ���� [ ��-�� ]

	gotoxy(p.x, ++p.y);
	if (set_language) printf("%s �Է� : ", str);
	else printf("Input your %s : ", str);
	fgets(some, len_str, stdin);
	system("cls");
}

void input_only_url(const char str[], wchar_t some[], rsize_t len_str) {
	system("cls");
	draw_box();
	draw_title(str);
	Point p = { (int)X_MAX / 3, (int)Y_MAX / 2 - 1 };

	gotoxy(p.x, p.y);
	textcolor(red, black);
	if (set_language) printf("�ִ� ���� : �ѱ��� %lld, ���� %lld", len_str / 2, len_str - 1);
	else printf("MAX syllable = Kor %lld, Eng %lld", len_str / 2, len_str);
	textcolor(white, black);
	gotoxy(p.x, ++p.y);

	rewind(stdin); // ���� ���� [ ��-�� ]

	gotoxy(p.x, ++p.y);
	if (set_language) printf("%s �Է� : ", str);
	else printf("Input your %s : ", str);
	fgetws(some, len_str, stdin);
	system("cls");
}

int select_question(int old_select) {
	int select = old_select, key[2] = { 0.0 };
	char* kor_question[7] = {
		"����� ���� ����б��� ?",
		"ù ��°�� Ű�� �ֿϵ��� �̸���?",
		"����� �� �ҷȴ� ������?",
		"���� �����ϴ� ������ �̸���?",
		"���� �����ϴ� ������ �̸���?",
		"����� �θ���� �¾ �⵵��?",
		"���� �����ϴ� å�� �̸���?"
	};
	char* eng_question[7] = {
		"What is the name of the high school you attended?",
		"What was the name of first pet you raised?",
		"What nickname were you called when you were young?",
		"What is the name of your favorite singer?",
		"What is the name of your favorite game?",
		"In which year were your parents born?",
		"What is the name of your favorite book?"
	};

	Point p = { 0, 0 };

	system("cls");
	draw_box();
	draw_title(set_language ? "����" : "QUESTION");

	while(TRUE){
		p.x = (int)X_MAX / 4, p.y = (int)Y_MAX / 3;
		for (int i = 0; i < 7; i++, p.y+= 2) {
			gotoxy(p.x, p.y);
			if (select == i) select_color(set_language ? kor_question[i] : eng_question[i]);
			else printf("%s", set_language ? kor_question[i] : eng_question[i]);
		}
		key[0] = _getch();
		if (key[0] == K_ARROW) {
			key[1] = _getch();
			switch (key[1]) {
				case K_DOWN:
					select = select == 6 ? 6 : select + 1;
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
				select = select == 6 ? 6 : select + 1;
				break;
			case 'w':
			case 'W':
				select = select == 0 ? 0 : select - 1;
				break;
			case K_ENTER:
				system("cls");
				return select;
			}
		}
	}
	error(2);
}

// game, vaccine, office, messenger
// DB, Graphics, education, Video
// Picture, Music, Text, etc
int input_genre(int old_genre) {
	int sel_genre = 0;

	char* kor_genre[13] = { "����", "���", "���ǽ�", "�޽���", "�����ͺ��̽�",
							"�׷���", "����", "������", "����", "����", "�ؽ�Ʈ",
							"��Ÿ", "���" };
	char* eng_genre[13] = { "Game", "Vaccine", "Office", "Messenger", "DataBase",
							"Graphics", "education", "Video", "Picture", "Music", "Text",
							"etc.", "Back" };

	int gen_count = 13;
	unsigned key[2] = { 0,0 };

	Point p = { 0, 0 };
	
	system("cls");
	draw_box();
	draw_title(set_language ? "�帣" : "GENRE");

	while (TRUE) {
		p.x = (int)X_MAX / 4, p.y = (int)Y_MAX / 3;
		gotoxy(p.x, p.y);
		for (int i = 0; i < gen_count; i++, p.x += 15) {
			if (i != 0 && i % 4 == 0) p.y += 2, p.x-=60;
			gotoxy(p.x, p.y);
			if (sel_genre == i) select_color(set_language ? kor_genre[i] : eng_genre[i]);
			else printf("%s", set_language ? kor_genre[i] : eng_genre[i]);
		}
		key[0] = _getch();
		if (key[0] == K_ARROW) {
			key[1] = _getch();
			switch (key[1]) {
			case K_RIGHT:
				sel_genre = sel_genre == gen_count-1 ? gen_count-1 : sel_genre + 1;
				break;
			case K_LEFT:
				sel_genre = sel_genre == 0 ? 0 : sel_genre - 1;
				break;
			case K_UP:
				sel_genre = sel_genre-4 < 0 ? sel_genre : sel_genre - 4;
				break;
			case K_DOWN:
				sel_genre = sel_genre + 4 > gen_count - 1 ? sel_genre : sel_genre + 4;
				break;
			}
		}
		else {
			switch (key[0]) {
			case 'd':
			case 'D':
				sel_genre = sel_genre == gen_count-1 ? gen_count-1 : sel_genre + 1;
				break;
			case 'a':
			case 'A':
				sel_genre = sel_genre == 0 ? 0 : sel_genre - 1;
				break;
			case 'w':
			case 'W':
				sel_genre = sel_genre - 4 < 0 ? sel_genre : sel_genre - 4;
				break;
			case 's':
			case 'S':
				sel_genre = sel_genre + 4 > gen_count - 1 ? sel_genre : sel_genre + 4;
				break;
			case K_ENTER:
				system("cls");
				return sel_genre;
			}
		}
	}
	// ���� ó��
}
char* output_genre(char genre) {
	char* kor_genre[12] = { "����", "���", "���ǽ�", "�޽���", "�����ͺ��̽�",
							"�׷���", "����", "������", "����", "����", "�ؽ�Ʈ",
							"��Ÿ" };
	char* eng_genre[12] = { "Game", "Vaccine", "Office", "Messenger", "DataBase",
							"Graphics", "education", "Video", "Picture", "Music", "Text",
							"etc." };
	return set_language ? kor_genre[genre] : eng_genre[genre];
}
// exe, zip, 7z, gif
// mp3, wav, mp4, avi
// png, jpg, pptx, xlex
// txt, hwp, doc, pdf
int input_extension(int old_extension) {
	int sel_extension = 0;
	char* str_extension[17] = { "exe", "zip", "7z", "gif", "mp3",
								"wav", "mp4", "avi", "png", "jpg",
								"pptx","xlex", "txt", "hwp", "doc",
								"pdf","Back" };

	int ext_count = 17;
	unsigned key[2] = { 0,0 };

	Point p = { 0, 0 };

	system("cls");
	draw_box();
	draw_title(set_language ? "Ȯ����" : "EXTENSION");

	while (TRUE) {
		p.x = (int)X_MAX / 2.5, p.y = (int)Y_MAX / 3;
		gotoxy(p.x, p.y);
		for (int i = 0; i < ext_count; i++, p.x += 6) {
			if (i != 0 && i % 4 == 0) p.y += 2, p.x -= 24;
			gotoxy(p.x, p.y);
			if (sel_extension == i) select_color(str_extension[i]);
			else printf("%s", str_extension[i]);
		}
		key[0] = _getch();
		if (key[0] == K_ARROW) {
			key[1] = _getch();
			switch (key[1]) {
			case K_RIGHT:
				sel_extension = sel_extension == ext_count - 1 ? ext_count - 1 : sel_extension + 1;
				break;
			case K_LEFT:
				sel_extension = sel_extension == 0 ? 0 : sel_extension - 1;
				break;
			case K_UP:
				sel_extension = sel_extension - 4 < 0 ? sel_extension : sel_extension - 4;
				break;
			case K_DOWN:
				sel_extension = sel_extension + 4 > ext_count - 1 ? sel_extension : sel_extension + 4;
				break;
			}
		}
		else {
			switch (key[0]) {
			case 'd':
			case 'D':
				sel_extension = sel_extension == ext_count - 1 ? ext_count - 1 : sel_extension + 1;
				break;
			case 'a':
			case 'A':
				sel_extension = sel_extension == 0 ? 0 : sel_extension - 1;
				break;
			case 'w':
			case 'W':
				sel_extension = sel_extension - 4 < 0 ? sel_extension : sel_extension - 4;
				break;
			case 's':
			case 'S':
				sel_extension = sel_extension + 4 > ext_count - 1 ? sel_extension : sel_extension + 4;
				break;
			case K_ENTER:
				system("cls");
				return sel_extension;
			}
		}
	}
	// ���� ó��
}
char* output_extension(char extension) {
	char* str_extension[16] = { "exe", "zip", "7z", "gif", "mp3",
								"wav", "mp4", "avi", "png", "jpg",
								"pptx","xlex", "txt", "hwp", "doc",
								"pdf" };
	return str_extension[extension];
}

int set_money() {
	char* str = set_language ? "����" : "PRICE";
	system("cls");
	draw_box();
	draw_title(str);
	
	char money[10];
	bool flag = false;
	Point p = { (int)X_MAX / 3, (int)Y_MAX / 2 - 1 };

	gotoxy(p.x, p.y);
	
	printf("%s", set_language ? "���ڸ� �Է� ����" : "Only numbers can be entered");
	gotoxy(p.x, ++p.y);
	printf("%s", set_language ? "�Է� �ִ�� 999,999,999��" : "Max Price is 999,999,999\\");

	gotoxy(p.x, ++p.y);
	printf("%s : ", set_language ? "���� �Է�" : "Input your price");
	scanf("%s", money);

	// ���� Ȯ��
	for (int i = 0; money[i] != '\0'; i++) {
		if (isdigit(money[i]) == 0) {
			flag = true;
			break;
		}
	}

	system("cls");
	if (flag) {
		draw_message(set_language ? "�Է��Ͻ� ���� ���ڰ� �ƴմϴ�!" : "The value you entered is not a number!");
		return set_money();
	}
	else atoi(money);
}