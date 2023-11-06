#include <stdio.h>
#include <conio.h>

#include "source.h"
#include "word_define.h"

// NOTHING	 - -1 / DOWN - 1 / UP - 2 / LEFT - 3 / RIGHT - 4
INT_kb_info INT_kb_for_page() {
	int new_select = 0;
	static int old_select = 0;
	int key[2] = { 0,0 };
	INT_kb_info kb_info = { 0,0 };
	key[0] = _getch();
	if (key[0] == K_ARROW) { // old_select이랑 같이 보낼 것
		kb_info.page_num = old_select;
		key[1] = _getch();
		switch (key[1]) {
			case K_DOWN:
				kb_info.key = 1;
				return kb_info;
			case K_UP:
				kb_info.key = 2;
				return kb_info;
			case K_LEFT:
				kb_info.key = 3;
				return kb_info;
			case K_RIGHT:
				kb_info.key = 4;
				return kb_info;
		}
	}
	else {
		switch (key[0]) {
			case 0:
				key[1] = _getch();
				new_select += key[1] - K_F1;
				if (new_select != old_select) {
					old_select = new_select;
					kb_info.page_num = old_select;
				}
				return kb_info;
			case 'w':
			case 'W':
				kb_info.key = 2;
				return kb_info;
			case 's':
			case 'S':
				kb_info.key = 1;
				return kb_info;
			case 'a':
			case 'A':
				kb_info.key = 3;
				return kb_info;
			case 'd':
			case 'D':
				kb_info.key = 4;
				return kb_info;
			default:
				kb_info.key = key[0];
				return kb_info;
		}
	}

}