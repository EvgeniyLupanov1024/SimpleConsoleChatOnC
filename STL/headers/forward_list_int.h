typedef struct forward_list_int forward_list_int;
typedef struct forward_list_int_element forward_list_int_element;

void Add (int number);
void Remove (int number);
void ForEach (void (* callback) (int number));

forward_list_int forward_list_int_init();
