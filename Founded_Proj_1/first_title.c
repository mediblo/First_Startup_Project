// 회원가입, 로그인, 비밀번호 찾기에 사용되는 키보드 처리 및 문자열 출력 함수들

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

#include "source.h"
#include "word_define.h"

#pragma warning(disable:4244) // double -> int 변환 손실 에러 처리
#pragma warning(disable:4267) // size_t -> int 변환 손실 에러 처리
#pragma warning(disable:6001) // 초기화 안한 메모리 사용 에러 처리

PNS select_title();
void select_register();
void select_find_pw();

PNS select_title() {
	int result = 0, select = 0, set_type = 0, old_select = 0, i = 0;
	unsigned char key[2] = { 0, 0 };
	Point p = { 0,0 };
	PNS set_proj;
	char temp_id[20] = "";
	char temp_pw[20] = "";
	char* eng_title_login[2] = { "ID","PASSWORD"};
	char* eng_title_type[3] = { "USER","SELLER","ADMIN" };
	char* eng_title_lang = "LANGUAGE SETTING";
	char* eng_title_setting[3] = { "REGISTER", "FIND PW", "QUIT" };
	
	char* kor_title_login[2] = {"아이디", "비밀번호"};
	char* kor_title_type[3] = { "유저", "판매자", "관리자" };
	char* kor_title_lang = "언어설정";
	char* kor_title_setting[3] = { "회원가입", "비밀번호 찾기", "종료"};

	draw_box();
	draw_title(set_language ? "스트림" : "STREAM");

	while(result !=1) {
		p.x = (int)X_MAX / 4, p.y = ((int)Y_MAX / 3);
		for (i = 0; i < 2; i++, p.y += 2) { // 아디 비번
			gotoxy(p.x, p.y);
			print_choice_lang(kor_title_login[i], eng_title_login[i], select == i);

			if (i == 0 && strlen(temp_id) != 0) printf(" : %s", temp_id);
			if (i == 1 && strlen(temp_pw) != 0) {
				printf(" : ");
				for (int j = 0; j < strlen(temp_pw); j++) printf("*");
			}
		}
		for (int px=p.x; i < 5; i++, px+=10) { // 유저 타입
			gotoxy(px, p.y);

			print_choice_lang(kor_title_type[i - 2], eng_title_type[i - 2], select == i);
			if (set_type + 2 == i ) printf(" ■");
			else printf(" □");
		}
		p.y += 2;

		if (i == 5) {
			gotoxy(p.x, p.y);
			print_choice_lang(kor_title_lang, eng_title_lang, select == i);
			printf(" : [");
			if (set_language) {
				select_color("KOR");
				printf(" %s", "ENG");
			}
			else {
				printf("%s ", "KOR");
				select_color("ENG");
			}
			printf("]");
		}
		p.y += 2, i++;

		for (; i < 9; i++, p.x += set_language ? 16 : 10) { // 세팅
			if (i == 7 && set_language) p.x -= 6;
			gotoxy(p.x, p.y);

			print_choice_lang(kor_title_setting[i - 6], eng_title_setting[i - 6], select == i);
		}

		gotoxy((int)X_MAX / 1.5, (int)Y_MAX / 2.3);
		if (select == 10) select_color(set_language ? "로그인" : "LOGIN");
		else printf(set_language ? "로그인" : "LOGIN");

		// 키 입력 이벤트 처리
		key[0] = _getch();
		if (key[0] == 224) {
			key[1] = _getch();
			switch (key[1]) { // 키보드 화살표 Ver
			case K_DOWN:
				if (2 <= select && select <= 4) select = 5;
				else select = select >= 8 ? 8 : select + 1;
				break;
			case K_UP:
				if (select != 5 && 2 <= select && select <= 8) select = 2 <= select && select <= 4 ? 1 : 5;
				else if (select == 5) select = 2;
				else select = select == 0 || select == 10 ? 0 : select - 1;
				break;
			case K_LEFT:
				if (2 <= select && select <= 8) select -= 1;
				else select = select == 10 ? old_select : select == 0 ? 0 : select - 1;
				break;
			case K_RIGHT:
				if (2 <= select && select <= 8) {
					if (select != 5 && select == 4 || select == 8) {
						old_select = select;
						select = 10;
					}
					else select += 1;
				}
				else if (select != 10) old_select = select, select = 10;
				break;
			}
		}
		else {
			switch (key[0]) { // 키보드 WASD Ver
				case 's':
				case 'S':
					if (2 <= select && select <= 4) select = 5;
					else select = select >= 8 ? 8 : select + 1;
					break;
				case 'w':
				case 'W':
					if (select != 5 && 2 <= select && select <= 8) select = 2 <= select && select <= 4 ? 1 : 5;
					else if (select == 5) select = 2;
					else select = select == 0 || select == 10 ? 0 : select - 1;
					break;
				case 'a':
				case 'A':
					if (2 <= select && select <= 8) select -= 1;
					else select = select == 10 ? old_select : select == 0 ? 0 : select - 1;
					break;
				case 'd':
				case 'D':
					if (select != 5 && 2 <= select && select <= 8) {
						if (select == 4 || select == 8) {
							old_select = select;
							select = 10;
						}
						else if( select != 10) select += 1;
					}
					else if (select != 10) old_select = select, select = 10;
					break;
			}
		}
		if (key[0] == K_ENTER) {
			switch (select) {
				case 0: // 아이디 입력
					input_some(set_language ? kor_title_login[select] : eng_title_login[select], temp_id);
					draw_box();
					draw_title(set_language ? "스트림" : "STREAM");
					break;
				case 1: // 비밀번호 입력
					input_some(set_language ? kor_title_login[select] : eng_title_login[select], temp_pw);
					draw_box();
					draw_title(set_language ? "스트림" : "STREAM");
					break;
				case 2:
				case 3:
				case 4: // 타입 변경
					set_type = select - 2;
					break;
				case 5: // 언어선택
					set_language = !set_language;
					system("cls");
					draw_box();
					draw_title(set_language ? "스트림" : "STREAM");
					break;
				case 6: // 회원가입
					select_register();
					draw_box();
					draw_title(set_language ? "스트림" : "STREAM");
					break;
				case 7: // 비밀번호 찾기
					select_find_pw();
					draw_box();
					draw_title(set_language ? "스트림" : "STREAM");
					break;
				case 8: // 종료
					set_proj.type = -1;
					set_proj.id = -10;
					return set_proj;
					break;
				case 10: {// 로그인
					Account ac = { temp_id, temp_pw };
					result=is_who(ac, set_type, is_user);
					if ( result == -2) result = is_who(ac, set_type, is_seller);
					if (result == -2) result = is_admin(ac);
					switch (result) {
						case 1: // 성공
							draw_message(set_language ? "성공!!" : "SUCCUSS!!");
							set_proj.type = set_type;
							set_proj.id = set_type == 2 ? 0 : who_ID(ac, set_type ? get_SID : get_UID);
							return set_proj;
						case 0: // 비밀번호 다름
							draw_title(set_language ? "비밀번호가 다릅니다!" : "not equal pw!!");
							break;
						case -1: // 아이디 없음
						case -2:
							draw_title(set_language ? "아이디가 존재하지 않습니다!" : "ID doesn't exits!!");
							break;
					}
					break;
				}
			}
		}
	}
	error(3);
}

