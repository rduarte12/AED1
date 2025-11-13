#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct linked_list LinkedList;
typedef struct node Node;

LinkedList *create_linked_list(void);
int insert_node(LinkedList *list, int pos, int value);
int remove_node(LinkedList *list, int pos, int *value);
int get_node(const LinkedList *list, int pos, int *value);
int is_empty_list(const LinkedList *list);
int size_list(const LinkedList *list);
void free_linked_list(LinkedList **list);

#endif // LINKEDLIST_H