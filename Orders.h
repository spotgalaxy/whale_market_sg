#pragma once
#include "Data.h"

typedef struct {
	char orderId[7];
	char goodsId[7];
	double sum;
	Data data;
	char sellerId[7];
	char buyerId[7];
} Orders;