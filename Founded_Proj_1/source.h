// 함수 소스 헤더파일
#pragma once
#include "word_define.h"

// 박스 그리는 함수
void draw_box();
// 타이틀 그리는 함수
// Input : title_name[string]
void draw_title(const char title_name[]);

// 메시지 팝업 함수
// Input : message[string]
void draw_message(char* message);
// 페이지 설명 함수
void draw_page();
// 판매자 페이지 설명 함수
void draw_seller_page();
// 작은 버튼 제작 함수
void draw_button(Point p, char* str);
// 종료 출력 함수
void draw_quit();
// 설명문 팝업
bool popup_Explantion(char* msg);
// URL 팝업
bool URL_popup_Explantion(wchar_t* msg);
// 작은 박스 그리는 함수
void draw_lil_box(Point p1, Point p2);

// 타이틀 선택 함수
PNS select_title();
// 회원가입 선택 함수
void select_register();

// 색깔 입력 함수 원형
// 사용시 기본으로 돌려놓을 것
void textcolor(Color_num foreground, Color_num background);
// 좌표 이동 함수
void gotoxy(int x, int y);
// 선택 강조 함수
void select_color(char* str);
// 글자 강조 함수
// 색은 열거형 참조
void choice_color(Color_num t_color, Color_num bg_color, char* str);
// 언어 및 선택 출력 함수
void print_choice_lang(const char* kor, const char* eng, bool choice);
// 글자 비활성화 함수
void disable_color(char* str);

// 입력 함수
void input_some(const char str[], char some[]);
// 공백 포함 입력 함수
void input_blank_some(const char str[], char some[], rsize_t len_str);
// URL만 받는 함수
void input_only_url(const char str[], wchar_t some[], rsize_t len_str);
// 질문 입력 함수
int select_question(int old_select);
// 장르 입력 함수
int input_genre(int old_genre);
// 확장자 입력 함수
int input_extension(int old_extension);
// 가격 입력 함수
// 정수가 아닌 입력이 들어오면 -1 반환
int set_money();

// 회원가입 정보 저장 콜백 함수
// insert_user = 유저 / insert_seller = 판매자
void insert_call(char* id, char* pw, char* nickname, short question, char* answer,
	void(*func)(char* id, char* pw, char* nickname, short question, char* answer));
void insert_user(char* id, char* pw, char* nickname, short question, char* answer);
void insert_seller(char* id, char* pw, char* nickname, short question, char* answer);
// 연결 삭제 콜백 함수
// delete_user = 유저 / delete_seller = 판매자 / delete_application = 프로그램
void delete_call(short ID, void(*func)(short ID));
void delete_user(short UID);
void delete_seller(short SID);
void delete_application(short AID);
// 회원 정보 수정 콜백 함수
// update_user = 유저 / update_seller = 판매자
void update_call(short ID, char* nickname, short question, char* answer, bool lang,
	void(*func)(short ID, char* nickname, short question, char* answer, bool lang));
// 유저 돈 가감 함수
void update_user_money(short UID, int money, bool op);
void update_user_aCount(short UID);
// 비밀번호 변경 콜백 함수
// change_pw_user = 유저 / change_pw_seller = 판매자
void change_pw(char* pw, short ID, void(*func)(char* pw));
void change_pw_user(char* pw, short UID);
void change_pw_seller(char* pw, short SID);
// 메모리 할당 해제 함수
void free_all();
// 프로그램 저장 함수
void insert_application(
	char* k_name, char* e_name, char* k_exp, char* e_exp,
	wchar_t* url, char genre, char extension,
	short SID, int price, char lang_set);
// 저장 폴더 제작 함수
void make_temp_folder();

// 에러 코드 처리 함수
// 입력 : 에러 코드
void error(int code);

// 계정 확인 함수
// 출력 : 1 성공 / 0 비밀번호 불일치 / -1 일치하는 아이디 X
// is_user = 유저 / is_seller = 판매자
int is_who(Account ac, short type, int(*func)(Account ac, short type));
int is_user(Account ac, short type);
int is_seller(Account ac, short type);
// 새로운 계정 확인 함수
// 출력 : TRUE 동일한 계정 X / FALSE 동일한 계정 O
// is_new_user = 유저 / is_new_seller = 판매자
bool is_new_who(char* id, int(*func)(char*));
bool is_new_user(char* id);
bool is_new_seller(char* id);
// 비밀번호 인증 함수
// 출력 : UID 존재함 / -1 존재안함
int is_exit_id(char* id, short quest, char* answer);
// ID 반환 함수
// 출력 : ID
// get_UID = 유저 / get_SID = 판매자
int who_ID(Account ac, int(*func)(Account ac));
int get_UID(Account ac);
int get_SID(Account ac);
// 비밀번호 확인 함수
// 1 일치 / 0 불일치
int check_pw(short UID, char* pw);
// 정보 가져오기 함수
User* get_data(short UID);
Seller* get_data_seller(short SID);
int get_money(short UID);
wchar_t* get_URL(short AID);
char get_extension(short AID);
// output 전용 함수들
char* output_extension(char extension);
char* output_genre(char genre);

// 비밀번호 암호화 함수
int make_pw_num(char* password);
// URL 다운로드 및 성공 여부 확인 함수
int check_url(wchar_t* URL, char extension, char* name);

// 유저 마이 페이지 함수
int my_page(short UID);
// 판매자 마이페이지 함수
int seller_page(short SID);
// 유저 라이브러리 페이지 함수
int library_page(short UID);
// 유저 상점 페이지 함수
int shop_page(short UID);