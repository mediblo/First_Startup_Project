// ���� ó�� �Լ�
#include <stdio.h>
#include <Windows.h>

// 100���� - ���� �κ� ����
// 200���� - �����Ҵ� ���Ḯ��Ʈ ���� ����
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
		case 109:
			printf("AID_D.bin �б� ����");
			break;
		case 200:
		case 201:
		case 202:
			printf("�����Ҵ� Delete ����");
			break;
		case 210:
		case 211:
		case 212:
		case 213:
		case 214:
			printf("�����Ҵ� Update ����");
			break;
		case 220:
		case 221:
			printf("�����Ҵ� Change ����");
		default:
			printf("�ٸ� ������ ����");
	}
	if (100 <= code && code < 200) printf("\n������... �ٽ� �������ּ���.");
	else printf("\n������ ȣ�� �ʿ�");
	printf("\nError Code : %d", code);
	exit(1);
}