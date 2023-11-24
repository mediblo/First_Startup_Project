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

	MultiByteToWideChar(CP_ACP, NULL, type, -1, w_type, 6); // char -> wchar_t Ȯ����
	MultiByteToWideChar(CP_ACP, NULL, name, -1, w_name, 21); // char -> wchar_t �̸�

	wchar_t route[100] = L"download/"; // ���� 9����
	wcscat(route, w_name); // �ִ� 21����
	wcscat(route, L"."); // 1����
	wcscat(route, w_type); // �ִ� 6����
	// ���� �ִ� ũ�� = 9 + 21 + 1 + 6 + 1 = 38����
	// ũ�� ���� ������ ������ �� �Ӹ� �νð� �ڵ带 ������ ��� �ۿ� ����.

	hr = URLDownloadToFile(0, URL, route, 0, 0);
	
	switch (hr) { // �� �޾Ҵ��� Ȯ��
		case S_OK: // SUCCESS
			check = 1;
			break;
		case E_OUTOFMEMORY: // ���� ���� ���� or �޸� ����
			check = 2;
			break;
		case INET_E_DOWNLOAD_FAILURE:
			// ���� ��ΰ� ���ų� ���� ����
			// callback ���� <-- �̰� �ȽἭ ����
			check = 3;
			break;
		case INET_E_RESOURCE_NOT_FOUND:
			// URL ��ΰ� ������ �ְų� �������� ����
			// ���ͳ� ����
			// ���ʿ��� ������ ���࿵
			check = 4;
			break;
		default:
			// ���� ó��
			break;
	}
	return check;
}

/*
* URL �ٿ�ε� ����?
int main() {
	LPCWSTR link = L"https://o365seowon-my.sharepoint.com/:u:/g/personal/jjssog_office_seowon_ac_kr/EYCBaYNFMdVKhOWDSkX_N08Bk_JmDxyWSYip0X8ms9SlPQ?e=mpmFKf&download=1";

	URLDownloadToFile(0, link, L"C:/Temp/test.zip", 0, 0);
	printf("Done");
	return 0;
}
*/
// https://o365seowon-my.sharepoint.com/:u:/g/personal/jjssog_office_seowon_ac_kr/EYCBaYNFMdVKhOWDSkX_N08Bk_JmDxyWSYip0X8ms9SlPQ?e=mpmFKf&download=1