// �߿� �Է� ���� �Լ���
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <windows.h>

#include "source.h"
#include "word_define.h"

void input_some(const char str[], char some[]);
void input_blank_some(const char str[], char some[], int len_str);
int select_question(int old_select);
int input_genre(int old_genre);

void input_some(const char str[], char some[]) {
	system("cls");
	draw_box();
	draw_title(str);
	char temp;
	Point p = { (int)X_MAX / 3, (int)Y_MAX / 2 - 1 };

	gotoxy(p.x, p.y);
	if (set_language) printf("�ִ� 19����");
	else printf("MAX Eng = 19word");
	gotoxy(p.x, ++p.y);


	if (set_language) choice_color(red, black, "�ѱ���� �Է����� ������!");
	else choice_color(red, black, "Do not Enter Korean");

	gotoxy(p.x, ++p.y);
	if (set_language) printf("%s �Է� : ", str);
	else printf("Input your %s : ", str);
	temp = scanf("%s", some);
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
	gets_s(some, len_str);
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
// Picture, Music, Text
int input_genre(int old_genre) {
	int sel_genre = 0;

	return sel_genre;
}

//