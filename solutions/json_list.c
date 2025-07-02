#include "json_list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

JObject* parse_json(const char *filename) {
    json_t *root;
    json_error_t error;

    root = json_load_file(filename, 0, &error);
    if (!json_is_array(root)) {
        fprintf(stderr, "Error: root is not an array\n");
        return NULL;
    }

    JObject *head = NULL;
    for (size_t i = 0; i < json_array_size(root); i++) {
        json_t *obj = json_array_get(root, i);
        if (!json_is_object(obj)) continue;

        json_t *jname = json_object_get(obj, "name");
        json_t *jage = json_object_get(obj, "age");

        if (!json_is_string(jname) || !json_is_integer(jage)) continue;

        JObject *node = malloc(sizeof(JObject));
        if (!node) continue;

        node->name = strdup(json_string_value(jname));
        node->age = json_integer_value(jage);
        node->next = head;
        head = node;
    }

    json_decref(root);
    return head;
}

void print_list(JObject *head) {
    for (JObject *p = head; p; p = p->next) {
        printf("Name: %s, Age: %d\n", p->name, p->age);
    }
}

void free_list(JObject *head) {
    while (head) {
        JObject *next = head->next;
        free(head->name);
        free(head);
        head = next;
    }
}

