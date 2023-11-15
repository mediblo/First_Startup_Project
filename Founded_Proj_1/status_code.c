// 에러 처리 함수
#include <stdio.h>
#include <Windows.h>

// 100번대 - 파일 부분 오류
// 200번대 - 동적할당 연결리스트 관련 오류
void error(int code) {
	free_all();
	system("cls");
	switch (code) {
		case 2:
			printf("질문 선택 오류");
			break;
		case 3:
			printf("select_title : 예기치 못한 오류");
		case 5:
			printf("get_UID : UID가 없음");
			break;
		case 6:
			printf("get_SID : SID가 없음");
			break;
		case 7:
			printf("popup_Explantion : 부적절한 종료");
			break;
		case 100:
			printf("user.bin 제작 or data폴더 없음 오류");
			break;
		case 101:
			printf("user.bin 읽기 오류");
			break;
		case 102:
			printf("proj.bin 제작 or data폴더 없음 오류");
			break;
		case 103:
			printf("proj.bin 읽기 오류");
			break;
		case 104:
			printf("seller.bin 제작 or data폴더 없음 오류");
			break;
		case 105:
			printf("seller.bin 읽기 오류");
			break;
		case 106:
			printf("application.bin 제작 or data폴더 없음 오류");
			break;
		case 107:
			printf("application.bin 읽기 오류");
			break;
		case 108:
			printf("저장 폴더 없음");
			break;
		case 109:
			printf("AID_D.bin 읽기 오류");
			break;
		case 200:
		case 201:
		case 202:
			printf("동적할당 Delete 오류");
			break;
		case 210:
		case 211:
		case 212:
		case 213:
		case 214:
			printf("동적할당 Update 오류");
			break;
		case 220:
		case 221:
			printf("동적할당 Change 오류");
		default:
			printf("다른 인위적 에러");
	}
	if (100 <= code && code < 200) printf("\n제작중... 다시 실행해주세요.");
	else printf("\n관리자 호출 필요");
	printf("\nError Code : %d", code);
	exit(1);
}