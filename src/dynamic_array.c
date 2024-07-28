#include <stdio.h>
typedef struct
{
  size_t capacity;
  size_t fullness;
  int *data;
} int_dynamic_array;

int_dynamic_array *create_int_dynamic_array(size_t size)
{
  int_dynamic_array *d_arr = malloc(sizeof(int_dynamic_array));
  d_arr->capacity = size;
  d_arr->fullness = 0;
  if (size == 0)
  {
    d_arr->data = NULL;
  }
  else
  {
    d_arr = malloc(sizeof(int) * size);
  }
  return d_arr;
}

void int_dynamic_array_add(int_dynamic_array *d_arr, int data)
{
  if (d_arr->capacity == d_arr->fullness)
  {
    int *t_arr = malloc(sizeof(int) * 2 * d_arr->capacity);
    for (int i = 0; i < d_arr->capacity; i++)
    {
      t_arr[i] = d_arr->data[i];
    }
    free(d_arr->data);
    d_arr->data = t_arr;
  }
  d_arr->data[d_arr->fullness] = data;
  d_arr->fullness++;
}

int int_dynamic_array_get(int_dynamic_array *d_arr, int index, int *status)
{
  if (index >= d_arr->fullness)
  {
    *status = 1;
    return 0;
  }
  *status = 0;
  return d_arr->data[index];
}

void int_dynamic_array_add_test()
{
  int_dynamic_array *int_d_arr = create_int_dynamic_array(0);
  for (int i = 0; i < 10; i++)
  {
    int_dynamic_array_add(int_d_arr, i);
  }
  int status;
  for (int i = 0; i < int_d_arr->fullness + 1; i++)
  {
    int t = int_dynamic_array_get(int_d_arr, i, &status);
    printf("%d, status: %d\n", t, status);
  }
}