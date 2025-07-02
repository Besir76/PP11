#include <stdlib.h>
#include "slist.h"

SNode* add_node(SNode *head, int value) {
    SNode *new_node = (SNode*) malloc(sizeof(SNode));
    if (!new_node) return head;
    new_node->value = value;
    new_node->next = head;
    return new_node;
}

int count_nodes(SNode *head) {
    int count = 0;
    for (SNode *p = head; p != NULL; p = p->next) {
        count++;
    }
    return count;
}

void free_list(SNode *head) {
    SNode *p = head;
    while (p != NULL) {
        SNode *tmp = p;
        p = p->next;
        free(tmp);
    }
}

