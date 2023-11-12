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
// ���� ��ư ���� �Լ�
void draw_button(Point p, char* str);
// ���� ��� �Լ�
void draw_quit();
// ���� �˾�
bool popup_Explantion(char* msg);
// ���� �ڽ� �׸��� �Լ�
void draw_lil_box(Point p1, Point p2);

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
// ���� �Է� �Լ�
// ������ �ƴ� �Է��� ������ -1 ��ȯ
int set_money();

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
// ���� �� ���� �Լ�
void update_user_money(short UID, int money, bool op);
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
// ���� ���� ���� �Լ�
void make_temp_folder();

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
// ��й�ȣ ���� �Լ�
// ��� : UID ������ / -1 �������
int is_exit_id(char* id, short quest, char* answer);
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
// output ���� �Լ���
char* output_extension(char extension);
char* output_genre(char genre);

// ��й�ȣ ��ȣȭ �Լ�
int make_pw_num(char* password);

// ���� ���� ������ �Լ�
int my_page(short UID);
// �Ǹ��� ���������� �Լ�
int seller_page(short SID);
// ���� ���̺귯�� ������ �Լ�
int library_page(short UID);
// ���� ���� ������ �Լ�
int shop_page(short UID);