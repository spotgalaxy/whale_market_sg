#define _CRT_SECURE_NO_WARNINGS

#include "PrivateMenu.h"

void privateMenu(char* UserId) {

	int choice;

	while (1) {
		puts("================================================");
		puts("1.注销登录 2.我是买家 3.我是卖家 4.个人信息管理");
		puts("================================================\n\n");

		printf("选择您的操作 : ");

		scanf("%d", &choice);

		switch (choice) {
		case 1:
			puts("正在返回主菜单，请稍后...");
			Sleep(2000);
			system("cls");
			return;
		case 2:
			system("cls");
			buyer();
			break;
		case 3:
			system("cls");
			seller(UserId);
			break;
		case 4:
			system("cls");
			privateInfocontrol();
			break;
		default:
			puts("无效的选择，请重新输入。\n\n");
		}

	}
}

void privateInfocontrol() {

}