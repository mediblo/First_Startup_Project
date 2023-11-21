#include <stdio.h>
#include <Windows.h>

#include "source.h"
#include "word_define.h"

int admin_page();
void report_page();

int admin_page() {
	char* kor_my[3] = { "프로그램 신고 관리", "로그아웃", "종료" };
	unsigned char key[2] = { 0,0 };
	int select = 0, page = 0;


	Point p = { 0,0 };

	draw_box();
	draw_title("관리 페이지");

	while (page == 0) {
		p.x = X_MAX / 8, p.y = Y_MAX / 4;
		gotoxy(p.x, p.y++);
		printf("유저 수 : %d", get_num_who(0));
		gotoxy(p.x, p.y++);
		printf("판매자 수 : %d", get_num_who(1));
		gotoxy(p.x, p.y++);
		printf("등록된 프로그램 갯수 : %d", get_num_who(2));

		p.y++;
		for (int i = 0; i < 3; i++, p.y += 2) {
			gotoxy(p.x, p.y);
			print_choice_lang(kor_my[i], NULL, i == select);
		}

		// 키 입력 이벤트 처리
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
				case 0: // 신고 관리
					system("cls");
					report_page();
					draw_box();
					draw_title("관리 페이지");
					break;
				case 1: // 로그아웃
					page = -1;

					break;
				case 2: // 종료
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
		draw_button(p, "신고먹은 프로그램이 없습니다.");
		Sleep(1000);
		system("cls");
		return 0; // 마이페이지로 돌아가거라
	}
	else {
		// 리스트 형식으로 처리
	}
}