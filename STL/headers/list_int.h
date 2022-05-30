typedef struct list_int list_int;
typedef struct list_int_node list_int_node;

void AddFirst (list_int *forward_list, int number);
void Remove (list_int *forward_list, int number);
void ForEach (list_int *list, bool (* callback) (list_int_node *node, void *arg), void *arg);

bool RemoveCallback (list_int_node *node, void *arg);

list_int forward_list_int_init();
