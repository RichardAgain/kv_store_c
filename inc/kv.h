#include <stdlib.h>

typedef struct {
  char *key;
  char *value;
} kv_entry;

typedef struct {
  size_t capacity;
  size_t count;
  kv_entry *entries;
} kv_table;

kv_table *kv_init(size_t capacity);
void kv_free(kv_table *table);
