#include <stdlib.h>

typedef struct {
  char *key;
  char *value;
} kv_entry_t;

typedef struct {
  kv_entry_t *entries;
  size_t capacity;
  size_t count;
} kv_t;

kv_t *kv_init(size_t capacity);
void kv_free(kv_t *table);
