#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>

#include "source.h"
#include "word_define.h"

void shop_page_setting(bool app_flag);
int shop_search_page(short UID, int user_money);

int shop_page(short UID) {
	if (root_app == NULL) {
		Point p = { X_MAX / 2.8, p.y = Y_MAX / 2 - 1 };
		draw_box();
		draw_button(p, set_language ? "등록된 프로그램이 없습니다." : "No Uploaded programs");
		Sleep(1000);
		return 0; // 마이페이지로 돌아가거라
	}

	AData temp_AD[5];
	temp_AD[0].AID = -1;
	Point p = { 20, 10 };
	short page_num = 0, page = 2;
	unsigned char key[2] = { 0,0 };
	bool flag = false, page_flag = true, is_hav[5], app_flag = false;
	int i = 0, temp_num = 0;
	int sel = 0, chk_url = 0, cnt = 0, app_sel = 0;
	int user_money = get_money(UID);

	char* sel_arrow[2] = { "<--", "-->" };
	char* kor_app_sel[3] = { "리뷰", "다운", "추가" };
	char* eng_app_sel[3] = { "Review", "Download", "Increased" };

	
	
	while (page == 2) {
		if (page_flag) {
			temp_num = 0;
			i = 0;
			flag = false;
			for(int j=0; j<5; j++) is_hav[j] = false;
			// 5개 앱을 하나의 페이지에 있을 수 있도록 프로그램 아이디 및 AID 추출
			// 페이지 인식은 어떻게?
			for (App* temp = root_app; temp != NULL; temp = temp->next, i++) {
				if (page_num * 5 == i) flag = true;
				if (temp->is_disable) { i--; continue; }
				if (flag) {
					if (temp->lang_set == 0) {
						strcpy(temp_AD[temp_num].name, set_language ? temp->kor_name : temp->eng_name);
						strcpy(temp_AD[temp_num].explanation, set_language ? temp->kor_explanation : temp->eng_explanation);
					}
					else {
						strcpy(temp_AD[temp_num].name, temp->lang_set == 1 ? temp->kor_name : temp->eng_name);
						strcpy(temp_AD[temp_num].explanation, temp->lang_set == 1 ? temp->kor_explanation : temp->eng_explanation);
					}
					temp_AD[temp_num].AID = temp->AID;
					is_hav[temp_num] = is_hav_app(UID, temp->AID);
					temp_AD[temp_num++].price = temp->price;
				}
				if (temp_num == 5) break;
			}
			if (temp_num == 0) {
				p.x = X_MAX / 2.8, p.y = Y_MAX / 2 - 1;
				draw_box();
				draw_button(p, set_language ? "등록된 프로그램이 없습니다." : "No Uploaded programs");
				Sleep(1000);
				return 0; // 마이페이지로 돌아가거라
			}
			else if (temp_num != 5) for (int j = temp_num; j < 5; j++) temp_AD[j].AID = -1;
			page_flag = false;

			if (temp_num - 1 <= sel) sel = temp_num - 1;
			cnt = AID_count % 5 == 0 ? AID_count / 5 : AID_count / 5 + 1;
			shop_page_setting(false);	
		}

		// 출력 부분
		p.x = X_MAX - 1 - (strlen(set_language ? "F8 검색" : "F8 Search")), p.y = 1;
		gotoxy(p.x, p.y);
		choice_color(lightRed, lightGray, "F8 ");
		choice_color(black, lightGray, set_language ? "검색" : "Search");

		p.x = X_MAX / 7, p.y = Y_MAX / 4;
		for (int i = 0; i < 5; i++, p.y += 2) {
			gotoxy(p.x, p.y);
			if (temp_AD[i].AID == -1) continue;
			else {
				i == sel ? select_color(temp_AD[i].name) : printf("%s", temp_AD[i].name);
				
				if (app_flag && i == sel) {
					printf(" [ ");
					for (int j = 0; j < 2; j++) {
						if (is_hav[i] && j==1) j++;
						print_choice_lang(kor_app_sel[j], eng_app_sel[j], j == app_sel);
						printf(" ");
					}
					printf("]");
				}
				else if (is_hav[i]) printf(" [H]");
			}
		}

		p.y += 4;
		for (int j = 0; j < 2; j++, p.x += 4) {
			gotoxy(p.x, p.y);
			if((page_num != 0 && j == 0) || ( cnt != page_num + 1 && j == 1))
				printf("%s", sel_arrow[j]);
		}
		p.x = X_MAX / 8, p.y += 2;
		gotoxy(p.x, p.y);
		printf("[ %03d/%03d ]", page_num + 1, cnt);

		// 설명창 인식
		// 기존 설명창 제거
		p.x = X_MAX / 1.7, p.y = Y_MAX / 2.3;
		gotoxy(p.x, p.y);
		for (int i = 0; i < 100; i++) {
			printf(" ");
			if ((i + 1) % 20 == 0) gotoxy(p.x, ++p.y);
		}
		p.x = X_MAX / 1.7, p.y = Y_MAX / 2.3;
		gotoxy(p.x, p.y); // sel -> 무언가로 변경해야함 [ 그대로 하기로 함 ]
		for (int i = 0; temp_AD[sel].explanation[i] != '\0'; i++) {
			printf("%c", temp_AD[sel].explanation[i]);
			if ((i + 1) % 20 == 0) gotoxy(p.x, ++p.y);
		}
		p.x = X_MAX / 1.7, p.y = Y_MAX / 1.5;
		gotoxy(p.x, p.y++);
		printf("%s :%10d", set_language ? "가격" : "Price", is_hav[sel] ? (temp_AD[sel].price / 20) * 10 : temp_AD[sel].price);
		gotoxy(p.x, ++p.y);
		printf("%s :%10d", set_language ? "보유 자산" : "Money", user_money);

		// 입력 부분	
		// 키 입력 이벤트 처리
		// <- -> 는 페이지 처리로 알아서 하도록
		key[0] = _getch();
		if (key[0] == K_ARROW || key[0] == 0) {
			key[1] = _getch();
			switch (key[1]) {
			case K_F1:
			case K_F2:
			case K_F3:
				if(!app_flag) page = key[1] - K_F1;
				break;
			case K_F8:
				user_money = shop_search_page(UID, user_money);
				shop_page_setting(app_flag);
				break;
			case K_DOWN:
				if(!app_flag) sel = sel == temp_num - 1 ? temp_num - 1 : sel + 1;
				break;
			case K_UP:
				if (!app_flag)sel = sel == 0 ? 0 : sel - 1;
				break;
			case K_LEFT:
				if (page_num != 0 && !app_flag) {
					page_num--;
					page_flag = true;
					shop_page_setting(app_flag);
				}
				else if (app_flag) app_sel = 0;
				break;
			case K_RIGHT:
				if (cnt != page_num + 1 && !app_flag) {
					page_num++;
					page_flag = true;
					shop_page_setting(app_flag);
				}
				else if (app_flag) app_sel = is_hav[sel] ? 2 : 1;
				break;
			}
		}
		else {
			switch (key[0]) {
			case 's':
			case 'S':
				if (!app_flag)sel = sel == temp_num - 1 ? temp_num - 1 : sel + 1;
				break;
			case 'w':
			case 'W':
				if (!app_flag)sel = sel == 0 ? 0 : sel - 1;
				break;
			case 'a':
			case 'A':
				if (page_num != 0 && !app_flag) {
					page_num--;
					page_flag = true;
					shop_page_setting(app_flag);
				}
				else if (app_flag) app_sel = 0;
				break;
			case 'd':
			case 'D':
				if (cnt != page_num + 1 && !app_flag) {
					page_num++;
					page_flag = true;
					shop_page_setting(app_flag);
				}
				else if (app_flag) app_sel = is_hav[sel] ? 2 : 1;
				break;
			case K_ESC:
				if (app_flag) {
					app_flag = false;
					app_sel = 0;
				}
				shop_page_setting(app_flag);
				break;
			case K_ENTER:
				if(app_flag) {
					if (app_sel == 0) review_view_page(temp_AD[sel]);
					else {
						if (user_money < temp_AD[sel].price)
							draw_message(set_language ? "돈이 부족합니다!" : "Not Enough Money!");
						else if (is_hav[sel]) {
							update_user_money(UID, (temp_AD[sel].price / 20) * 10, false);
							update_AID_D_count(UID, temp_AD[sel].AID, true);
							update_seller_revenue(get_SID_from_AID(temp_AD[sel].AID), (temp_AD[sel].price / 20) * 10);
							user_money = get_money(UID);
							draw_message(set_language ? "다운 가능 횟수 5회 추가!" : "Download limit increased by 5 times!");
						}
						else {
							p.x = X_MAX / 2 - 8, p.y = Y_MAX / 2 - 1;
							system("cls");
							draw_box();
							draw_button(p, set_language ? "다운로드중..." : "Downloading...");
							chk_url = check_url(
								get_URL(temp_AD[sel].AID), get_extension(temp_AD[sel].AID), temp_AD[sel].name);
							if (chk_url == 1) { // 성공
								update_user_money(UID, temp_AD[sel].price, false);
								update_user_aCount(UID);
								update_seller_revenue(get_SID_from_AID(temp_AD[sel].AID), temp_AD[sel].price);
								update_revenue(temp_AD[sel].AID, temp_AD[sel].price);
								insert_AID_D(UID, temp_AD[sel]);
								user_money = get_money(UID);
								page_flag = true;
								draw_message(set_language ? "다운로드 완료." : "Download Complete");
							}
							else {// 나머진 실패
								Rep_data temp_repData = {UID, "다운로드 실패", 7};
								update_repData(temp_repData, temp_AD[sel].AID);
								page_flag = true;
								draw_message(set_language ? "다운로드 실패." : "Download Fail");
							}
						}
					}
				}
				else app_flag = true;
				shop_page_setting(app_flag);
				break;
			}
		}
	}
	return page;
}

