#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdbool.h>

typedef struct {
	int year;
	int month;
	int day;
} Data;

typedef struct {
	char id[7];
	char name[10];
	float price;
	char description[30];
	char sellerId[7];
	Data data;
	char statu[7];
} Goods;

typedef struct {
	char orderId[7];
	char goodsId[7];
	float sum;
	Data data;
	char sellerId[7];
	char buyerId[7];
} Orders;

typedef struct {
	char Uid[7];
	char name[10];
	char passwords[20];
	char tel[12];
	char add[25];
	float balance;
} Users;



const char* admin_name = "a";//"admin";
const char* admin_password = "0";//"1234567890";

void logIn();
void registerIn();
void adminLogIn();
void manage();
void checkAllGoods();
void searchGoods();
void checkAllOrder();
void checkAllUser();
void delUser();
void delistGoods();


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
			Sleep(1500);
			exit(0);
		}
	}


	return 0;
}


void logIn() {

	char name[50] = { 0 };
	char buffer[50] = { 0 };
	char password[11] = { 0 };

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

		sscanf(buffer, "%6[^,],%9[^,],%19[^,],%11[^,],%24[^,],%f",
			user.Uid,
			user.name,
			user.passwords,
			user.tel,
			user.add,
			&user.balance
		);

		if (strcmp(name, user.name) == 0) {
			isFound = true;
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
			printf("登录成功，欢迎使用 whale market.\n\n");
			
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

void registerIn() {

	char buffer[50] = { 0 };
	
	Users newUser = { 0 };
	Users user = { 0 };

	int id = 0;

	int isRepeated = 0;

	FILE* fp = fopen("userList.txt", "a+");

	if (!fp) {

		perror("open failed");
		return;
	}

	printf("输入您的名字: ");
	scanf("%s", newUser.name);


	while (fgets(buffer, sizeof(buffer), fp)) {


		if (!strcmp(buffer, newUser.name)) {

			isRepeated = 1;
			break;
		}
	}
	
	while (fgets(buffer, sizeof(buffer), fp)) {

		buffer[strcspn(buffer, "\n")] = '\0';

		sscanf(buffer, "%6[^,],%9[^,],%19[^,],%11[^,],%24[^,],%f",
			user.Uid,
			user.name,
			user.passwords,
			user.tel,
			user.add,
			&user.balance
		);
	}
	if (isRepeated) {

		puts("重复的名字，请重新输入.");

		printf("输入您的名字: ");
		scanf("%s", newUser.name);
	}
	else {

		printf("请输入您的密码: ");
		scanf("%s", newUser.passwords);
		puts("");
		
		printf("请输入您的联系电话: ");
		scanf("%s", newUser.tel);
		puts("");

		printf("请输入您的家庭住址: ");
		scanf("%s", newUser.add);

			char* end;

			id = (int)strtol(user.Uid, &end, 10);
		}

		sprintf(newUser.name, "U%05d", id+1);

		newUser.balance = 0.0f;

		fprintf(fp, "%s,%s,%s,%s,%s,%.1f\n",
			newUser.Uid,
			newUser.name,
			newUser.passwords,
			newUser.tel,
			newUser.add,
			newUser.balance
		);

		printf("注册成功！您的用户ID是: %s\n", newUser.Uid);
	
	fclose(fp);
}

void adminLogIn() {

	char buffer[50] = { 0 };
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
	}
	else {

		puts("\n\n");
		puts("******登录失败，即将返回主菜单******");

		Sleep(5000);
	}

}

void manage() {

	puts("====================================================================================");
	puts("1.查看所有商品 2.搜索商品 3.查看所有订单 4.查看所有用户 5.删除用户 6.下架商品 7.注销");
	puts("====================================================================================\n");

	int choice;

	while (1) {

		printf("选择您的操作 : ");

		scanf("%d", &choice);

		switch (choice) {

		case 1:
			checkAllGoods();
			break;
		case 2:
			searchGoods();
			break;
		case 3:
			checkAllOrder();
			break;
		case 4:
			checkAllUser();
			break;
		case 5:
			delUser();
			break;
		case 6:
			delistGoods();
			break;
		case 7:
			puts("正在返回主菜单...");
			Sleep(1500);
			system("cls");
			return;
		}
	}
}

void checkAllGoods() {

	char goods[256] = { 0 };

	Goods good = { 0 };

	puts("\n\n");

	FILE* fp = fopen("goodsList.txt", "r");

	if (!fp) {

		perror("open failed");
		return;
	}

	puts("********************************************************************************\n");
	
	fgets(goods, sizeof(goods), fp);
	fputs(goods, stdout);

	while (fgets(goods, sizeof(goods), fp)) {
		// 移除 fgets 可能读入的换行符（可选，但推荐）
		goods[strcspn(goods, "\n")] = '\0';

		int ret = sscanf(goods,
			"%6[^,],%9[^,],%f,%29[^,],%6[^,],%d-%d-%d,%6[^\n]",
			good.id,
			good.name,
			&good.price,
			good.description,
			good.sellerId,
			&good.data.year,
			&good.data.month,
			&good.data.day,
			good.statu
		);

		if (ret == 9) {
			// 成功解析
			printf("%s\t %s\t %.1f\t %s\t %04d-%02d-%02d\t %s\n",
				good.id,
				good.name,
				good.price,
				good.sellerId,
				good.data.year,
				good.data.month,
				good.data.day,
				good.statu
			);
		}
		else {
			// 解析失败：打印错误信息（调试用）
			fprintf(stderr, "警告：无法解析该行（匹配 %d 项）: %s\n", ret, goods);
		}
	}

	fclose(fp);
	puts("\n********************************************************************************\n\n\n");
}

void searchGoods() {

	char shopName[10] = { 0 };

	char goods[256] = { 0 };
	char title[50] = { 0 };

	Goods good = { 0 };

	int is_found = 0;
	
	printf("输入您要搜索的商品名称: ");
	scanf("%9s", shopName);

	FILE* fp = fopen("goodsList.txt", "r");

	if (!fp) {

		perror("open failed");
		return;
	}

	fgets(title, sizeof(title), fp);

	while (fgets(goods, sizeof(goods), fp)) {

		sscanf(goods,
			"%6[^,],%9[^,],%f,%29[^,],%6[^,],%d-%d-%d,%6[^\n]",
			good.id,
			good.name,
			&good.price,
			good.description,
			good.sellerId,
			&good.data.year,
			&good.data.month,
			&good.data.day,
			good.statu
		);

		if (strstr(good.name, shopName) != NULL) {
			
			is_found = 1;
			break;
		}
	}

	if (is_found) {

		puts("********************************************************************************\n");
		fputs(title, stdout);
		printf("%-6s %-9s %.1f %-6s %04d-%02d-%02d %-6s\n",
			good.id,
			good.name,
			good.price,
			good.sellerId,
			good.data.year,
			good.data.month,
			good.data.day,
			good.statu
		);
		puts("\n********************************************************************************\n\n\n");
	}
	else {

		puts("\n********************************************************************************\n");
		puts("没有找到您想搜索的商品，即将返回搜索页面...");
		puts("\n********************************************************************************\n\n\n");

		Sleep(2000);
		system("cls");

		puts("====================================================================================");
		puts("1.查看所有商品 2.搜索商品 3.查看所有订单 4.查看所有用户 5.删除用户 6.下架商品 7.注销");
		puts("====================================================================================\n");

		return;
	}

	fclose(fp);
}

void checkAllOrder() {

	char orders[256] = { 0 };

	Orders order = { 0 };

	puts("\n\n");

	FILE* fp = fopen("orders.txt", "r");

	if (!fp) {

		perror("open failed");
		return;
	}

	puts("********************************************************************************\n");

	fgets(orders, sizeof(orders), fp);
	fputs(orders, stdout);

	while (fgets(orders, sizeof(orders), fp)) {

		orders[strcspn(orders, "\n")] = '\0';

		int ret = sscanf(orders,
			"%6[^,],%6[^,],%f,%d-%d-%d,%6[^,],%6[^\n]",
			order.orderId,
			order.goodsId,
			&order.sum,
			&order.data.year,
			&order.data.month,
			&order.data.day,
			order.sellerId,
			order.buyerId
		);

		if (ret == 8) {
			printf("%-6s %-6s %.1f %04d-%02d-%02d %-6s %-6s\n",
				order.orderId,
				order.goodsId,
				order.sum,
				order.data.year,
				order.data.month,
				order.data.day,
				order.sellerId,
				order.buyerId
			);
		}
		else {
			fprintf(stderr, "警告：无法解析该行（匹配 %d 项）: %s\n", ret, orders);
		}
	}

	fclose(fp);
	puts("\n********************************************************************************\n\n\n");
}

void checkAllUser() {

	char users[256] = { 0 };

	Users user = { 0 };

	puts("\n\n");

	FILE* fp = fopen("userList.txt", "r");

	if (!fp) {

		perror("open failed");
		return;
	}

	puts("********************************************************************************\n");


	fgets(users, sizeof(users), fp);
	fputs(users, stdout);


	while (fgets(users, sizeof(users), fp)) {

		users[strcspn(users, "\n")] = '\0';

		int ret = sscanf(users, "%6[^,],%9[^,],%19[^,],%11[^,],%24[^,],%f",
			user.Uid,
			user.name,
			user.passwords,
			user.tel,
			user.add,
			&user.balance
		);

		if (ret == 6) {
			printf("%-6s %-9s %-11s %-24s %.1f\n",
				user.Uid,
				user.name,
				user.tel,
				user.add,
				user.balance
			);
		}
		else {
			fprintf(stderr, "警告：无法解析该行（匹配 %d 项）: %s\n", ret, users);
		}
	}

	fclose(fp);
	puts("\n********************************************************************************\n\n\n");

}

void delUser() {


}

void delistGoods() {

}


