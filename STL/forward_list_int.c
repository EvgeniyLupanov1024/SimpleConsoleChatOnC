#include "headers/forward_list_int.h"

struct forward_list_int {
    int count;
    forward_list_int_element *lastElement;

    void (* add) (int number);
    void (* remove) (int number);
    void (* for_each) (void (* callback) (int number));
};

struct forward_list_int_element {
    int value;
    forward_list_int_element *prevElement;
};

void Add (int number) 
{

}

void Remove (int number) 
{
    
}

void ForEach (void (* callback) (int number)) 
{
    
}

forward_list_int forward_list_int_init()
{
    forward_list_int empty_list = {
        0, 
        NULL,

        Add,
        Remove,
        ForEach
    };

    return empty_list;
}
