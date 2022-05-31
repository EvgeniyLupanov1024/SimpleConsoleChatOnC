#ifndef LIST_INT_H
#define LIST_INT_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct list_int list_int;
typedef struct list_int_node list_int_node;

struct list_int {
    int count;
    list_int_node *last_node;
};
struct list_int_node {
    int value;
    list_int_node *next_node;
    list_int_node *prev_node;
};

/**
 * Добавляет переданное значение в начало списка. 
 */
void AddFirst (list_int *list, int number);

/**
 * Удаляет первый узел с переданным значением из списка. 
 */
void Remove (list_int *list, int number);
bool RemoveCallback (list_int_node *node, void *arg);

/**
 * Выполняет переданный колбэк 
 * с переданными аргументами
 * над каждым элементом переданного списка.
 * 
 * Если колбэк вернёт false,
 * foreach завершит перебор.
 * 
 * Возращает итератор на момент выхода из функции.
 */
list_int_node * ForEach (list_int *list, bool (* callback) (list_int_node *node, void *arg), void *arg);

/**
 * Возращает пустой лист. 
 */
list_int list_int_init();

void Print(list_int *list);
bool PrintCallback (list_int_node *node, void *arg);

#endif
