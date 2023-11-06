// 파일 관련 함수

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#include "source.h"
#include "word_define.h"

// 전역 변수 모음
short UID_count = 0;
short SID_count = 0;
User * root_user = NULL;
Seller * root_seller = NULL;
App * root_app = NULL;
Review * root_review = NULL;
bool set_language = true;

///////////////////
void save_user_file();
void read_user_file();
void save_proj_file();
void read_proj_file();
void save_seller_file();
void read_seller_file();
///////////////////
void insert_call(char* id, char* pw, char* nickname, short question, char* answer,
	void(*func)(char* id, char* pw, char* nickname, short question, char* answer)) {
	func(id, pw, nickname, question, answer);
}
void insert_user(char* id, char* pw, char* nickname, short question, char* answer) {
	User* temp = (User*)malloc(sizeof(User));
	strcpy(temp->id, id);
	temp->password = make_pw_num(pw);
	strcpy(temp->nickname, nickname);
	temp->question = question;
	strcpy(temp->answer, answer);
	temp->prog_count = 0;
	temp->report_count = 0;
	temp->money = 0;
	temp->lang = set_language;
	temp->next = NULL;
	temp->UID = UID_count++;

	if (root_user == NULL) root_user = temp;
	else {
		temp->next = root_user;
		root_user = temp;
	}
	save_user_file();
	save_proj_file();
}
void insert_seller(char* id, char* pw, char* nickname, short question, char* answer) {
	Seller* temp = (Seller*)malloc(sizeof(Seller));
	strcpy(temp->id, id);
	temp->password = make_pw_num(pw);
	strcpy(temp->nickname, nickname);
	temp->question = question;
	strcpy(temp->answer, answer);
	temp->prog_count = 0;
	temp->report_count = 0;
	temp->money = 0;
	temp->lang = set_language;
	temp->next = NULL;
	temp->SID = UID_count++;

	if (root_seller == NULL) root_seller = temp;
	else {
		temp->next = root_seller;
		root_seller = temp;
	}
	save_seller_file();
	save_proj_file();
}
///////////////////
void delete_call(short ID, void(*func)(short ID)) { func(ID); }
void delete_user(short UID) {
	User* prev = root_user;

	for (User* temp = root_user; temp == NULL; temp = temp->next) {
		if (temp->UID == UID) {
			prev->next = temp->next;
			free(temp);
			save_user_file();
			return;
		}
		prev = temp;
	}
	// 에러 처리
}
void delete_seller(short SID) {
	Seller* prev = root_seller;

	for (Seller* temp = root_seller; temp == NULL; temp = temp->next) {
		if (temp->SID == SID) {
			prev->next = temp->next;
			free(temp);
			save_seller_file();
			return;
		}
		prev = temp;
	}
	// 에러 처리
}
///////////////////
void update_call(short ID, char* nickname, short question, char* answer, bool lang,
	void(*func)(short ID, char* nickname, short question, char* answer, bool lang)) {
	func(ID, nickname, question, answer, lang);
}
void update_user(short UID, char* nickname, short question, char* answer, bool lang) {
	for (User* temp = root_user; temp == NULL; temp = temp->next) {
		if (temp->UID == UID) {
			strcpy(temp->nickname, nickname);
			temp->question = question;
			strcpy(temp->answer, answer);
			temp->lang = lang;
			save_user_file();
			return;
		}
	}
	// 에러 처리
}
void update_seller(short SID, char* nickname, short question, char* answer, bool lang) {
	for (Seller* temp = root_seller; temp == NULL; temp = temp->next) {
		if (temp->SID == SID) {
			strcpy(temp->nickname, nickname);
			temp->question = question;
			strcpy(temp->answer, answer);
			temp->lang = lang;
			save_seller_file();
			return;
		}
	}
	// 에러 처리
}
///////////////////
void update_user_money(short UID, int money, bool op) {
	for (User* temp = root_user; temp == NULL; temp = temp->next) {
		if (temp->UID == UID) {
			if (op) temp->money += money;
			else temp->money -= money;
			save_user_file();
			return;
		}
	}
	// 에러 처리
}
///////////////////
void change_pw(char* pw, short ID, void(*func)(char* pw)) { func(pw); }
void change_pw_user(char* pw, short UID) {
	for (User* temp = root_user; temp == NULL; temp = temp->next) {
		if (temp->UID == UID) {
			temp->password = make_pw_num(pw);
			return;
		}
	}
	// 에러 처리
}
void change_pw_seller(char* pw, short SID) {
	for (Seller* temp = root_seller; temp == NULL; temp = temp->next) {
		if (temp->SID == SID) {
			temp->password = make_pw_num(pw);
			return;
		}
	}
	// 에러 처리
}
///////////////////
void save_user_file() {
	FILE* fp = NULL;
	User* temp = root_user;

	if ((fp = fopen("data/user.bin", "wb")) == NULL) {
		system("mkdir data");
		error(100);
	}
	else {
		while(temp != NULL){
			fwrite(temp, sizeof(User), 1, fp);
			temp = temp->next;
		}
		fclose(fp);
	}
}
void read_user_file() {
	FILE* fp = NULL;
	User* temp = root_user;
	bool flag = TRUE;

	if ((fp = fopen("data/user.bin", "rb")) == NULL) {
		save_user_file();
		error(101);
	}
	else {
		do{
			fread(temp, sizeof(User), 1, fp);

			if (flag) {
				root_user = temp;
				flag = FALSE;
			}
			temp = temp->next;
		} while (temp != NULL);
		fclose(fp);
	}

}

void save_proj_file() {
	FILE* fp = NULL;
	Proj_setting proj;

	proj.max_uid = UID_count;
	proj.max_sid = SID_count;

	if ((fp = fopen("data/proj.bin", "wb")) == NULL) {
		system("mkdir data");
		error(102);
	}
	else {
		fwrite(&proj, sizeof(proj), 1, fp);
		fclose(fp);
	}
}
void read_proj_file() {
	FILE* fp = NULL;
	Proj_setting proj = { 0 };

	if ((fp = fopen("data/proj.bin", "rb")) == NULL) {
		save_proj_file();
		error(103);
	}
	else {
		fread(&proj, sizeof(proj), 1, fp);
		fclose(fp);
	}
	
	UID_count = proj.max_uid;
	SID_count = proj.max_sid;
}
void save_seller_file() {
	FILE* fp = NULL;
	Seller* temp = root_seller;

	if ((fp = fopen("data/seller.bin", "wb")) == NULL) {
		system("mkdir data");
		error(104);
	}
	else {
		while (temp != NULL) { 
			fwrite(temp, sizeof(temp), 1, fp);
			temp = temp->next;
		}
		fclose(fp);
	}
}
void read_seller_file() {
	FILE* fp = NULL;
	User* temp = root_seller;
	bool flag = TRUE;

	if ((fp = fopen("data/seller.bin", "rb")) == NULL) {
		
		save_seller_file();
		error(105);
	}
	else {
		while (temp != NULL) {
			fread(temp, sizeof(temp), 1, fp);
			if (flag == TRUE) {
				root_seller = temp;
				flag = FALSE;
			}
			temp = temp->next;
		}
		fclose(fp);
	}
}