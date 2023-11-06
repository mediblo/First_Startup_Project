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

// TYPE 1. ����� �� �Ǹ��� ����ü
// �� �߰��ؾ���
typedef struct user{
	char id[20]; // ���̵�
	int password; // ��й�ȣ
	char nickname[20]; // �г���
	short question; // ����
	char answer[20]; // �亯
	short UID; // ���� UID
	int money; // ��
	short report_count; // �Ű� Ƚ��
	short prog_count; // ���α׷� ����
	bool lang; // ��� ���� true = kor / false = eng
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
	short report_count; // �Ű� Ƚ��
	short prog_count; // ���α׷� ����
	int money; // ����
	bool lang; // ��� ���� true = kor / false = eng
	struct seller* next; // ���Ḯ��Ʈ
} Seller;

// TYPE 3. ������ ����ü
typedef struct administrator{
	char id[20];
	char password[20];
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
	short GID; // ���α׷� ���� ID
	int price; // ����
	char lang_set; // ���� ��� [ 0 = �� ��, 1 = �ѱ���, 2 = ���� ]
	struct application* next; // ���Ḯ��Ʈ
} App;

typedef struct review {
	short UID; // ���� ���� ID
	short GID; // ���α׷� ���� ID
	short RID; // ���� ID
	char comment[101]; // ���� [ kor = 50, eng = 100�� �̳� ]
	struct review* next; // ���Ḯ��Ʈ
} Review;

// ���α׷� ���� �ֿ� ���� ����ü
typedef struct project_secret_setting{
	short max_uid;
	short max_sid;
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
extern short UID_count; // UID ī��Ʈ
extern short SID_count; // SID ī��Ʈ
extern bool set_language; // ���� ��� ����

// ���� ã�� �����Ƽ� ���� ������
typedef enum {
	black, blue, green, cyan, red,
	magenta, bronw, lightGray, darkGray, lightBlue,
	lightGreen, lightCyan, lightRed, lightMagenta, yellow,
	white
} Color_num;