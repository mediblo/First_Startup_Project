// 단어 정의 모음 헤더파일
#pragma once
#include <stdbool.h>

// 박스 크기
#define X_MAX 100
#define Y_MAX 30

// 키보드 숫자
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

// 좌표설정에 용이하기 위해 제작한 포인트 구조체
typedef struct {
	int x;
	int y;
} Point;

// 확인용 아이디, 비밀번호를 가지는 계정 구조체
typedef struct {
	char* id;
	char* password;
} Account;

// TYPE 1. 사용자 및 판매자 구조체
// 돈 추가해야함
typedef struct user{
	char id[20]; // 아이디
	int password; // 비밀번호
	char nickname[20]; // 닉네임
	short question; // 질문
	char answer[20]; // 답변
	short UID; // 고유 UID
	int money; // 돈
	short report_count; // 신고 횟수
	short prog_count; // 프로그램 갯수
	bool lang; // 언어 설정 true = kor / false = eng
	struct user* next; // 연결리스트
} User;

// TYPE 2. 판매자 구조체
typedef struct seller{
	char id[20]; // 아이디
	int password; // 비밀번호
	char nickname[20]; // 가게 또는 개발자 이름
	short question; // 질문
	char answer[20]; // 답변
	short SID; // 고유 SID
	short report_count; // 신고 횟수
	short prog_count; // 프로그램 갯수
	int money; // 매출
	bool lang; // 언어 설정 true = kor / false = eng
	struct seller* next; // 연결리스트
} Seller;

// TYPE 3. 관리자 구조체
typedef struct administrator{
	char id[20];
	char password[20];
} Admin;

// 프로그램 구조체
typedef struct application{
	char kor_name[20]; // 프로그램 이름 [ 한국어 ]
	char eng_name[20]; // 프로그램 이름 [ 영어 ]
	char kor_explanation[101]; // 프로그램 소개말 [50자 이내]
	char eng_explanation[101]; // 프로그램 소개말 [100자 이내]
	wchar_t url[200]; // 다운로드 URL / HOL 231004 참조
	char genre; // 장르
	char extension; // 확장자
	short SID; // 판매자 고유 ID
	short GID; // 프로그램 고유 ID
	int price; // 가격
	char lang_set; // 지원 언어 [ 0 = 둘 다, 1 = 한국어, 2 = 영어 ]
	struct application* next; // 연결리스트
} App;

typedef struct review {
	short UID; // 유저 고유 ID
	short GID; // 프로그램 고유 ID
	short RID; // 리뷰 ID
	char comment[101]; // 리뷰 [ kor = 50, eng = 100자 이내 ]
	struct review* next; // 연결리스트
} Review;

// 프로그램 내부 주요 정보 구조체
typedef struct project_secret_setting{
	short max_uid;
	short max_sid;
	Admin admin;
} Proj_setting;

typedef struct project_normal_setting{
	short type; // 현재 사용자 타입 [ 0 = USER / 1 = SELLER / 2 = ADMIN ]
	short id; // 고유번호 [ ID랑 혼동하지 말 것 ]
} PNS;

extern User* root_user; // 유저 전역변수
extern Seller* root_seller; // 판매자 전역변수
extern App* root_app; // 프로그램 전역변수
extern Review* root_review; // 리뷰 전역변수
extern short UID_count; // UID 카운트
extern short SID_count; // SID 카운트
extern bool set_language; // 현재 언어 설정

// 색깔 찾기 귀찮아서 만든 열거형
typedef enum {
	black, blue, green, cyan, red,
	magenta, bronw, lightGray, darkGray, lightBlue,
	lightGreen, lightCyan, lightRed, lightMagenta, yellow,
	white
} Color_num;
