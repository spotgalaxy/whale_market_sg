#define _CRT_SECURE_NO_WARNINGS

#include "Seller.h"

void seller(char* UserId) {

	int choice;

	while (1) {
		puts("====================================================================================");
		puts("1.发布商品 2.查看发布商品 3.修改商品信息 4.下架商品 5.查看历史订单 6.返回用户主界面");
		puts("====================================================================================\n\n");

		printf("选择您的操作 : ");

		scanf("%d", &choice);

		switch (choice) {
		case 1:
			publishGoods(UserId);

			Sleep(2000);
			system("cls");
			break;
		case 2:
			checkPublishedGoods();
			break;
		case 3:
			changeGoodsInfo();
			break;
		case 4:
			delistOwnGoods();
			break;
		case 5:
			checkHistoryOrder();
			break;
		case 6:
			puts("正在返回用户主界面，请稍后...");
			Sleep(2000);
			system("cls");
			return;
		default:
			puts("无效的选择，请重新输入。\n\n");
		}
	}
}

void publishGoods(char* UserId) {
	Goods newGood = { 0 };

	char buffer[150] = { 0 };

	int id = 0;

	Goods good = { 0 };

	time_t raw_time;
	time(&raw_time);

	struct tm* time_info = localtime(&raw_time);

	while (1) {

		printf("请输入商品名称: ");
		scanf("%s", newGood.name);

		printf("请输入商品价格: ");
		scanf("%lf", &newGood.price);

		printf("请输入商品描述: ");
		scanf("%s", newGood.description);
		puts("\n");

		puts("请确认商品信息无误.\n");

		puts("*********************\n");
		printf("商品名称: %s\n", newGood.name);
		printf("商品价格: %.2lf\n", newGood.price);
		printf("商品描述: %s\n", newGood.description);
		puts("\n*********************\n\n");

		char coe;
		printf("您确认要发布该商品吗(y/n): ");
		scanf(" %c", &coe);
		puts("");


		if ('y' == coe) {
			break;
		}
	}

	FILE* fp = fopen("goodsList.txt", "a+");

	if (!fp) {

		perror("open failed");
		return;
	}

	fgets(buffer, sizeof(buffer), fp);

	while (fgets(buffer, sizeof(buffer), fp)) {

		buffer[strcspn(buffer, "\n")] = '\0';

		sscanf(buffer, "%6[^,],%9[^,],%lf,%29[^,],%6[^,],%d-%d-%d,%6[^\n]",
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

		char mtid[7] = { 0 };
		memcpy(mtid, good.id + 1, 5);

		char* end;

		id = (int)strtol(mtid, &end, NULL);
	}

	sprintf(newGood.id, "M%05d", id + 1);

	memcpy(newGood.statu, "销售中", 7);

	newGood.data.year = time_info->tm_year + 1900;
	newGood.data.month = time_info->tm_mon + 1;
	newGood.data.day = time_info->tm_mday;

	memcpy(newGood.sellerId, UserId, 7);

	fprintf(fp, "%s,%s,%.2lf,%s,%s,%04d-%02d-%02d,%s\n",
		newGood.id,
		newGood.name,
		newGood.price,
		newGood.description,
		newGood.sellerId,
		newGood.data.year,
		newGood.data.month,
		newGood.data.day,
		newGood.statu
	);

	puts("发布中，请稍后...\n\n");
	Sleep(1500);

	puts("发布商品成功.");

	fclose(fp);

}

void checkPublishedGoods() {}
void changeGoodsInfo() {}
void delistOwnGoods() {}
void checkHistoryOrder() {}