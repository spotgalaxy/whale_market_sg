#define _CRT_SECURE_NO_WARNINGS

#include "Register.h"

void registerIn() {

	char buffer[150] = { 0 };


	Users newUser = { 0 };
	Users user = { 0 };

	int id = 0;
	bool isFound = false;
	int isRepeated = 0;

	FILE* fp = fopen("userList.txt", "a+");

	if (!fp) {

		perror("open failed");
		return;
	}

SCN:
	printf("输入您的名字: ");
	scanf("%s", newUser.name);

	fgets(buffer, sizeof(buffer), fp);

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


		if (strcmp(newUser.name, user.name) == 0) {
			isFound = true;
			break;
		}

		char utid[7] = { 0 };
		memcpy(utid, user.Uid + 1, 5);

		char* end;

		id = (int)strtol(utid, &end, NULL);
	}
	if (isFound) {

		puts("重复的名字，请重新输入.\n");

		goto SCN;
	}
	else {

		printf("请输入您的密码: ");
		scanf("%s", newUser.passwords);


		printf("请输入您的联系电话: ");
		scanf("%s", newUser.tel);


		printf("请输入您的家庭住址: ");
		scanf("%s", newUser.add);


	}

	sprintf(newUser.Uid, "U%05d", id + 1);

	newUser.balance = 0.0;

	fprintf(fp, "%s,%s,%s,%s,%s,%.1lf\n",
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