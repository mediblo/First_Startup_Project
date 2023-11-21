// ���� Ȯ�� �Լ���
#include <stdio.h>
#include <Windows.h>
#include <string.h>

#include "source.h"
#include "word_define.h"

#pragma warning(disable:6011) // NULL ������ ������ ��� ����

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

///////////////////////////���� ���� �Լ���////////////
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
	// ���� ó��
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
	// ���� ó��
}
int get_money(short UID) {
	for (User* temp = root_user; temp != NULL; temp = temp->next)
		if (temp->UID == UID) return temp->money;
	// ���� ó��
}
char* get_name(short UID) {
	for (User* temp = root_user; temp != NULL; temp = temp->next)
		if (temp->UID == UID) return temp->nickname;
	return set_language ? "Ż���� �����" : "Withdrawn user";
}
///////////////////////////�Ǹ��� ���� �Լ���////////////
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
	// ���� ó��
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
	// ���� ó��
}
int get_SID_from_AID(short AID) {
	for (App* temp = root_app; temp != NULL; temp = temp->next)
		if (temp->AID == AID)
			return temp->SID;
	// ���� ó��
}
///////////////////////////���α׷� ���� �Լ���////////////
wchar_t* get_URL(short AID) {
	for (App* temp = root_app; temp != NULL; temp = temp->next)
		if (temp->AID == AID) return temp->url;
	// ���� ó��
}
char get_extension(short AID) {
	for (App* temp = root_app; temp != NULL; temp = temp->next)
		if (temp->AID == AID) return temp->extension;
	// ���� ó��
}
char get_genre(short AID) {
	for (App* temp = root_app; temp != NULL; temp = temp->next)
		if (temp->AID == AID) return temp->genre;
	// ���� ó��
}
char get_rate(short UID, short AID) {
	for (Review* temp = root_review; temp != NULL; temp = temp->next)
		if (temp->UID == UID && temp->AID == AID)
			return temp->rate;
	// ���� ó��
}
char* get_comment(short UID, short AID) {
	for (Review* temp = root_review; temp != NULL; temp = temp->next)
		if (temp->UID == UID && temp->AID == AID)
			return temp->comment;
	// ���� ó��
}
int get_revenue(short AID) {
	for (App* temp = root_app; temp != NULL; temp = temp->next)
		if (temp->AID == AID)
			return temp->revenue;
	// ���� ó��
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
///////////////////////////������ ���� �Լ���////////////
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
int get_num_who(char type) { // 0 = ���� / 1 = �Ǹ��� / 2 = ���α׷�
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
bool chk_report() {
	for (App* temp = root_app; temp != NULL; temp = temp->next)
		if (temp->is_report) return true;
	return false;
}