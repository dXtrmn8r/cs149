//
// Created by Darren Peralta on 4/3/23.
//

#ifndef ITEM_TO_PURCHASE_H
#define ITEM_TO_PURCHASE_H

typedef struct ItemToPurchase {
    char itemName[100];
    int itemPrice;
    int itemQuantity;
} Item;

void MakeItemBlank(Item *itemToBlank);

void PrintItemCost(Item *itemToPrint);
#endif //ITEM_TO_PURCHASE_H
