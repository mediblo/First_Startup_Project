// �ܾ� ���� ���� �������
#pragma once
#include <stdbool.h>

// �ڽ� ũ��
#define X_MAX 100
#define Y_MAX 30

// Ű���� ����
#define K_ARROW 224
#define K_LEFT 75
#define K_RIGHT 77
#define K_DOWN 80
#define K_UP 72
#define K_ENTER 13
#define K_SPACE 32
#define K_ESC 27
#define K_F1 59
#define K_F2 60
#define K_F3 61

// ��ǥ������ �����ϱ� ���� ������ ����Ʈ ����ü
typedef struct {
	int x;
	int y;
} Point;

// Ȯ�ο� ���̵�, ��й�ȣ�� ������ ���� ����ü
typedef struct {
	char* id;
	char* password;
} Account;

typedef struct app_data {
	char name[20]; // ���α׷� �̸�
	char explanation[101]; // ���α׷� �Ұ���
	short AID; // ���α׷� ���� ID
	int price; // ���� or ���̺귯������ �ٿ� ���� Ƚ���� ����
} AData;

typedef struct aid_data {
	short UID; // ���� ����
	AData AD; // ���α׷� ���� ����
	struct aid_data* next;
} AID_D;

typedef struct review {
	short UID; // ���� ���� ID
	short AID; // ���α׷� ���� ID
	char rate; // ����
	bool flag; // Ż�� ���� [ Ż��� Ż���� ����ڷ� ������ ]
	char comment[101]; // ���� [ kor = 50, eng = 100�� �̳� ]
	struct review* next; // ���Ḯ��Ʈ
} Review;

typedef struct review_data {
	char name[20]; // �г��� [ Ż��� Unable�� ]
	char comment[101]; // ����
	char rate; // ����
}RData;

typedef struct report_data {
	short UID; // �ߺ��� �����ϱ� ���� UID ����
	char comment[101]; // �Ű� ����
	char reason; // �Ű� ����
} Rep_data;

// TYPE 1. ����� ����ü
// �� �߰��ؾ���
typedef struct user{
	char id[20]; // ���̵�
	int password; // ��й�ȣ
	char nickname[20]; // �г���
	short question; // ����
	char answer[20]; // �亯
	short UID; // ���� UID
	int money; // ��
	short prog_count; // ���α׷� ����
	bool lang; // ��� ���� true = kor / false = eng
	AID_D* appData;
	struct user* next; // ���Ḯ��Ʈ
} User;

// TYPE 2. �Ǹ��� ����ü
typedef struct seller{
	char id[20]; // ���̵�
	int password; // ��й�ȣ
	char nickname[20]; // ���� �Ǵ� ������ �̸�
	short question; // ����
	char answer[20]; // �亯
	short SID; // ���� SID
	short prog_count; // ���α׷� ����
	int revenue; // ����
	bool lang; // ��� ���� true = kor / false = eng
	struct seller* next; // ���Ḯ��Ʈ
} Seller;

// TYPE 3. ������ ����ü
typedef struct administrator{
	char id[20];
	int password;
} Admin;

// ���α׷� ����ü
typedef struct application{
	char kor_name[20]; // ���α׷� �̸� [ �ѱ��� ]
	char eng_name[20]; // ���α׷� �̸� [ ���� ]
	char kor_explanation[101]; // ���α׷� �Ұ��� [50�� �̳�]
	char eng_explanation[101]; // ���α׷� �Ұ��� [100�� �̳�]
	wchar_t url[200]; // �ٿ�ε� URL / HOL 231004 ����
	char genre; // �帣
	char extension; // Ȯ����
	short SID; // �Ǹ��� ���� ID
	short AID; // ���α׷� ���� ID
	int price; // ����
	int revenue; // ����
	char lang_set; // ���� ��� [ 0 = �� ��, 1 = �ѱ���, 2 = ���� ]
	short report_count; // �Ű� ��� ����?
	bool is_report; // ���� �Ű���߳���? [ �� / �ƴ� ]
	bool is_disable; // ���� �� ������? [ �� / �ƴ� ]
	struct application* next; // ���Ḯ��Ʈ
	Review* Rnext; // ���� ���Ḯ��Ʈ
	Rep_data repData[10]; // �Ű� ��� [ �ִ� 10���� ���� ]
} App;

// ���α׷� ���� �ֿ� ���� ����ü
typedef struct project_secret_setting{
	short count_uid;
	short count_sid;
	short count_aid;
	short count_aid_d;
	short count_rid;
	short max_uid;
	short max_sid;
	short max_aid;
	Admin admin;
} Proj_setting;

typedef struct project_normal_setting{
	short type; // ���� ����� Ÿ�� [ 0 = USER / 1 = SELLER / 2 = ADMIN ]
	short id; // ������ȣ [ ID�� ȥ������ �� �� ]
} PNS;

extern User* root_user; // ���� ��������
extern Seller* root_seller; // �Ǹ��� ��������
extern App* root_app; // ���α׷� ��������
extern Review* root_review; // ���� ��������
extern AID_D* root_AID_D; // ������ ������ ���α׷� ��������
extern short UID_count; // UID ī��Ʈ
extern short SID_count; // SID ī��Ʈ
extern short AID_count; // AID ī��Ʈ
extern short AID_D_count; // AID_D ī��Ʈ
extern short RID_count; // RID ī��Ʈ
extern short UID_max; // UID �ִ�
extern short SID_max; // SID �ִ�
extern short AID_max; // AID �ִ�
extern bool set_language; // ���� ��� ����

// ���� ã�� �����Ƽ� ���� ������
typedef enum {
	black, blue, green, cyan, red,
	magenta, bronw, lightGray, darkGray, lightBlue,
	lightGreen, lightCyan, lightRed, lightMagenta, yellow,
	white
} Color_num;

/* �帣 ���
game, vaccine, office, messenger
DB, Graphics, education, Video
Picture, Music, Text, etc
*/

/* Ȯ���� ���
exe, zip, 7z, gif
mp3, wav, mp4, avi
png, jpg, pptx, xlex
txt, hwp, doc, pdf
*/