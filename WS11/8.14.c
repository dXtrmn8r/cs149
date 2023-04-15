#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define NUM_CONTACTS 3

size_t MAX_CHARS = 200;
size_t MAX_PHONE_CHARS = 12;

typedef struct ContactNode_struct {
    /* Define ContactNode struct here. */
    char *contactName;
    char *contactPhoneNumber;
    struct ContactNode_struct *nextNodePtr;
} ContactNode;

// static ContactNode *head = NULL;

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

void PrintContactNode(ContactNode *c) {
    printf("Name: %s\n", c->contactName);
    printf("Phone number: %s\n", c->contactPhoneNumber);
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

    ContactNode *temp;
    name = malloc(MAX_CHARS * sizeof(char));
    phone = malloc(MAX_PHONE_CHARS * sizeof(char));
    
    getdelim(&name, &MAX_CHARS, '\n', stdin);
    name[strlen(name) - 1] = '\0';
    getdelim(&phone, &MAX_PHONE_CHARS, '\n', stdin);
    phone[strlen(phone) - 1] = '\0';

    temp = (ContactNode *) malloc(sizeof(ContactNode));

    InitializeContactNode(temp, name, phone);

    PrintContactNode(temp);

    FreeContactNode(temp);

    free(name);
    free(phone);

    return 0;
}
