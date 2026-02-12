#define _CRT_SECURE_NO_WARNINGS

#include "header.h"
#include "LogIn.h"
#include "Register.h"



int main() {

	int choice;

	//主菜单
	while (1) {

		puts("=========================================");
		puts("1.用户登录 2.用户注册 3.管理员登录 4.退出");
		puts("=========================================\n\n");

		printf("选择您的操作 : ");

		scanf("%d", &choice);

		switch (choice) {

		case 1:
			logIn();
			break;
		case 2:
			registerIn();
			break;
		case 3:
			adminLogIn();
			break;
		case 4:
			puts("\n\n感谢您的使用，下次再见，拜拜！");
			Sleep(2000);
			exit(0);
		default:
			puts("无效的选择，请重新输入。\n\n");
		}
	}

	return 0;
}
