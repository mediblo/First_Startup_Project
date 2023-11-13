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
short AID_count = 0;
short UID_max = 0;
short SID_max = 0;
short AID_max = 0;
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
void save_application_file();
void read_application_file();
///////////////////
void update_seller_aCount(short SID, bool op);
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
	temp->UID = UID_max++;
	UID_count++;

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
	temp->SID = SID_max++;
	SID_count++;

	if (root_seller == NULL) root_seller = temp;
	else {
		temp->next = root_seller;
		root_seller = temp;
	}
	save_seller_file();
	save_proj_file();
}
void insert_application(
	char* k_name, char* e_name, char* k_exp, char* e_exp,
	wchar_t* url, char genre, char extension,
	short SID, int price, char lang_set) {
	App* temp = (App*)malloc(sizeof(App));
	strcpy(temp->kor_name, k_name);
	strcpy(temp->eng_name, e_name);
	strcpy(temp->kor_explanation, k_exp);
	strcpy(temp->eng_explanation, e_exp);
	wcscpy(temp->url, url);
	temp->genre = genre;
	temp->extension = extension;
	temp->SID = SID;
	temp->price = price;
	temp->lang_set = lang_set;
	temp->next = NULL;
	temp->AID = AID_max++;
	AID_count++;
	update_seller_aCount(SID, true);

	if (root_app == NULL) root_app = temp;
	else {
		temp->next = root_app;
		root_app = temp;
	}
	save_application_file();
	save_proj_file();
}
///////////////////
void delete_call(short ID, void(*func)(short ID)) { func(ID); }
void delete_user(short UID) {
	User* prev = root_user;

	for (User* temp = root_user; temp != NULL; temp = temp->next) {
		if (temp->UID == UID) {
			prev->next = temp->next;
			free(temp);
			if (--UID_count != 0) save_user_file();
			else root_user = NULL;
			return;
		}
		prev = temp;
	}
	// 에러 처리
}
void delete_seller(short SID) {
	Seller* prev = root_seller;

	for (Seller* temp = root_seller; temp != NULL; temp = temp->next) {
		if (temp->SID == SID) {
			prev->next = temp->next;
			free(temp);
			if (--SID_count != 0)save_seller_file();
			else root_seller = NULL;
			return;
		}
		prev = temp;
	}
	// 에러 처리
}
void delete_application(short AID) {
	App* prev = root_app;

	for (App* temp = root_app; temp != NULL; temp = temp->next) {
		if (temp->AID == AID) {
			prev->next = temp->next;
			free(temp);
			if (--AID_count != 0)save_application_file();
			else root_app = NULL;
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
	for (User* temp = root_user; temp != NULL; temp = temp->next) {
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
	for (Seller* temp = root_seller; temp != NULL; temp = temp->next) {
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
	for (User* temp = root_user; temp != NULL; temp = temp->next) {
		if (temp->UID == UID) {
			if (op) temp->money += money;
			else temp->money -= money;
			save_user_file();
			return;
		}
	}
	// 에러 처리
}
void update_user_aCount(short UID) {
	for (User* temp = root_user; temp != NULL; temp = temp->next) {
		if (temp->UID == UID) {
			temp->prog_count++;
			save_user_file();
			return;
		}
	}
	// 에러 처리
}
void update_seller_aCount(short SID, bool op) {
	for (Seller* temp = root_seller; temp != NULL; temp = temp->next) {
		if (temp->SID == SID) {
			if (op) temp->prog_count++;
			else temp->prog_count--;
			save_seller_file();
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
	User* temp = NULL; // 데이터를 받을 더미
	User** temp_root = &root_user; // 루트에 연결할 더미

	if ((fp = fopen("data/user.bin", "rb")) == NULL) {
		save_user_file();
		error(101);
	}
	else {
		while(1){
			temp = (User*)malloc(sizeof(User)); // 데이터 입력 받기 전 메모리 할당 [ 안하면 메모리 없는거! ]
			if (fread(temp, sizeof(User), 1, fp) != 1) { // 데이터 입력이 정상인지 판별
				if(temp != NULL) free(temp); // NULL일 때 free하면 메모리 누수가 일어난다.
				break; // 다 읽었으면 끝내
			}
			*temp_root = temp; // 데이터를 읽고
			temp_root = &temp->next; // 다음 주소로 이동
		} 
		fclose(fp);
	}
}
void save_proj_file() {
	FILE* fp = NULL;
	Proj_setting proj;

	proj.count_uid = UID_count;
	proj.count_sid = SID_count;
	proj.count_aid = AID_count;
	proj.max_uid = UID_max;
	proj.max_sid = SID_max;
	proj.max_aid = AID_max;

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
		strcpy(proj.admin.id, "asdf");
		proj.admin.password = make_pw_num("1111");
		error(103);
	}
	else {
		fread(&proj, sizeof(proj), 1, fp);
		fclose(fp);
	}
	
	UID_count = proj.count_uid;
	SID_count = proj.count_sid;
	AID_count = proj.count_aid;
	UID_max = proj.max_uid;
	SID_max = proj.max_sid;
	AID_max = proj.max_aid;
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
			fwrite(temp, sizeof(Seller), 1, fp);
			temp = temp->next;
		}
		fclose(fp);
	}
}
void read_seller_file() {
	FILE* fp = NULL;
	Seller* temp = NULL;
	Seller** temp_root = &root_seller;

	if ((fp = fopen("data/seller.bin", "rb")) == NULL) {
		
		save_seller_file();
		error(105);
	}
	else {
		while (1) {
			temp = (Seller*)malloc(sizeof(Seller));
			if (fread(temp, sizeof(Seller), 1, fp) != 1) {
				if (temp != NULL) free(temp);
				break;
			}
			*temp_root = temp;
			temp_root = &temp->next;
		}
		fclose(fp);
	}
}
void save_application_file() {
	FILE* fp = NULL;
	App* temp = root_app;

	if ((fp = fopen("data/application.bin", "wb")) == NULL) {
		system("mkdir data");
		error(106);
	}
	else {
		while (temp != NULL) {
			fwrite(temp, sizeof(App), 1, fp);
			temp = temp->next;
		}
		fclose(fp);
	}
}
void read_application_file() {
	FILE* fp = NULL;
	App* temp = NULL; // 데이터를 받을 더미
	App** temp_root = &root_app; // 루트에 연결할 더미

	if ((fp = fopen("data/application.bin", "rb")) == NULL) {
		save_application_file();
		error(107);
	}
	else {
		while (1) {
			temp = (App*)malloc(sizeof(App)); // 데이터 입력 받기 전 메모리 할당 [ 안하면 메모리 없는거! ]
			if (fread(temp, sizeof(App), 1, fp) != 1) { // 데이터 입력이 정상인지 판별
				if (temp != NULL) free(temp); // NULL일 때 free하면 메모리 누수가 일어난다.
				break; // 다 읽었으면 끝내
			}
			*temp_root = temp; // 데이터를 읽고
			temp_root = &temp->next; // 다음 주소로 이동
		}
		fclose(fp);
	}
}
void make_temp_folder() {
	FILE* fp = NULL;

	if ((fp = fopen("download/temp.txt", "wb")) == NULL) {
		system("mkdir download");
		error(108);
	}
	fclose(fp);
}
///////////////////
void free_user() {
	while (root_user != NULL) {
		User* temp = root_user;
		root_user = root_user->next;
		free(temp);
	}
}
void free_seller() {
	while (root_seller != NULL) {
		User* temp = root_seller;
		root_seller = root_seller->next;
		free(temp);
	}
}
void free_application() {
	while (root_app != NULL) {
		User* temp = root_app;
		root_app = root_app->next;
		free(temp);
	}
}
void free_all() {
	free_user();
	free_seller();
	free_application();
}