int shop_search_page(short UID, int user_money) {
	Point p;
	
	char msg[20];
	short AID, sel=0;
	AData temp_AD;
	bool is_hav = false, flag = true;
	unsigned char key[2] = { 0,0 };
	char* kor_app_sel[3] = { "리뷰", "다운", "추가" };
	char* eng_app_sel[3] = { "Review", "Download", "Increased" };
	int chk_url = 0;

	input_some("검색 문장", msg);

	AID = is_search(msg);
	if (AID == -1) {
		draw_message(set_language ? "검색 결과 : 없음" : "Search Results : NULL");
		return;
	}
	shop_page_setting(true);

	for (App* temp = root_app; temp != NULL; temp = temp->next) {
		if (temp->AID == AID) {
			if (temp->lang_set == 0) {
				strcpy(temp_AD.name, set_language ? temp->kor_name : temp->eng_name);
				strcpy(temp_AD.explanation, set_language ? temp->kor_explanation : temp->eng_explanation);
			}
			else {
				strcpy(temp_AD.name, temp->lang_set == 1 ? temp->kor_name : temp->eng_name);
				strcpy(temp_AD.explanation, temp->lang_set == 1 ? temp->kor_explanation : temp->eng_explanation);
			}
			temp_AD.AID = temp->AID;
			is_hav = is_hav_app(UID, temp->AID);
			temp_AD.price = temp->price;
			break;
		}
	}

	// 설명창 인식
	// 기존 설명창 제거
	p.x = X_MAX / 1.7, p.y = Y_MAX / 2.3;
	gotoxy(p.x, p.y);
	for (int i = 0; i < 100; i++) {
		printf(" ");
		if ((i + 1) % 20 == 0) gotoxy(p.x, ++p.y);
	}
	p.x = X_MAX / 1.7, p.y = Y_MAX / 2.3;
	gotoxy(p.x, p.y); // sel -> 무언가로 변경해야함 [ 그대로 하기로 함 ]
	for (int i = 0; temp_AD.explanation[i] != '\0'; i++) {
		printf("%c", temp_AD.explanation[i]);
		if ((i + 1) % 20 == 0) gotoxy(p.x, ++p.y);
	}
	p.x = X_MAX / 1.7, p.y = Y_MAX / 1.5;
	gotoxy(p.x, p.y++);
	printf("%s :%10d", set_language ? "가격" : "Price", is_hav ? (temp_AD.price / 20) * 10 : temp_AD.price);
	gotoxy(p.x, ++p.y);
	printf("%s :%10d", set_language ? "보유 자산" : "Money", user_money);

	while(flag){
		p.x = X_MAX / 7, p.y = Y_MAX / 4;
		gotoxy(p.x, p.y);
		printf("%s", temp_AD.name);
		printf(" [ ");
		for (int j = 0; j < 2; j++) {
			if (is_hav && j == 1) j++;
			print_choice_lang(kor_app_sel[j], eng_app_sel[j], j == sel);
			printf(" ");
		}
		printf("]");
		if (is_hav) printf(" [H]");

		key[0] = _getch();
		if (key[0] == K_ARROW || key[0] == 0) {
			key[1] = _getch();
			switch (key[1]) {
			case K_LEFT:
				sel = 0;
				break;
			case K_RIGHT:
				sel = is_hav ? 2 : 1;
				break;
			}
		}
		else {
			switch (key[0]) {
				case 'a':
				case 'A':
					sel = 0;
					break;
				case 'd':
				case 'D':
					sel = is_hav ? 2 : 1;
					break;
			case K_ESC:
				flag = false;
				break;
			case K_ENTER:
				if (sel == 0) review_view_page(temp_AD);
				else {
					if (user_money < temp_AD.price)
						draw_message(set_language ? "돈이 부족합니다!" : "Not Enough Money!");
					else if (is_hav) {
						update_user_money(UID, (temp_AD.price / 20) * 10, false);
						update_AID_D_count(UID, temp_AD.AID, true);
						update_seller_revenue(get_SID_from_AID(temp_AD.AID), (temp_AD.price / 20) * 10);
						user_money = get_money(UID);
						draw_message(set_language ? "다운 가능 횟수 5회 추가!" : "Download limit increased by 5 times!");
					}
					else {
						p.x = X_MAX / 2 - 8, p.y = Y_MAX / 2 - 1;
						system("cls");
						draw_box();
						draw_button(p, set_language ? "다운로드중..." : "Downloading...");
						chk_url = check_url(
							get_URL(temp_AD.AID), get_extension(temp_AD.AID), temp_AD.name);
						if (chk_url == 1) { // 성공
							update_user_money(UID, temp_AD.price, false);
							update_user_aCount(UID);
							update_seller_revenue(get_SID_from_AID(temp_AD.AID), temp_AD.price);
							update_revenue(temp_AD.AID, temp_AD.price);
							insert_AID_D(UID, temp_AD);
							user_money = get_money(UID);
							draw_message(set_language ? "다운로드 완료." : "Download Complete");
						}
						else {// 나머진 실패
							Rep_data temp_repData = { UID, "다운로드 실패", 7 };
							update_repData(temp_repData, temp_AD.AID);
							draw_message(set_language ? "다운로드 실패." : "Download Fail");
						}
					}
				}
				flag = false;
			}
		}
	}
	return user_money;
}

// 기본 UI 출력
void shop_page_setting(bool app_flag) {
	Point p;
	system("cls");
	if (app_flag) draw_ESC();
	else draw_page();
	draw_box();
	if (set_language) draw_title("상점 페이지");
	else draw_title("SHOP PAGE");
	p.x = X_MAX / 1.7, p.y = Y_MAX / 2.3;
	Point p2 = { p.x + 19, p.y + 4 };
	draw_lil_box(p, p2);
}