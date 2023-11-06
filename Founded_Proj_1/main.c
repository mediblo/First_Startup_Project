#include <stdio.h>
#include <urlmon.h> // URLDOWNLOAD
#include <conio.h>

#include "source.h"
#include "word_define.h"

int main() {
	int select = 0;
	int page = 0;
	int uid = 0;
	bool flag = TRUE;
	PNS pns;

	read_proj_file();
	if (UID_count != 0)read_user_file();
	if (SID_count != 0)read_seller_file();
	do {
		
		if (flag) {
			pns = select_title();
			if (pns.id == -10) page = -10;
			else page = 0;
			flag = false;
			system("cls");
		}

		if (pns.type == 0) { // TYPE 0. 사용자
			switch (page) {
			case -1:
				flag = true;
				break;
			case 0:
				page = my_page(pns.id);
				break;
			case 1:
				break;
			case 2:
				break;
			}
		}
		else if (pns.type == 1) { // TYPE 1. 판매자
			page = seller_page(pns.id);
			if (page == -1) flag = true;
		}
		system("cls");
	} while (page != -10);
	draw_quit();

	return 0;
}