void select_register() {
	char* eng_str_register[9] = { "ID", "PASSWORD", "NICKNAME", "USER", "SELLER", "QUESTION", "ANSWER", "BACK", "REGISTER"};
	char* kor_str_register[9] = { "아이디", "비밀번호", "닉네임", "유저", "판매자", "질문", "답변", "뒤로가기", "회원가입" };
	char temp_id[20] = "";
	char temp_pw[20] = "";
	char temp_n_name[20] = "";
	int temp_type = 0;
	int temp_quest = 0;
	char temp_answer[20] = "";
	int len_id = 0, len_pw = 0, len_n_name = 0, len_answer = 0;

	int select = 0, key[2] = { 0,0 };
	Point p = { 0,0 };
	bool flag = TRUE;

	system("cls");
	draw_box();
	draw_title(set_language ? "회원가입" : "Register");
	while(flag){
		p.x = (int)X_MAX / 4, p.y = ((int)Y_MAX / 4);
		for (int i = 0; i < 9; i++, p.y += 2) {
			if (i == 4 || i == 8) p.y -= 2;
			else if (i == 7) p.y += 1;
			gotoxy(i == 4 || i == 8 ? p.x+10 : p.x, p.y);

			print_choice_lang(kor_str_register[i], eng_str_register[i], select == i);
			switch (i) {
				case 0:
					if (strlen(temp_id) != 0) printf(" : %s", temp_id);
					break;
				case 1:
					if (strlen(temp_pw) != 0) {
						printf(" : ");
						for (int j = 0; j < strlen(temp_pw); j++) printf("*");
					}
					break;
				case 2:
					if (strlen(temp_n_name) != 0) printf(" : %s", temp_n_name);
					break;
				case 3:
				case 4:
					if (temp_type + 3 == i) printf(" ■");
					else printf(" □");
					break;
				case 5:
					printf(" : No.%d", temp_quest + 1);
					break;
				case 6:
					if (strlen(temp_answer) != 0) printf(" : %s", temp_answer);
					break;
			}
		}
		key[0] = _getch();
		if (key[0] == K_ARROW) {
			key[1] = _getch();
			switch (key[1]) { // 키보드 화살표 Ver
				case K_DOWN:
					if (select == 3) select = 5;
					else select = select >= 8 ? 8 : select + 1;
					break;
				case K_UP:
					if (select == 4 || select == 5 || select == 8) select = select == 4 ? 2 : select == 5 ? 3 : 6;
					else select = select == 0 || select == 10 ? 0 : select - 1;
					break;
				case K_LEFT:
					select = select == 0 || select == 10 ? 0 : select - 1;
					break;
				case K_RIGHT:
					select = select >= 8 ? 8 : select + 1;
					break;
			}
		}
		else {
			switch (key[0]) { // 키보드 WASD Ver
				case 'w':
				case 'W':
					if (select == 4 || select == 5 || select == 8) select = select == 4 ? 2 : select == 5 ? 3 : 6;
					else select = select == 0 || select == 10 ? 0 : select - 1;
					break;
				case 'a':
				case 'A':
					select = select == 0 || select == 10 ? 0 : select - 1;
					break;
				case 's':
				case 'S':
					if (select == 3) select = 5;
					else select = select >= 8 ? 8 : select + 1;
					break;
				case 'd':
				case 'D':
					select = select >= 8 ? 8 : select + 1;
					break;
			}
		}
		if (key[0] == K_ENTER) {
			switch (select) {
				case 0: // 아이디 입력
					input_some(set_language ? kor_str_register[select] : eng_str_register[select], temp_id);
					len_id = strlen(temp_id);
					draw_box();
					draw_title(set_language ? "회원가입" : "Register");
					break;
				case 1: // 비밀번호 입력
					input_some(set_language ? kor_str_register[select] : eng_str_register[select], temp_pw);
					len_pw = strlen(temp_pw);
					draw_box();
					draw_title(set_language ? "회원가입" : "Register");
					break;
				case 2: // 닉네임 입력
					input_some(set_language ? kor_str_register[select] : eng_str_register[select], temp_n_name);
					len_n_name = strlen(temp_n_name);
					draw_box();
					draw_title(set_language ? "회원가입" : "Register");
					break;
				case 3:
				case 4:
					temp_type = select - 3;
					break;
				case 5: // 질문 입력
					temp_quest = select_question(temp_quest);
					draw_box();
					draw_title(set_language ? "회원가입" : "Register");
					break;
				case 6: // 답변 입력
					input_some(set_language ? kor_str_register[select] : eng_str_register[select], temp_answer);
					len_answer = strlen(temp_answer);
					draw_box();
					draw_title(set_language ? "회원가입" : "Register");
					break;
				case 7:
					flag = FALSE;
					break;
				case 8:
					if (len_answer && len_id && len_n_name && len_pw) {
						if (is_new_who(temp_id, temp_type == 0 ? is_new_user : is_new_seller)) {
							insert_call(temp_id, temp_pw, temp_n_name, temp_quest, temp_answer,
								temp_type == 0 ? insert_user : insert_seller);
							flag = FALSE;
						}
						else draw_title(set_language ? "아이디가 이미 존재합니다!" : "ID already exits!!");
					}
					else draw_title(set_language ? "빈칸이 있습니다!" : "Input Empty place!!");
					break;
			}
		}
	}
	system("cls");
}

