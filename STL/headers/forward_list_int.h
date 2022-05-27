typedef struct forward_list_int forward_list_int;
typedef struct forward_list_int_element forward_list_int_element;

void Add (int number);
void Remove (int number);
void ForEach ();

forward_list_int forward_list_int_init();
void forward_list_int_delete(forward_list_int forward_list);
