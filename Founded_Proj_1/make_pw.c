// 비밀번호 암호화 함수
#include <string.h>

#include "source.h"
#include "word_define.h"

int make_pw_num(char* password);

int make_pw_num(char* password) {
	int temp = 0;
	for (int i = 0; i < strlen(password); i++)
		temp += password[i] * 4 + i;

	return temp;
}