#include <stdio.h>
#include <Windows.h>

#include "source.h"
#include "word_define.h"

int seller_page(short SID);
void upload_app(short SID);

int seller_page(short SID) {
	char* eng_my[3] = { "UPLOAD APPLICATION", "LOGOUT","QUIT" };
	char* kor_my[3] = { "프로그램 등록", "로그아웃", "종료" };
	unsigned char key[2] = { 0,0 };
	int select = 0;
	int page = 0;
	Seller* temp = get_data_seller(SID);

	Point p = { 0,0 };

	draw_seller_page();
	draw_box();
	if (set_language) draw_title("마이 페이지");
	else draw_title("MY PAGE");

	while (page == 0) {
		p.x = X_MAX / 8, p.y = Y_MAX / 4;
		// 닉네임 카운트 경고 돈
		gotoxy(p.x, p.y++);
		printf("%s : %s",set_language ? "닉네임" : "NickName", temp->nickname);
		gotoxy(p.x, p.y++);
		printf("SID : %d", SID);
		gotoxy(p.x, p.y++);
		if (set_language) printf("등록한 프로그램 갯수 : %d", temp->prog_count);
		else printf("Number of Application Uploaded : %d", temp->prog_count);
		gotoxy(p.x, p.y++);
		if (set_language) printf("현재 수입 : %d", temp->revenue);
		else printf("Revenue : %d", temp->revenue);

		p.y++;
		for (int i = 0; i < 3; i++, p.y += 2) {
			gotoxy(p.x, p.y);
			print_choice_lang(kor_my[i], eng_my[i], i == select);
		}

		// 키 입력 이벤트 처리
		key[0] = _getch();
		if (key[0] == K_ARROW || key[0] == 0) {
			key[1] = _getch();
			switch (key[1]) {
			case K_F1:
			case K_F2:
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
				case 0: // 프로그램 등록
					upload_app(SID);
					draw_seller_page();
					draw_box();
					if (set_language) draw_title("마이 페이지");
					else draw_title("MY PAGE");
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

void upload_app(short SID) {
	char* kor_str[11] = {"지원 언어", "제목[Kor]", "제목[Eng]", "소개말[Kor]", "소개말[ENG]",
						"URL", "장르", "확장자", "가격", "취소", "등록"};
	char* eng_str[11] = {"Support Language", "Name[Kor]", "Name[Eng],", "Explantion[Kor]",
						"Explanation[Eng]", "URL", "Genre", "Extension", "Price", "Back", "Upload"};

	char str_len = 11;
	char* kor_sel_lang[3] = { "둘 다", "한국어만", "영어만" };
	char* eng_sel_lang[3] = { "Both", "Korean Only", "English Only" };

	bool flag_NK = false, flag_NE = false, flag_EK = false, flag_EE = false, flag_URL = false;
	short temp_NL = 0;
	unsigned char key[2] = { 0,0 };
	int select = 0;
	int sel_lang = 0;
	char temp_NK[20], temp_NE[20], temp_EK[101], temp_EE[101];
	wchar_t url[200];
	bool flag = true;
	bool chk_explan_K = true, chk_explan_E = true, chk_URL = true;
	int temp_genre = 0, temp_extension = 0, temp_money = -1;


	Point p = { 0,0 };
	
	system("cls");
	draw_box();

	if (set_language) draw_title("프로그램 등록");
	else draw_title("Application Upload");

	while (flag) {
		p.x = (int)X_MAX / 4, p.y = ((int)Y_MAX / 4);
		for (int i = 0; i < str_len; i++, p.y += 2) {
			if (i == 10) p.x += 10, p.y -= 2;
			gotoxy(p.x, p.y);
			if ((sel_lang == 1 && (i == 2 || i == 4)) || (sel_lang == 2 && (i == 1 || i == 3)))
				choice_color(darkGray, black, set_language ? kor_str[i] : eng_str[i]);
			else print_choice_lang(kor_str[i], eng_str[i], i == select);
			switch (i) {
				case 0:
					for (int j = 0, px = p.x+11; j < 3; j++, px += 6) {
						gotoxy(j == 2 ? px + 8 : px, p.y);
						print_choice_lang(kor_sel_lang[j], eng_sel_lang[j], j == sel_lang);
					}
					break;
				case 1:
					if (flag_NK)
						if (sel_lang == 2) {
							textcolor(darkGray, black);
							printf(" : %s", temp_NK);
							textcolor(white, black);
						}
						else printf(" : %s", temp_NK);
					break;
				case 2:
					if (flag_NE)
						if (sel_lang == 1) {
							textcolor(darkGray, black);
							printf(" : %s", temp_NE);
							textcolor(white, black);
						}
						else printf(" : %s", temp_NE);
					break;
				case 6:
					printf(" : %s", output_genre(temp_genre));
					break;
				case 7:
					printf(" : %s", output_extension(temp_extension));
					break;
				case 8:
					if(temp_money != -1) printf(" : %d%s", temp_money, set_language ? "원" : "Won");
					break;
				case 5:
					break;
			}
		}

		// 키 입력 이벤트 처리
		key[0] = _getch();
		if (key[0] == K_ARROW || key[0] == 0) {
			key[1] = _getch();
			switch (key[1]) {
			case K_DOWN:
				select = select == str_len - 1 ? str_len - 1 : select + 1;
				if ((sel_lang == 1 && (select == 2 || select == 4)) || (sel_lang == 2 && (select == 1 || select == 3))) select++;
				break;
			case K_UP:
				select = select == 0 ? 0 : select - 1;
				if ((sel_lang == 1 && (select == 2 || select == 4)) || (sel_lang == 2 && (select == 1 || select == 3)) || select == 9) select--;
				break;
			case K_LEFT:
				if (select == 10) select = 9;
				break;
			case K_RIGHT:
				if (select == 9) select = 10;
				break;
			}
		}
		else {
			switch (key[0]) {
			case 's':
			case 'S':
				select = select == str_len - 1 ? str_len - 1 : select + 1;
				if ((sel_lang == 1 && (select == 2 || select == 4)) || (sel_lang == 2 && (select == 1 || select == 3))) select++;
				break;
			case 'w':
			case 'W':
				select = select == 0 ? 0 : select - 1;
				if ((sel_lang == 1 && (select == 2 || select == 4)) || (sel_lang == 2 && (select == 1 || select == 3)) || select == 9) select--;
				break;
			case 'a':
			case 'A':
				if (select == 10) select = 9;
				break;
			case 'd':
			case 'D':
				if (select == 9) select = 10;
				break;
			case K_ENTER:
				switch (select) {
					case 0:
						if (sel_lang == 2) sel_lang = 0;
						else sel_lang++;
						break;
					case 1: // 한국어 제목
						input_some(set_language ? kor_str[select] : eng_str[select], temp_NK);
						flag_NK = true;
						draw_box();
						if (set_language) draw_title("프로그램 등록");
						else draw_title("Application Upload");
						break;
					case 2: // 영어 제목
						input_some(set_language ? kor_str[select] : eng_str[select], temp_NE);
						flag_NE = true;
						draw_box();
						if (set_language) draw_title("프로그램 등록");
						else draw_title("Application Upload");
						break;
					case 3: // 한국어 소개말
						if (flag_EK) chk_explan_K = popup_Explantion(temp_EK);
						if (chk_explan_K)input_blank_some(set_language ? kor_str[select] : eng_str[select], temp_EK, sizeof(temp_EK));
						flag_EK = true;
						draw_box();
						if (set_language) draw_title("프로그램 등록");
						else draw_title("Application Upload");
						break;
					case 4: // 영어 소개말
						if (flag_EE) chk_explan_E = popup_Explantion(temp_EE);
						if(chk_explan_E) input_blank_some(set_language ? kor_str[select] : eng_str[select], temp_EE, sizeof(temp_EE));
						flag_EE = true;
						draw_box();
						if (set_language) draw_title("프로그램 등록");
						else draw_title("Application Upload");
						break;
					case 5: // URL
						if (flag_URL) chk_URL = URL_popup_Explantion(url);
						if (chk_URL) input_only_url(set_language ? kor_str[select] : eng_str[select], url, sizeof(url) / sizeof(char));
						flag_URL = true;
						draw_box();
						if (set_language) draw_title("프로그램 등록");
						else draw_title("Application Upload");
						break;
					case 6: // 장르
						temp_genre = input_genre(temp_genre);
						draw_box();
						if (set_language) draw_title("프로그램 등록");
						else draw_title("Application Upload");
						break;
					case 7: // 확장자
						temp_extension = input_extension(temp_extension);
						draw_box();
						if (set_language) draw_title("프로그램 등록");
						else draw_title("Application Upload");
						break;
					case 8: // 가격
						temp_money = set_money();
						draw_box();
						if (set_language) draw_title("프로그램 등록");
						else draw_title("Application Upload");
						break;
					case 9: // 취소
						flag = false;
						break;
					case 10: // 결정
						if(temp_EE && temp_EK && temp_NE && temp_NK && flag_URL && temp_money != -1){
							insert_application(temp_NK, temp_NE, temp_EK, temp_EE, url,
								temp_genre, temp_extension, SID, temp_money, sel_lang);
							flag = false;
						}
						else draw_title(set_language ? "빈칸이 있습니다!" : "Input Empty place!!");
						break;
				}
			}
		}
	}
	system("cls");
}