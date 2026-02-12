#pragma once
#include "Data.h"

typedef struct {
	char id[7];
	char name[10];
	double price;
	char description[30];
	char sellerId[7];
	Data data;
	char statu[7];
} Goods;