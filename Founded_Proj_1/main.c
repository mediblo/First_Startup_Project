#include <stdio.h>
#include <conio.h>
#include <stdbool.h>

#include "source.h"
#include "word_define.h"

int main() {
	int select = 0;
	int page = 0;
	int uid = 0;
	bool flag = true;
	PNS pns;

	make_temp_folder();
	read_proj_file();
	if (UID_count != 0)read_user_file(); // NULL �б� ����
	if (SID_count != 0)read_seller_file(); // NULL �б� ����
	if (AID_count != 0)read_application_file(); // NULL �б� ����
	if (AID_D_count != 0)read_AID_D_file(); // NULL �б� ����
	if (RID_count != 0)read_review_file(); // NULL �б� ����

	do {
		
		if (flag) {
			pns = select_title();
			if (pns.id == -10) page = -10;
			else page = 0;
			flag = false;
			system("cls");
		}

		if (pns.type == 0) { // TYPE 0. �����
			switch (page) {
			case -1:
				flag = true;
				break;
			case 0:
				page = my_page(pns.id);
				break;
			case 1:
				page = library_page(pns.id);
				break;
			case 2:
				page = shop_page(pns.id);
				break;
			}
		}
		else if (pns.type == 1) { // TYPE 1. �Ǹ���
			switch (page) {
			case -1:
				flag = true;
				break;
			case 0:
				page = seller_page(pns.id);
				break;
			case 1:
				page = seller_library_page(pns.id);
				break;
			}
			
			if (page == -1) flag = true;
		}
		else if (pns.type == 2) {
			switch(page){
			case -1:
				flag = true;
				break;
				case 0:
					page = admin_page();
				break;
			}
		}
		system("cls");
		rewind(stdin); // Ȥ�� �� ���� �����սô�.
	} while (page != -10);
	draw_quit();
	
	free_all();

	return 0;
}