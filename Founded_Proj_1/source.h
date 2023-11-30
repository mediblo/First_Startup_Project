// �Լ� �ҽ� �������
#pragma once
#include "word_define.h"

// �ڽ� �׸��� �Լ�
void draw_box();
// Ÿ��Ʋ �׸��� �Լ�
// Input : title_name[string]
void draw_title(const char title_name[]);

// �޽��� �˾� �Լ�
// Input : message[string]
void draw_message(char* message);
// ������ ���� �Լ�
void draw_page();
// �Ǹ��� ������ ���� �Լ�
void draw_seller_page();
// �ڷΰ��� ���� �Լ�
void draw_ESC();
// ���� ��ư ���� �Լ�
void draw_button(Point p, char* str);
// ���� ��� �Լ�
void draw_quit();
// ���� �˾�
bool popup_Explantion(char* msg);
// URL �˾�
bool URL_popup_Explantion(wchar_t* msg);
// ���� �ڽ� �׸��� �Լ�
void draw_lil_box(Point p1, Point p2);
// ���� �˾�
bool popup_review(char* msg, float rate);
// �Ű� �˾�
bool popup_report(short reason);

// Ÿ��Ʋ ���� �Լ�
PNS select_title();
// ȸ������ ���� �Լ�
void select_register();

// ���� �Է� �Լ� ����
// ���� �⺻���� �������� ��
void textcolor(Color_num foreground, Color_num background);
// ��ǥ �̵� �Լ�
void gotoxy(int x, int y);
// ���� ���� �Լ�
void select_color(char* str);
// ���� ���� �Լ�
// ���� ������ ����
void choice_color(Color_num t_color, Color_num bg_color, char* str);
// ��� �� ���� ��� �Լ�
void print_choice_lang(const char* kor, const char* eng, bool choice);
// ���� ��Ȱ��ȭ �Լ�
void disable_color(char* str);

// �Է� �Լ�
void input_some(const char str[], char some[]);
// ���� ���� �Է� �Լ�
void input_blank_some(const char str[], char some[], rsize_t len_str);
// URL�� �޴� �Լ�
void input_only_url(const char str[], wchar_t some[], rsize_t len_str);
// ���� �Է� �Լ�
int select_question(int old_select);
// �帣 �Է� �Լ�
int input_genre(int old_genre);
// Ȯ���� �Է� �Լ�
int input_extension(int old_extension);
// �Ű� �Է� �Լ�
int input_report(int old_report, short UID, short AID, bool flag);
// ���� �Է� �Լ�
// ������ �ƴ� �Է��� ������ ��ȣ��
int set_money();
// ���� �Է� �Լ�
int set_rate();
// output ���� �Լ���
char* output_extension(char extension);
char* output_genre(char genre);
char* output_report(char report);

// ȸ������ ���� ���� �ݹ� �Լ�
// insert_user = ���� / insert_seller = �Ǹ���
void insert_call(char* id, char* pw, char* nickname, short question, char* answer,
	void(*func)(char* id, char* pw, char* nickname, short question, char* answer));
void insert_user(char* id, char* pw, char* nickname, short question, char* answer);
void insert_seller(char* id, char* pw, char* nickname, short question, char* answer);
// ���� ���� �ݹ� �Լ�
// delete_user = ���� / delete_seller = �Ǹ��� / delete_application = ���α׷�
void delete_call(short ID, void(*func)(short ID));
void delete_user(short UID);
void delete_seller(short SID);
void delete_application(short AID);
// ȸ�� ���� ���� �ݹ� �Լ�
// update_user = ���� / update_seller = �Ǹ���
void update_call(short ID, char* nickname, short question, char* answer, bool lang,
	void(*func)(short ID, char* nickname, short question, char* answer, bool lang));
void update_user(short UID, char* nickname, short question, char* answer, bool lang);
void update_seller(short SID, char* nickname, short question, char* answer, bool lang);
// ������Ʈ �Լ�
void update_user_money(short UID, int money, bool op);
void update_user_aCount(short UID);
void update_AID_D_count(short UID, short AID, bool op);
void update_seller_revenue(short SID, int price);
void update_revenue(short AID, int price);
void update_repData(Rep_data RD, short AID);
void update_app_disable(short AID, bool flag);
void update_cls_repData(short AID);
// ��й�ȣ ���� �ݹ� �Լ�
// change_pw_user = ���� / change_pw_seller = �Ǹ���
void change_pw(char* pw, short ID, void(*func)(char* pw));
void change_pw_user(char* pw, short UID);
void change_pw_seller(char* pw, short SID);
// �޸� �Ҵ� ���� �Լ�
void free_all();
// ���α׷� ���� �Լ�
void insert_application(
	char* k_name, char* e_name, char* k_exp, char* e_exp,
	wchar_t* url, char genre, char extension,
	short SID, int price, char lang_set);
