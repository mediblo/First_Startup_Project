// ���� ó�� �Լ�
#include <stdio.h>
#include <Windows.h>

// 100���� - ���� �κ� ����

void error(int code) {
	free_all();
	system("cls");
	switch (code) {
		case 2:
			printf("���� ���� ����");
			break;
		case 3:
			printf("select_title : ����ġ ���� ����");
		case 5:
			printf("get_UID : UID�� ����");
			break;
		case 6:
			printf("get_SID : SID�� ����");
			break;
		case 7:
			printf("popup_Explantion : �������� ����");
			break;
		case 100:
			printf("user.bin ���� or data���� ���� ����");
			break;
		case 101:
			printf("user.bin �б� ����");
			break;
		case 102:
			printf("proj.bin ���� or data���� ���� ����");
			break;
		case 103:
			printf("proj.bin �б� ����");
			break;
		case 104:
			printf("seller.bin ���� or data���� ���� ����");
			break;
		case 105:
			printf("seller.bin �б� ����");
			break;
		case 106:
			printf("application.bin ���� or data���� ���� ����");
			break;
		case 107:
			printf("application.bin �б� ����");
			break;
		case 108:
			printf("���� ���� ����");
			break;
		default:
			printf("�ٸ� ������ ����");
	}
	if (code >= 100) printf("\n������... �ٽ� �������ּ���.");
	printf("\nError Code : %d", code);
	exit(1);
}