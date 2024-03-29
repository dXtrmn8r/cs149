#include <stdio.h>
#include <string.h>

#include "ItemToPurchase.h"

int numItems;
int total;

void inputItem(ItemToPurchase* i) {
    numItems++;
    printf("Item %d\n", numItems);
    printf("Enter the item name: ");
    scanf("%s", i->itemName);

    printf("Enter the item price: ");
    scanf("%d", &i->itemPrice);

    printf("Enter the item quantity: ");
    scanf("%d", &i->itemQuantity);

    total += (i->itemPrice * i->itemQuantity);
}

int main(void) {

    /* Type your code here */
    ItemToPurchase i1;
    inputItem(&i1);

    char c = getchar();
    while(c != '\n' && c != EOF) {
        c = getchar();
    }
    printf("\n");

    ItemToPurchase i2;
    inputItem(&i2);

    printf("\n");
    printf("TOTAL COST\n");
    PrintItemCost(&i1);
    PrintItemCost(&i2);


    printf("Total: $%d\n", total);

    return 0;
}
