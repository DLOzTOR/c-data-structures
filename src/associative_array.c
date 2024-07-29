#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  char *key;
  char *value;
} key_value;

typedef struct
{
  size_t capacity;
  size_t fullness;
  key_value **data;
} associative_array;

associative_array *create_associative_array(size_t size)
{
  associative_array *a_arr = malloc(sizeof(associative_array));
  a_arr->capacity = size;
  a_arr->fullness = 0;
  if (size == 0)
  {
    a_arr->data = NULL;
  }
  else
  {
    a_arr->data = malloc(sizeof(key_value *) * size);
  }
  return a_arr;
}

void associative_array_if_full_increase(associative_array *a_arr)
{
  if (a_arr->capacity == a_arr->fullness)
  {
    if (a_arr->capacity == 0)
    {
      a_arr->capacity = 1;
    }
    key_value **t_arr = malloc(sizeof(key_value *) * 2 * a_arr->capacity);
    for (size_t i = 0; i < a_arr->fullness; i++)
    {
      t_arr[i] = a_arr->data[i];
    }
    free(a_arr->data);
    a_arr->data = t_arr;
    a_arr->capacity = 2 * a_arr->capacity;
  }
}

int associative_array_is_key_exist(associative_array *a_arr, char *key)
{
  for (size_t i = 0; i < a_arr->fullness; i++)
  {
    if (!strcmp(a_arr->data[i]->key, key))
    {
      return 1;
    }
  }
  return 0;
}

int associative_array_add(associative_array *a_arr, char *key, char *value)
{
  if (associative_array_is_key_exist(a_arr, key))
  {
    return 0;
  }
  associative_array_if_full_increase(a_arr);
  key_value *data = malloc(sizeof(key_value));
  data->key = strdup(key);
  data->value = strdup(value);
  a_arr->data[a_arr->fullness] = data;
  a_arr->fullness++;
  return 1;
}

char *associative_array_get(associative_array *a_arr, char *key)
{
  for (size_t i = 0; i < a_arr->fullness; i++)
  {
    if (!strcmp(a_arr->data[i]->key, key))
    {
      return a_arr->data[i]->value;
    }
  }
  return NULL;
}

key_value *associative_array_get_by_index(associative_array *a_arr, size_t index)
{
  if (index < a_arr->fullness)
  {
    return a_arr->data[index];
  }
  return NULL;
}

void associative_array_remove(associative_array *a_arr, char *key)
{
  int find = 0, index;
  for (size_t i = 0; i < a_arr->fullness; i++)
  {
    if (!strcmp(a_arr->data[i]->key, key))
    {
      find = 1;
      index = i;
      break;
    }
  }
  if (find)
  {
    key_value *t;
    t = a_arr->data[index];
    for (size_t i = index + 1; i < a_arr->fullness; i++)
    {
      a_arr->data[i - 1] = a_arr->data[i];
    }
    free(t->key);
    free(t->value);
    free(t);
    a_arr->fullness--;
  }
}

void associative_array_free(associative_array *a_arr)
{
  if (a_arr == NULL)
  {
    return;
  }
  for (size_t i = 0; i < a_arr->fullness; i++)
  {
    free(a_arr->data[i]->key);
    free(a_arr->data[i]->value);
    free(a_arr->data[i]);
  }
  free(a_arr->data);
  free(a_arr);
}

void associative_array_print(associative_array *a_arr)
{
  size_t i = 0;
  key_value *t = associative_array_get_by_index(a_arr, i);
  while (t != NULL)
  {
    printf("key: %s; value: %s\n", t->key, t->value);
    i++;
    t = associative_array_get_by_index(a_arr, i);
  }
}

void associative_array_test()
{
  associative_array *t = create_associative_array(2);

  if (!associative_array_add(t, "test", "value"))
  {
    printf("Key already exists: test\n");
  }

  if (!associative_array_add(t, "test1", "value1"))
  {
    printf("Key already exists: test1\n");
  }

  associative_array_print(t);
  associative_array_remove(t, "test");

  char *value = associative_array_get(t, "test");
  if (value != NULL)
  {
    printf("test: %s\n", value);
  }
  else
  {
    printf("Key not found after removal: test\n");
  }

  value = associative_array_get(t, "test1");
  if (value != NULL)
  {
    printf("test1: %s\n", value);
  }
  else
  {
    printf("Key not found: test1\n");
  }

  associative_array_free(t);
}