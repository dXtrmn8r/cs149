//
// Created by Darren Peralta on 4/3/23.
//
#include <stdio.h>
#include <string.h>

#include "ItemToPurchase.h"

/* Type your code here */
void MakeItemBlank(ItemToPurchase *itemToBlank) {
    strcpy(itemToBlank -> itemName, "none");
    itemToBlank -> itemPrice = 0;
    itemToBlank -> itemQuantity = 0;
}

void PrintItemCost(ItemToPurchase *itemToPrint) {
    int totalCost = (itemToPrint -> itemQuantity) * (itemToPrint -> itemPrice);
    printf("%s %d @ $%d = $%d\n",
           itemToPrint -> itemName,
           itemToPrint -> itemQuantity,
           itemToPrint -> itemPrice,
           totalCost);
}
