#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct ContactNode_struct {
    /* Define ContactNode struct here. */
    char *contactName;
    char *contactPhoneNumber;
    struct ContactNode_struct *nextNodePtr;
} ContactNode;

/* Define the functions here. */
void InitializeContactNode(ContactNode *newContact, char *name, char *phoneNumber) {
    // newContact = (ContactNode*) malloc(sizeof(ContactNode));

    newContact->contactName = (char*) malloc(strlen(name) * sizeof(char));
    newContact->contactName = name;
    newContact->contactPhoneNumber = (char*) malloc(strlen(phoneNumber) * sizeof(char));
    newContact->contactPhoneNumber = phoneNumber;
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

void PrintContactNode(ContactNode c) {
    printf("Name: %s\n", c.contactName);
    printf("Phone number: %s\n", c.contactPhoneNumber);
}

int main(void) {
   /* Type your code here. */
   
   return 0;
}


