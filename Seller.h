#pragma once
#include "header.h"
#include "Goods.h"
#include "Orders.h"
#include "Users.h"

void seller(char* UserId);
void publishGoods(char* UserId);
void checkPublishedGoods(char* UserId);
void changeGoodsInfo(char* UserId);
void delistOwnGoods();
void checkHistoryOrder();