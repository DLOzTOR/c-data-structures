#include <stdio.h>
typedef struct int_linked_list_node int_linked_list_node;
struct int_linked_list_node
{
  int_linked_list_node *next;
  int data;
};

typedef struct int_linked_list int_linked_list;
struct int_linked_list
{
  int_linked_list_node *first;
};

void int_linked_list_add(int_linked_list *list, int data)
{
  if (list->first != NULL)
  {
    int_linked_list_node *current_node = list->first;
    while (current_node->next != NULL)
    {

      current_node = current_node->next;
    }
    current_node->next = malloc(sizeof(int_linked_list_node));
    current_node->next->data = data;
    current_node->next->next = NULL;
  }
  else
  {
    list->first = malloc(sizeof(int_linked_list_node));
    list->first->data = data;
    list->first->next = NULL;
  }
}

void linked_list_test()
{
  int_linked_list int_list={0};
  int_linked_list_add(&int_list, 0);
  for (int i = 0; i < 10; i++)
  {
    int_linked_list_add(&int_list, i);
  }
  int_linked_list_node *current_node = int_list.first;
  while (current_node != NULL)
  {
    printf("%i\n", current_node->data);
    current_node = current_node->next;
  }
}