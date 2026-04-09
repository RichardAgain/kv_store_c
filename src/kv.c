#include "kv.h"
#include <stdlib.h>

kv_table *kv_init(size_t capacity) {
  if (capacity == 0)
    return NULL;

  kv_table *table = malloc(sizeof(kv_table));

  if (table == NULL) {
    return NULL;
  }

  table->capacity = capacity;
  table->count = 0;

  table->entries = calloc(sizeof(kv_entry), capacity);
  if (table->entries == NULL) {
    free(table);
    return NULL;
  }

  return table;
}