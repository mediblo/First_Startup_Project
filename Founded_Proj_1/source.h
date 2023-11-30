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
// 뒤로가기 설명 함수
void draw_ESC();
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
// 리뷰 팝업
bool popup_review(char* msg, float rate);
// 신고 팝업
bool popup_report(short reason);

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
// 신고 입력 함수
int input_report(int old_report, short UID, short AID, bool flag);
// 가격 입력 함수
// 정수가 아닌 입력이 들어오면 재호출
int set_money();
// 평점 입력 함수
int set_rate();
// output 전용 함수들
char* output_extension(char extension);
char* output_genre(char genre);
char* output_report(char report);

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
void update_user(short UID, char* nickname, short question, char* answer, bool lang);
void update_seller(short SID, char* nickname, short question, char* answer, bool lang);
// 업데이트 함수
void update_user_money(short UID, int money, bool op);
void update_user_aCount(short UID);
void update_AID_D_count(short UID, short AID, bool op);
void update_seller_revenue(short SID, int price);
void update_revenue(short AID, int price);
void update_repData(Rep_data RD, short AID);
void update_app_disable(short AID, bool flag);
void update_cls_repData(short AID);
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
// AID_D 관련 함수
void insert_AID_D(short UID, AData AD);
void delete_AID_D(short UID, short AID);
// 리뷰 관련 함수
void insert_review(short UID, short AID, char* comment, char rate);
void update_review(short UID, short AID, char* comment, char rate);
// 저장 폴더 제작 함수
void make_temp_folder();
// 파일 존재하는지 확인하는 함수
bool is_hav_file(char extension, char* name);
// 관리자 계정 가져오기 함수 [ 읽기 전용 ]
Admin get_admin();

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
// 이미 가지고 있는 프로그램인가?
bool is_hav_app(short UID, short AID);
// 해당 프로그램에 대해 리뷰를 쓴 적이 있는가?
bool is_write_review(short UID, short AID);
// 해당 프로그램에 대해 신고를 한 적이 있는가?
// 처리안되어있으면 true 처리되면 false
bool is_report_write(short AID, short UID);
// 비밀번호 인증 함수
// 출력 : UID 존재함 / -1 존재안함
// is_exit_id = 유저 / is_exit_id_seller = 판매자
int is_exit_who(char* id, short quest, char* answer, int(*func)(char* id, short quest, char* answer));
int is_exit_id(char* id, short quest, char* answer);
int is_exit_id_seller(char* id, int quest, char* answer);
// 검색이 있나요? [ -1 없어요 / AID = 있어요 ]
short is_search(char* msg);
short is_user_search(char* msg);
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
char get_genre(short AID);
char get_rate(short UID, short AID);
char* get_comment(short UID, short AID);
char* get_name(short UID);
int get_revenue(short AID);
int get_SID_from_AID(short AID);
short get_report_reason(short AID, short UID);

// 비밀번호 암호화 함수
int make_pw_num(char* password);
// URL 다운로드 및 성공 여부 확인 함수
int check_url(wchar_t* URL, char extension, char* name);

// 유저 마이 페이지 함수
int my_page(short UID);
// 유저 라이브러리 페이지 함수
int library_page(short UID);
// 유저 상점 페이지 함수
int shop_page(short UID);
// 유저 프로그램 페이지 함수
void app_page(short UID, AData AD);
// 판매자 마이페이지 함수
int seller_page(short SID);
// 판매자 라이브러리 페이지 함수
int seller_library_page(short SID);
// 판매자 프로그램 페이지 함수
void seller_app_page(short SID, AData AD);
// 리뷰 확인 페이지 함수
void review_view_page(AData AD);

// 어드민 로그인 확인 함수
int is_admin(Account ac);
// 유저/판매자/프로그램 수 확인 함수
int get_num_who(char type);
// 어드민 페이지 함수
int admin_page();
// 신고 활성화 체크 함수 [ T = is_report / F = is_disable ]
bool chk_report(bool flag);
// AID 리스트 반환 함수 [ T = 신고 먹은 놈들만 / F = 비활성화 친구들만 ] / 나머진 -1
void get_AID_list(short AID_list[], bool flag);
// aName 리스트 반환 함수s
char* get_aNameList(short AID_list[], char aNameList[][20]);
// 신고 사유 확인 함수
void report_view_page(short AID, char* A_name);
// 간이 신고 종류 카운트 함수
short* get_rep_count(short rep_count[], short AID);