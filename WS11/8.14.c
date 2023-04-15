#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define NUM_CONTACTS 3

size_t MAX_CHARS = 200;
size_t MAX_PHONE_CHARS = 12;

typedef struct ContactNode_struct ContactNode;

struct ContactNode_struct {
    /* Define ContactNode struct here. */
    char *contactName;
    char *contactPhoneNumber;
    ContactNode *nextNodePtr;
};

static ContactNode *head = NULL;

/* Define the functions here. */
void InitializeContactNode(ContactNode *newContact, char *name, char *phoneNumber) {
    //vnewContact->contactName = (char*) malloc(strlen(name) * sizeof(char));
    newContact->contactName = strdup(name);

    //vnewContact->contactPhoneNumber = (char*) malloc(strlen(phoneNumber) * sizeof(char));
    //vstrcpy(newContact->contactPhoneNumber, phoneNumber);
    newContact->contactPhoneNumber = strdup(phoneNumber);

    newContact->nextNodePtr = NULL;
}

char* GetName(ContactNode *c) {
    return c->contactName;
}

char* GetPhoneNumber(ContactNode *c) {
    return c->contactPhoneNumber;
}

void InsertAfter(ContactNode *this, ContactNode *after) {
    this->nextNodePtr = after;
}

ContactNode* GetNext(ContactNode *c) {
    return c->nextNodePtr;
}

void PrintContactNode(ContactNode *c, unsigned int i) {
    printf("Person %d: %s, %s\n", i, GetName(c), GetPhoneNumber(c));
}

void PrintPhonebook(ContactNode *c) {
    printf("Name: %s\n", GetName(c));
    printf("Phone number: %s\n\n", GetPhoneNumber(c));
    if (c-> nextNodePtr != NULL)
        PrintPhonebook(c->nextNodePtr);
}

void FreeContactNode(ContactNode *c) {
    if ((c->nextNodePtr) != NULL)
        FreeContactNode(c->nextNodePtr);

    free(c->contactPhoneNumber);
    free(c->contactName);
    free(c);
}

int main(void) {
    /* Type your code here. */
    char *name, *phone;

    ContactNode *temp[3];
    name = malloc(MAX_CHARS * sizeof(char));
    phone = malloc(MAX_PHONE_CHARS * sizeof(char));

    for (int i = 0; i < NUM_CONTACTS; i++) {

        getdelim(&name, &MAX_CHARS, '\n', stdin);
        name[strlen(name) - 1] = '\0';
        getdelim(&phone, &MAX_PHONE_CHARS, '\n', stdin);
        phone[strlen(phone) - 1] = '\0';

        temp[i] = (ContactNode *) malloc(sizeof(ContactNode));

        InitializeContactNode(temp[i], name, phone);

        PrintContactNode(temp[i], i+1);
        if (i == 0) head = temp[i];
        else InsertAfter(temp[i - 1], temp[i]);
    }

    printf("\n");
    printf("CONTACT LIST\n");
    PrintPhonebook(head);


    FreeContactNode(temp[0]);

//    FreeContactNode(head);

    free(name);
    free(phone);

    return 0;
}