// AID_D ���� �Լ�
void insert_AID_D(short UID, AData AD);
void delete_AID_D(short UID, short AID);
// ���� ���� �Լ�
void insert_review(short UID, short AID, char* comment, char rate);
void update_review(short UID, short AID, char* comment, char rate);
// ���� ���� ���� �Լ�
void make_temp_folder();
// ���� �����ϴ��� Ȯ���ϴ� �Լ�
bool is_hav_file(char extension, char* name);
// ������ ���� �������� �Լ� [ �б� ���� ]
Admin get_admin();

// ���� �ڵ� ó�� �Լ�
// �Է� : ���� �ڵ�
void error(int code);

// ���� Ȯ�� �Լ�
// ��� : 1 ���� / 0 ��й�ȣ ����ġ / -1 ��ġ�ϴ� ���̵� X
// is_user = ���� / is_seller = �Ǹ���
int is_who(Account ac, short type, int(*func)(Account ac, short type));
int is_user(Account ac, short type);
int is_seller(Account ac, short type);
// ���ο� ���� Ȯ�� �Լ�
// ��� : TRUE ������ ���� X / FALSE ������ ���� O
// is_new_user = ���� / is_new_seller = �Ǹ���
bool is_new_who(char* id, int(*func)(char*));
bool is_new_user(char* id);
bool is_new_seller(char* id);
// �̹� ������ �ִ� ���α׷��ΰ�?
bool is_hav_app(short UID, short AID);
// �ش� ���α׷��� ���� ���並 �� ���� �ִ°�?
bool is_write_review(short UID, short AID);
// �ش� ���α׷��� ���� �Ű� �� ���� �ִ°�?
// ó���ȵǾ������� true ó���Ǹ� false
bool is_report_write(short AID, short UID);
// ��й�ȣ ���� �Լ�
// ��� : UID ������ / -1 �������
// is_exit_id = ���� / is_exit_id_seller = �Ǹ���
int is_exit_who(char* id, short quest, char* answer, int(*func)(char* id, short quest, char* answer));
int is_exit_id(char* id, short quest, char* answer);
int is_exit_id_seller(char* id, int quest, char* answer);
// �˻��� �ֳ���? [ -1 ����� / AID = �־�� ]
short is_search(char* msg);
short is_user_search(char* msg);
// ID ��ȯ �Լ�
// ��� : ID
// get_UID = ���� / get_SID = �Ǹ���
int who_ID(Account ac, int(*func)(Account ac));
int get_UID(Account ac);
int get_SID(Account ac);
// ��й�ȣ Ȯ�� �Լ�
// 1 ��ġ / 0 ����ġ
int check_pw(short UID, char* pw);
// ���� �������� �Լ�
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

// ��й�ȣ ��ȣȭ �Լ�
int make_pw_num(char* password);
// URL �ٿ�ε� �� ���� ���� Ȯ�� �Լ�
int check_url(wchar_t* URL, char extension, char* name);

// ���� ���� ������ �Լ�
int my_page(short UID);
// ���� ���̺귯�� ������ �Լ�
int library_page(short UID);
// ���� ���� ������ �Լ�
int shop_page(short UID);
// ���� ���α׷� ������ �Լ�
void app_page(short UID, AData AD);
// �Ǹ��� ���������� �Լ�
int seller_page(short SID);
// �Ǹ��� ���̺귯�� ������ �Լ�
int seller_library_page(short SID);
// �Ǹ��� ���α׷� ������ �Լ�
void seller_app_page(short SID, AData AD);
// ���� Ȯ�� ������ �Լ�
void review_view_page(AData AD);

// ���� �α��� Ȯ�� �Լ�
int is_admin(Account ac);
// ����/�Ǹ���/���α׷� �� Ȯ�� �Լ�
int get_num_who(char type);
// ���� ������ �Լ�
int admin_page();
// �Ű� Ȱ��ȭ üũ �Լ� [ T = is_report / F = is_disable ]
bool chk_report(bool flag);
// AID ����Ʈ ��ȯ �Լ� [ T = �Ű� ���� ��鸸 / F = ��Ȱ��ȭ ģ���鸸 ] / ������ -1
void get_AID_list(short AID_list[], bool flag);
// aName ����Ʈ ��ȯ �Լ�s
char* get_aNameList(short AID_list[], char aNameList[][20]);
// �Ű� ���� Ȯ�� �Լ�
void report_view_page(short AID, char* A_name);
// ���� �Ű� ���� ī��Ʈ �Լ�
short* get_rep_count(short rep_count[], short AID);