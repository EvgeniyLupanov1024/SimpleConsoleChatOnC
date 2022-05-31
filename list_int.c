#include "list_int.h"

void AddFirst (list_int *list, int number) 
{
    list_int_node *adding_node = (list_int_node *) malloc(sizeof(list_int_node));

    adding_node->next_node = NULL;
    adding_node->prev_node = list->last_node;
    adding_node->value = number;

    if (list->last_node != NULL) {
        list->last_node->next_node = adding_node;
    }

    list->count += 1;
    list->last_node = adding_node;
}

void Remove (list_int *list, int number) 
{
    list_int_node *iterator_removable = ForEach(list, RemoveCallback, &number);

    if (iterator_removable == list->last_node) {
        list->last_node = iterator_removable->prev_node;
    }

    list->count -= 1;
    free(iterator_removable);
}

bool RemoveCallback (list_int_node *node, void *arg)
{
    int removable_value = * (int *) arg;

    if (removable_value != node->value) {
        return true;
    }

    if (node->next_node != NULL) {
        node->next_node->prev_node = node->prev_node;
    }
    if (node->prev_node != NULL) {
        node->prev_node->next_node = node->next_node;
    }

    return false;
}

list_int_node * ForEach (list_int *list, bool (* callback) (list_int_node *node, void *arg), void *arg)
{
    list_int_node *iterator = list->last_node;

    while(iterator != NULL)
    {
        if (!callback(iterator, arg)) {
            break;
        }

        iterator = iterator->prev_node;
    }

    return iterator;
}

list_int list_int_init()
{
    list_int empty_list = {
        0, 
        NULL,
    };

    return empty_list;
}

void Print(list_int *list)
{
    ForEach(list, PrintCallback, NULL);
}

bool PrintCallback (list_int_node *node, void *arg)
{
    printf("value:%d (%p | %p | %p)\n", node->value, node->prev_node, node, node->next_node);
    return true;
}