void select_find_pw() {
	char* eng_str_find_pw[7] = { "ID", "USER" ,"SELLER", "QUESTION", "ANSWER", "BACK", "FIND PW"};
	char* kor_str_find_pw[7] = { "아이디", "유저", "판매자", "질문", "답변", "뒤로가기", "비밀번호 찾기"};
	char temp_id[20] = "", temp_new_pw[20] = "", temp_answer[20] = "";
	short temp_ID = 0, temp_type = 0;
	int question = 0, select = 0;
	unsigned char key[2] = { 0,0 };
	Point p = { 0,0 };
	bool flag = TRUE;

	system("cls");
	draw_box();
	draw_title(set_language ? "비밀번호 찾기" : "FIND PASSWORD");

	while (flag) {
		p.x = X_MAX / 3, p.y = Y_MAX / 4;
		for (int i = 0; i < 7; i++, p.y += 2) {
			if (i == 2 || i == 6) { 
				p.y -= 2;
				gotoxy(p.x + 10, p.y);
			}
			else gotoxy(p.x, p.y);
			print_choice_lang(kor_str_find_pw[i], eng_str_find_pw[i], select == i);
			switch (i) {
			case 0:
				if (strlen(temp_id) != 0) printf(" : %s", temp_id);
				break;
			case 1:
			case 2:
				if (i - 1 == temp_type) printf(" ■");
				else printf(" □");
				break;
			case 3:
				printf(" : No.%d", question + 1);
				break;
			case 4:
				if (strlen(temp_answer) != 0) printf(" : %s", temp_answer);
				break;
			}
		}

		key[0] = _getch();
		if (key[0] == K_ARROW) {
			key[1] = _getch();
			switch (key[1]) {
			case K_DOWN:
				if (select == 1) select = 3;
				else select = select == 6 ? 6 : select + 1;
				break;
			case K_UP:
				if (select == 3) select = 1;
				else select = select == 0 ? 0 : select - 1;
				break;
			case K_RIGHT:
				if (select == 5 || select == 1) select++;
				break;
			case K_LEFT:
				if (select == 6 || select == 2) select--;
				break;
			}
		}
		else {
			switch (key[0]) {
			case 'w':
			case 'W':
				if (select == 3) select = 1;
				else select = select == 0 ? 0 : select - 1;
				break;
			case 's':
			case 'S':
				if (select == 1) select = 3;
				else select = select == 6 ? 6 : select + 1;
				break;
			case 'a':
			case 'A':
				if (select == 6 || select == 2) select--;
				break;
			case 'd':
			case 'D':
				if (select == 5 || select == 1) select++;
				break;
			case K_ENTER:
				switch (select) {
				case 0: // 아이디 입력
					input_some(set_language ? kor_str_find_pw[select] : eng_str_find_pw[select], temp_id);
					draw_box();
					draw_title(set_language ? "비밀번호 찾기" : "FIND PASSWORD");
					break;
				case 1:
				case 2:
					temp_type = select - 1;
					break;
				case 3: // 질문 입력
					question = select_question(question);
					draw_box();
					draw_title(set_language ? "비밀번호 찾기" : "FIND PASSWORD");
					break;
				case 4: // 답변 입력
					input_some(set_language ? kor_str_find_pw[select] : eng_str_find_pw[select], temp_answer);
					draw_box();
					draw_title("FIND PASSWORD");
					break;
				case 5: // 뒤로가기
					flag = FALSE;
					break;
				case 6: // 찾기
					temp_ID = is_exit_who(temp_id, question, temp_answer, temp_type ? is_exit_id_seller : is_exit_id);
					if (temp_ID != -1) {
						input_some(set_language ? "새로운 비밀번호" : "NEW PASSWORD", temp_new_pw);
						change_pw(temp_new_pw, temp_ID, temp_type ? change_pw_seller : change_pw_user);
					}
					else draw_message(set_language ? "아이디가 존재하지 않습니다!" : "ID doesn't exits!!");
					flag = FALSE;
					break;
				}
				break;
			}
		}
	}
	system("cls");
}