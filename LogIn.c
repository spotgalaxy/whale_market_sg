#define _CRT_SECURE_NO_WARNINGS

#include "LogIn.h"

const char* admin_name = "a";//"admin";
const char* admin_password = "0";//"1234567890";

void logIn() {

	char name[50] = { 0 };
	char buffer[150] = { 0 };
	char password[11] = { 0 };
	char UserId[10] = { 0 };

	Users user = { 0 };

	bool isFound = false;

SCM:
	printf("请输入您的用户名称 : ");

	scanf("%s", name);

	FILE* fp = fopen("userList.txt", "r");

	if (!fp) {

		perror("open failed");
		return;
	}

	while (fgets(buffer, sizeof(buffer), fp)) {

		buffer[strcspn(buffer, "\n")] = '\0';

		sscanf(buffer, "%6[^,],%9[^,],%19[^,],%11[^,],%24[^,],%lf",
			user.Uid,
			user.name,
			user.passwords,
			user.tel,
			user.add,
			&user.balance
		);

		if (strcmp(name, user.name) == 0) {
			isFound = true;
			memcpy(UserId, user.Uid, 7);
			break;
		}
	}

	if (isFound) {
		int cnt = 4;
	SC:
		printf("请输入密码: ");
		scanf("%s", password);
		cnt--;
		if (strcmp(password, user.passwords) == 0) {
			printf("\n\n***** 登录成功，欢迎使用 whale market. *****");

			Sleep(2000);
			system("cls");

			privateMenu(UserId);
		}
		else {
			if (cnt) {
				printf("密码错误，你还有 %d 次机会。\n\n", cnt);
				goto SC;
			}
			else {
				puts("次数用尽，即将返回主菜单。\n");

				Sleep(2000);
				system("cls");
			}

		}
	}
	else {
		printf("未识别的name，请检查后重新输入.\n\n");
		goto SCM;
	}
}

void adminLogIn() {

	char buffer[150] = { 0 };
	char password[11] = { 0 };

	printf("输入管理员姓名: ");
	scanf("%s", buffer);

	if (strcmp(buffer, admin_name) == 0) {

		printf("请输入密码: ");
		scanf("%s", password);

		if (strcmp(password, admin_password) == 0) {

			puts("\n\n**************** 登录成功! ****************");

			Sleep(2000);
			system("cls");

			manage();
		}
		else {

			puts("\n");
			puts("******登录失败，即将返回主菜单******");

			Sleep(2000);
			system("cls");
		}
	}
	else {

		puts("\n\n");
		puts("******登录失败，即将返回主菜单******");

		Sleep(2000);
		system("cls");
	}

}