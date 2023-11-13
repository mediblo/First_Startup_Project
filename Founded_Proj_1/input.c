// 중요 입력 관련 함수들
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
		printf("영어 최대 19음절");
		gotoxy(p.x, ++p.y);
		printf("한국어 최대 9자");
	}
	else{
		printf("MAX Eng = 19word");
		gotoxy(p.x, ++p.y);
		printf("MAX Kor = 9word");
	}

	gotoxy(p.x, ++p.y);
	if (set_language) printf("%s 입력 : ", str);
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
	if (set_language) printf("최대 음절 : 한국어 %lld, 영어 %lld", len_str / 2, len_str - 1);
	else printf("MAX syllable = Kor %lld, Eng %lld", len_str / 2, len_str);
	textcolor(white, black);
	gotoxy(p.x, ++p.y);

	rewind(stdin); // 버퍼 제거 [ 편-안 ]

	gotoxy(p.x, ++p.y);
	if (set_language) printf("%s 입력 : ", str);
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
	if (set_language) printf("최대 음절 : 한국어 %lld, 영어 %lld", len_str / 2, len_str - 1);
	else printf("MAX syllable = Kor %lld, Eng %lld", len_str / 2, len_str);
	textcolor(white, black);
	gotoxy(p.x, ++p.y);

	rewind(stdin); // 버퍼 제거 [ 편-안 ]

	gotoxy(p.x, ++p.y);
	if (set_language) printf("%s 입력 : ", str);
	else printf("Input your %s : ", str);
	fgetws(some, len_str, stdin);
	system("cls");
}

int select_question(int old_select) {
	int select = old_select, key[2] = { 0.0 };
	char* kor_question[7] = {
		"당신이 나온 고등학교는 ?",
		"첫 번째로 키운 애완동물 이름은?",
		"어렸을 때 불렸던 별명은?",
		"가장 좋아하는 가수의 이름은?",
		"가장 좋아하는 게임의 이름은?",
		"당신의 부모님이 태어난 년도는?",
		"가장 좋아하는 책의 이름은?"
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
	draw_title(set_language ? "질문" : "QUESTION");

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

	char* kor_genre[13] = { "게임", "백신", "오피스", "메신저", "데이터베이스",
							"그래픽", "교육", "동영상", "사진", "음악", "텍스트",
							"기타", "취소" };
	char* eng_genre[13] = { "Game", "Vaccine", "Office", "Messenger", "DataBase",
							"Graphics", "education", "Video", "Picture", "Music", "Text",
							"etc.", "Back" };

	int gen_count = 13;
	unsigned key[2] = { 0,0 };

	Point p = { 0, 0 };
	
	system("cls");
	draw_box();
	draw_title(set_language ? "장르" : "GENRE");

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
	// 에러 처리
}
char* output_genre(char genre) {
	char* kor_genre[12] = { "게임", "백신", "오피스", "메신저", "데이터베이스",
							"그래픽", "교육", "동영상", "사진", "음악", "텍스트",
							"기타" };
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
	draw_title(set_language ? "확장자" : "EXTENSION");

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
	// 에러 처리
}
char* output_extension(char extension) {
	char* str_extension[16] = { "exe", "zip", "7z", "gif", "mp3",
								"wav", "mp4", "avi", "png", "jpg",
								"pptx","xlex", "txt", "hwp", "doc",
								"pdf" };
	return str_extension[extension];
}

int set_money() {
	char* str = set_language ? "가격" : "PRICE";
	system("cls");
	draw_box();
	draw_title(str);
	
	char money[10];
	bool flag = false;
	Point p = { (int)X_MAX / 3, (int)Y_MAX / 2 - 1 };

	gotoxy(p.x, p.y);
	
	printf("%s", set_language ? "숫자만 입력 가능" : "Only numbers can be entered");
	gotoxy(p.x, ++p.y);
	printf("%s", set_language ? "입력 최대는 999,999,999원" : "Max Price is 999,999,999\\");

	gotoxy(p.x, ++p.y);
	printf("%s : ", set_language ? "가격 입력" : "Input your price");
	scanf("%s", money);

	// 정수 확인
	for (int i = 0; money[i] != '\0'; i++) {
		if (isdigit(money[i]) == 0) {
			flag = true;
			break;
		}
	}

	system("cls");
	if (flag) {
		draw_message(set_language ? "입력하신 값은 숫자가 아닙니다!" : "The value you entered is not a number!");
		return set_money();
	}
	else atoi(money);
}