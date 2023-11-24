#define _CRT_SECURE_NO_WARNINGS

#include <urlmon.h>

#include "source.h"
#include "word_define.h"

int check_url(wchar_t* URL, char extension, char* name) {
	HRESULT hr;
	char check=0;
	char* type = output_extension(extension);
	wchar_t w_type[6];
	wchar_t w_name[21];

	MultiByteToWideChar(CP_ACP, NULL, type, -1, w_type, 6); // char -> wchar_t 확장자
	MultiByteToWideChar(CP_ACP, NULL, name, -1, w_name, 21); // char -> wchar_t 이름

	wchar_t route[100] = L"download/"; // 기존 9글자
	wcscat(route, w_name); // 최대 21글자
	wcscat(route, L"."); // 1글자
	wcscat(route, w_type); // 최대 6글자
	// 최종 최대 크기 = 9 + 21 + 1 + 6 + 1 = 38글자
	// 크기 에러 나려면 누군가 내 머리 부시고 코드를 조지는 방법 밖에 없다.

	hr = URLDownloadToFile(0, URL, route, 0, 0);
	
	switch (hr) { // 잘 받았는지 확인
		case S_OK: // SUCCESS
			check = 1;
			break;
		case E_OUTOFMEMORY: // 버퍼 길이 문제 or 메모리 부족
			check = 2;
			break;
		case INET_E_DOWNLOAD_FAILURE:
			// 저장 경로가 없거나 권한 부족
			// callback 문제 <-- 이건 안써서 ㄱㅊ
			check = 3;
			break;
		case INET_E_RESOURCE_NOT_FOUND:
			// URL 경로가 문제가 있거나 존재하지 않음
			// 인터넷 문제
			// 그쪽에서 파일을 안줘영
			check = 4;
			break;
		default:
			// 에러 처리
			break;
	}
	return check;
}

/*
* URL 다운로드 원문?
int main() {
	LPCWSTR link = L"https://o365seowon-my.sharepoint.com/:u:/g/personal/jjssog_office_seowon_ac_kr/EYCBaYNFMdVKhOWDSkX_N08Bk_JmDxyWSYip0X8ms9SlPQ?e=mpmFKf&download=1";

	URLDownloadToFile(0, link, L"C:/Temp/test.zip", 0, 0);
	printf("Done");
	return 0;
}
*/
// https://o365seowon-my.sharepoint.com/:u:/g/personal/jjssog_office_seowon_ac_kr/EYCBaYNFMdVKhOWDSkX_N08Bk_JmDxyWSYip0X8ms9SlPQ?e=mpmFKf&download=1