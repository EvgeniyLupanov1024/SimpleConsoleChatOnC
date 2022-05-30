#include "headers/list_int.h"

struct list_int {
    int count;
    list_int_node *last_node;
};

struct list_int_node {
    int value;
    list_int_node *next_node;
    list_int_node *prev_node;
};

void AddFirst (list_int *list, int number) 
{
    list_int_node *adding_node = (list_int_node *) malloc(sizeof(list_int_node));

    adding_node->next_node = NULL;
    adding_node->prev_node = list->last_node;
    adding_node->value = number;

    if (list->last_node != NULL) {
        list->last_node->next_node = adding_node;
    }

    list->last_node = adding_node;
}

void Remove (list_int *list, int number) 
{
    ForEach(list, RemoveCallback, &number);
}

bool RemoveCallback (list_int_node *node, void *arg)
{
    int remotable_value = * (int *) arg;

    if (remotable_value != node->value) {
        return false;
    }

    if (node->next_node != NULL) {
        node->next_node->prev_node = node->prev_node;
    }
    if (node->prev_node != NULL) {
        node->prev_node->next_node = node->next_node;
    }

    free(node);
    return true;
}

void ForEach (list_int *list, bool (* callback) (list_int_node *node, void *arg), void *arg)
{
    list_int_node *iterator = list->last_node;

    while(iterator != NULL)
    {
        if (!callback(iterator, arg)) {
            break;
        }

        iterator = iterator->prev_node;
    }
}

list_int list_int_init()
{
    list_int empty_list = {
        0, 
        NULL,
    };

    return empty_list;
}
