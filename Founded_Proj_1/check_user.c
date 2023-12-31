#define _CRT_SECURE_NO_WARNINGS
// 유저 확인 함수들
#include <stdio.h>
#include <Windows.h>
#include <string.h>

#include "source.h"
#include "word_define.h"

#pragma warning(disable:6011) // NULL 포인터 역참조 경고 무시

int is_user(Account ac, short type);
bool is_new_user(char* id);
int is_exit_id(char* id, short quest, char* answer);
int get_UID(Account ac);
int check_pw(short UID, char* pw);

int is_seller(Account ac, short type);
bool is_new_seller(char* id);
int is_exit_id_seller(char* id, int quest, char* answer);
int get_SID(Account ac);
int check_pw_seller(short UID, char* pw);

int is_who(Account ac, short type, int(*func)(Account ac, short type)) { return func(ac, type); }
bool is_new_who(char* id, int(*func)(char*)) { return func(id); }
int who_ID(Account ac, int(*func)(Account ac)) { return func(ac); }
int is_exit_who(char* id, short quest, char* answer, int(*func)(char* id, short quest, char* answer)) { return func(id, quest, answer); }

///////////////////////////유저 버전 함수들////////////
int is_user(Account ac, short type) {
	if (type != 0) return -2;
	for (User* temp = root_user; temp != NULL; temp = temp->next) {
		if (strcmp(temp->id, ac.id) == 0) {
			if (temp->password == make_pw_num(ac.password)) {
				set_language = temp->lang;
				return 1;
			}
			else return 0;
		}
	}
	return -1;
}
bool is_new_user(char* id) {
	if (root_user == NULL) return TRUE;
	for (User* temp = root_user; temp != NULL; temp = temp->next)
		if (strcmp(temp->id, id) == 0) return FALSE;
	return TRUE;
}
int is_exit_id(char* id, short quest, char* answer) {
	for (User* temp = root_user; temp != NULL; temp = temp->next) {
		if (strcmp(temp->id, id) == 0 && temp->question == quest && strcmp(temp->answer, answer) == 0)
			return temp->UID;
	}
	return -1;
}
int get_UID(Account ac) {
	for (User* temp = root_user; temp != NULL; temp = temp->next) {
		if (strcmp(temp->id, ac.id) == 0 && temp->password == make_pw_num(ac.password))
			return temp->UID;
	}
	// 에러 처리
}
int check_pw(short UID, char* pw) {
	for (User* temp = root_user; temp != NULL; temp = temp->next) {
		if (temp->UID == UID && temp->password == make_pw_num(pw))
			return 1;
	}
	return 0;
}
User* get_data(short UID) {
	for (User* temp = root_user; temp != NULL; temp = temp->next)
		if (temp->UID == UID) return temp;
	// 에러 처리
}
int get_money(short UID) {
	for (User* temp = root_user; temp != NULL; temp = temp->next)
		if (temp->UID == UID) return temp->money;
	// 에러 처리
}
char* get_name(short UID) {
	for (User* temp = root_user; temp != NULL; temp = temp->next)
		if (temp->UID == UID) return temp->nickname;
	return set_language ? "탈퇴한 사용자" : "Withdrawn user";
}
bool is_report_write(short AID, short UID) {
	for (App* temp = root_app; temp != NULL; temp = temp->next) {
		if (temp->AID == AID) {
			for (int i = 0; i < 10; i++) {
				if (temp->repData[i].UID == -1) return false;
				else if (temp->repData[i].UID == UID) return true;
			}
			break;
		}
	}
	return false;
}
short get_report_reason(short AID, short UID) {
	for (App* temp = root_app; temp != NULL; temp = temp->next) {
		if (temp->AID == AID) {
			for (int i = 0; i < 10; i++) {
				if (temp->repData[i].UID == -1) return 0;
				else if (temp->repData[i].UID == UID) return temp->repData[i].reason;
			}
			break;
		}
	}
	return 0;
}
///////////////////////////판매자 버전 함수들////////////
int is_seller(Account ac, short type) {
	if (type != 1) return -2;
	for (Seller* temp = root_seller; temp != NULL; temp = temp->next) {
		if (strcmp(temp->id, ac.id) == 0)
			if (temp->password == make_pw_num(ac.password)) {
				set_language = temp->lang;
				return 1;
			}
			else return 0;
	}
	return -1;
}
bool is_new_seller(char* id) {
	if (root_seller == NULL) return TRUE;
	for (Seller* temp = root_seller; temp != NULL; temp = temp->next) {
		if (strcmp(temp->id, id) == 0) return FALSE;
	}
	return TRUE;
}
int is_exit_id_seller(char* id, int quest, char* answer) {
	for (Seller* temp = root_seller; temp != NULL; temp = temp->next) {
		if (strcmp(temp->id, id) == 0 && temp->question == quest && strcmp(temp->answer, answer) == 0)
			return temp->SID;
	}
	return -1;
}
int get_SID(Account ac) {
	for (Seller* temp = root_seller; temp != NULL; temp = temp->next) {
		if (strcmp(temp->id, ac.id) == 0 && temp->password == make_pw_num(ac.password))
			return temp->SID;
	}
	// 에러 처리
}
int check_pw_seller(short SID, char* pw) {
	for (Seller* temp = root_seller; temp != NULL; temp = temp->next) {
		if (temp->SID == SID && temp->password == make_pw_num(pw)) return 1;
	}
	return 0;
}
Seller* get_data_seller(short SID) {
	for (Seller* temp = root_seller; temp != NULL; temp = temp->next)
		if (temp->SID == SID) return temp;
	// 에러 처리
}
int get_SID_from_AID(short AID) {
	for (App* temp = root_app; temp != NULL; temp = temp->next)
		if (temp->AID == AID)
			return temp->SID;
	// 에러 처리
}
///////////////////////////프로그램 버전 함수들////////////
wchar_t* get_URL(short AID) {
	for (App* temp = root_app; temp != NULL; temp = temp->next)
		if (temp->AID == AID) return temp->url;
	// 에러 처리
}
char get_extension(short AID) {
	for (App* temp = root_app; temp != NULL; temp = temp->next)
		if (temp->AID == AID) return temp->extension;
	// 에러 처리
}
char get_genre(short AID) {
	for (App* temp = root_app; temp != NULL; temp = temp->next)
		if (temp->AID == AID) return temp->genre;
	// 에러 처리
}
char get_rate(short UID, short AID) {
	for (Review* temp = root_review; temp != NULL; temp = temp->next)
		if (temp->UID == UID && temp->AID == AID)
			return temp->rate;
	// 에러 처리
}
char* get_comment(short UID, short AID) {
	for (Review* temp = root_review; temp != NULL; temp = temp->next)
		if (temp->UID == UID && temp->AID == AID)
			return temp->comment;
	// 에러 처리
}
int get_revenue(short AID) {
	for (App* temp = root_app; temp != NULL; temp = temp->next)
		if (temp->AID == AID)
			return temp->revenue;
	// 에러 처리
}
bool is_hav_app(short UID, short AID) {
	for (AID_D* temp = root_AID_D; temp != NULL; temp = temp->next)
		if (temp->UID == UID && temp->AD.AID == AID)
			return true;
	return false;
}
bool is_write_review(short UID, short AID) {
	for (Review* temp = root_review; temp != NULL; temp = temp->next)
		if (temp->UID == UID && temp->AID == AID)
			return true;
	return false;
}
short is_search(char* msg) {
	for (App* temp = root_app; temp != NULL; temp = temp->next) {
		char* temp_name = temp->lang_set == 0 ? (set_language ? temp->kor_name : temp->eng_name) : (temp->lang_set == 1 ? temp->kor_name : temp->eng_name);
		if ((strstr(temp_name, msg) != NULL ) && !temp->is_disable)
			return temp->AID;
	}
	return -1;
}
short is_user_search(char* msg) {
	for (AID_D* temp = root_AID_D; temp != NULL; temp = temp->next) {
		if ((strstr(temp->AD.name, msg) != NULL))
			return temp->AD.AID;
	}
	return -1;
}
///////////////////////////관리자 버전 함수들////////////
int is_admin(Account ac) {
	static char count = 0;
	Admin ADM = get_admin();
	if (strcmp(ADM.id, ac.id) == 0)
		if (ADM.password == make_pw_num(ac.password)) {
			set_language = true;
			count = 0;
			return 1;
		}
		else {
			if (++count == 5) error(999);
			return 0;
		}
	return -1;
}
int get_num_who(char type) { // 0 = 유저 / 1 = 판매자 / 2 = 프로그램
	int cnt = 0;
	switch(type){
		case 0:
			for (User* temp = root_user; temp != NULL; temp = temp->next, cnt++);
			break;
		case 1:
			for (Seller* temp = root_seller; temp != NULL; temp = temp->next, cnt++);
			break;
		case 2:
			for (App* temp = root_app; temp != NULL; temp = temp->next, cnt++);
			break;
	}
	return cnt;
}
bool chk_report(bool flag) {
	for (App* temp = root_app; temp != NULL; temp = temp->next)
		if (flag && temp->is_report) return true;
		else if (!flag && temp->is_disable) return true;
	return false;
}
void get_AID_list(short AID_list[], bool flag) {
	int num=0;
	for (int i = 0; i < 12; i++) AID_list[i] = -1; // 초기화

	for(App* temp = root_app; temp != NULL; temp= temp->next)
		if (flag && temp->is_report) AID_list[num++] = temp->AID;
		else if(!flag && temp->is_disable) AID_list[num++] = temp->AID;
}
char* get_aNameList(short AID_list[], char aNameList[][20]) {
	char i = 0;
	for (App* temp = root_app; temp != NULL && i < 12; temp = temp->next) {
		if (temp->AID == AID_list[i]) {
			strcpy(aNameList[i++], temp->lang_set == 2 ? temp->eng_name : temp->kor_name);
		}
	}
	for (; i < 12; i++) strcpy(aNameList[i], "-1");
}
short* get_rep_count(short rep_count[], short AID) {
	for (App* temp = root_app; temp != NULL; temp = temp->next) {
		if (temp->AID == AID) {
			for (int i = 0; i < 10; i++) {
				if (temp->repData[i].UID == -1) break;
				else rep_count[temp->repData[i].reason]++;
			}
			break;
		}
	}
}