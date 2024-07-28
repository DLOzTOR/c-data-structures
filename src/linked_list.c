#include <stdio.h>
#include <stdlib.h>

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

int_linked_list_node *create_int_linked_list_node(int data)
{
  int_linked_list_node *t = malloc(sizeof(int_linked_list_node));
  t->data = data;
  t->next = NULL;
  return t;
}

int_linked_list_node *int_linked_list_get_at(int_linked_list *list, size_t position)
{
  int_linked_list_node *current_node = list->first;
  if (position == 0)
  {
    return list->first;
  }
  else
  {
    size_t current_none_index = 0;
    while (current_node->next != NULL && current_none_index < position)
    {
      current_none_index++;
      current_node = current_node->next;
    }
    if (current_node->next == NULL)
    {
      return NULL;
    }
    else
    {
      return current_node;
    }
  }
}

void int_linked_list_add(int_linked_list *list, int data)
{
  if (list->first != NULL)
  {
    int_linked_list_node *current_node = list->first;
    while (current_node->next != NULL)
    {

      current_node = current_node->next;
    }
    current_node->next = create_int_linked_list_node(data);
    current_node->next->next = NULL;
  }
  else
  {
    list->first = malloc(sizeof(int_linked_list_node));
    list->first->data = data;
    list->first->next = NULL;
  }
}

int int_linked_list_add_at(int_linked_list *list, size_t position, int data) // -1 if can't add
{
  size_t current_none_index = 0;
  int_linked_list_node *current_node = list->first;
  if (position == 0)
  {
    int_linked_list_node *t_node = list->first;
    list->first = create_int_linked_list_node(data);
    list->first->next = t_node;
    return 0;
  }
  else if (list->first == NULL)
  {
    return -1;
  }
  else
  {
    while (current_node->next != NULL && current_none_index < position)
    {
      current_none_index++;
      current_node = current_node->next;
    }
    if (current_node->next == NULL)
    {
      return -1;
    }
    else
    {
      int_linked_list_node *t_node = current_node->next;
      current_node->next = create_int_linked_list_node(data);
      current_node->next->next = t_node;
      return 0;
    }
  }
}

void int_linked_list_remove_last(int_linked_list *list, int isFree)
{
  if (list->first == NULL)
  {
    return;
  }
  else if (list->first->next == NULL)
  {
    if (isFree)
      free(list->first);
    list->first = NULL;
  }
  else
  {
    int_linked_list_node *current_node = list->first;
    while (current_node->next->next != NULL)
    {
      current_node = current_node->next;
    }
    if (isFree)
      free(current_node->next);
    current_node->next = NULL;
  }
}

int int_linked_list_remove_at(int_linked_list *list, size_t position, int freeNode) // -1 if can't add
{
  int_linked_list_node *current_node = list->first;
  if (list->first == NULL)
  {
    return -1;
  }
  else if (position == 0)
  {
    int_linked_list_node *t_node = list->first;
    list->first = list->first->next;
    if (freeNode)
      free(t_node);
    return 0;
  }
  else
  {
    size_t current_none_index = 1;
    while (current_node->next != NULL && current_none_index < position)
    {
      current_none_index++;
      current_node = current_node->next;
    }
    if (current_node->next == NULL)
    {
      return -1;
    }
    else
    {
      int_linked_list_node *t_node = current_node->next;
      current_node->next = current_node->next->next;
      if (freeNode)
        free(t_node);
      return 0;
    }
  }
}

int int_linked_list_cout(int_linked_list *list)
{
  int_linked_list_node *current_node = list->first;
  int counter = 0;
  while (current_node != NULL)
  {
    counter++;
    current_node = current_node->next;
  }
  return counter;
}

void int_linked_list_sort(int_linked_list *list)
{
  if (list->first == NULL)
  {
    return;
  }
  if (list->first->next == NULL)
  {
    return;
  }
  int is_sorted = 0;
  int_linked_list_node *curren_node = list->first, *prev = NULL;
  while (is_sorted == 0)
  {
    is_sorted = 1;
    curren_node = list->first;
    prev = list->first;
    while (curren_node->next != NULL)
    {
      if (curren_node->data > curren_node->next->data)
      {
        is_sorted = 0;
        if (curren_node == list->first)
        {
          list->first = curren_node->next;
          curren_node->next = curren_node->next->next;
          list->first->next = curren_node;
          curren_node = list->first->next;
          break;
        }
        else
        {
          prev->next = curren_node->next;
          curren_node->next = curren_node->next->next;
          prev->next->next = curren_node;
          curren_node = prev->next->next;
          break;
        }
      }
      else
      {
        prev = curren_node;
        curren_node = curren_node->next;
      }
    }
  }
}

void int_linked_list_print(int_linked_list *list)
{
  int_linked_list_node *current_node = list->first;
  while (current_node != NULL)
  {
    printf("%i\n", current_node->data);
    current_node = current_node->next;
  }
}

void int_linked_list_free(int_linked_list *list)
{
  int_linked_list_node *current_node = list->first, *t;
  while (current_node != NULL)
  {
    t = current_node->next;
    free(current_node);
    current_node = t;
  }
}

void linked_list_test()
{
  int_linked_list int_list = {0};
  for (int i = 10; i > 0; i--)
  {
    int_linked_list_add(&int_list, i);
  }
  // int_linked_list_get_at(&int_list, 4)->data = -4;
  // printf("4 element is: %i.\n", int_linked_list_get_at(&int_list, 4)->data);
  // int_linked_list_add_at(&int_list, 0, -1);
  int_linked_list_print(&int_list);
  // int_linked_list_add_at(&int_list, 2, -100);
  // printf("list nodes count: %i.\n", int_linked_list_cout(&int_list));
  // int_linked_list_remove_last(&int_list, 1);
  // int_linked_list_remove_at(&int_list, 0, 1);
  // int_linked_list_remove_at(&int_list, 4, 1);
  // printf("list nodes count: %i.\n", int_linked_list_cout(&int_list));
  // int_linked_list_print(&int_list);
  int_linked_list_sort(&int_list);
  printf("sorted\n");
  int_linked_list_print(&int_list);
  int_linked_list_free(&int_list);
}