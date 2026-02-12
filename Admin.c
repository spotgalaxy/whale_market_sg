#define _CRT_SECURE_NO_WARNINGS

#include "Admin.h"

void manage() {

	int choice;

	while (1) {

		puts("====================================================================================");
		puts("1.查看所有商品 2.搜索商品 3.查看所有订单 4.查看所有用户 5.删除用户 6.下架商品 7.注销");
		puts("====================================================================================\n");

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
		default:
			puts("无效的选择，请重新输入。\n\n");
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
			"%6[^,],%15[^,],%lf,%50[^,],%6[^,],%d-%d-%d,%6[^\n]",
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
			printf("%s\t %10s\t %10.2lf\t %10s\t %04d-%02d-%02d\t %10s\n",
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
			"%6[^,],%9[^,],%lf,%29[^,],%6[^,],%d-%d-%d,%6[^\n]",
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
			"%6[^,],%6[^,],%lf,%d-%d-%d,%6[^,],%6[^\n]",
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
			printf("%s %10s %10.2lf %04d-%02d-%02d %10s %10s\n",
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

		int ret = sscanf(users, "%6[^,],%9[^,],%19[^,],%11[^,],%24[^,],%lf",
			user.Uid,
			user.name,
			user.passwords,
			user.tel,
			user.add,
			&user.balance
		);

		if (ret == 6) {
			printf("%s %15s %15s %20s %10.2lf\n",
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