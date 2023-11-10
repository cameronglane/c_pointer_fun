#include "pointer_functions.h"

void freeCustomerList(struct CustomerList* list) {
    struct CustomerNode* current = list->head;
    while (current != NULL) {
        struct CustomerNode* temp = current;
        current = current->next;

        free(temp); // Free the memory of the current node
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}