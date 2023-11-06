#include <urlmon.h>

#include "source.h"
#include "word_define.h"

bool check_url(LPCWSTR* URL) {
	URLDownloadToFile(0, URL, L"test.zip", 0, 0);
	return true;
}

/*
int main() {
	LPCWSTR link = L"https://o365seowon-my.sharepoint.com/:u:/g/personal/jjssog_office_seowon_ac_kr/ES18Bz_4tfZIqsZnNUf0ahMBdEDGUbCDiGsA0O6caGSPTw?e=3DtJrx&download=1";

	URLDownloadToFile(0, link, L"C:/Temp/test.zip", 0, 0);
	printf("Done");
	return 0;
}
*/