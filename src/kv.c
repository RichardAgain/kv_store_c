#include "kv.h"
#include <stdlib.h>
#include <string.h>

#define TOMBSTONE ((char *)0x1)

int hash(const char *value, size_t capacity) {
  unsigned int h = 2166136261u;
  while (*value) {
    h ^= (unsigned char)*value++;
    h *= 16777619u;
  }

  return (int)(h % capacity);
}

int kv_put(kv_t *db, const char *key, const char *value) {
  if (!db || !key || !value) {
    return -1;
  }

  int index = hash(key, db->capacity);

  for (int i = 0; i < db->capacity - 1; i++) {
    int real_idx = (index + i) % db->capacity;

    kv_entry_t *entry = &db->entries[real_idx];

    if (entry->key && strcmp(entry->key, key) == 0) {
      char *new_value = strdup(value);
      if (new_value == NULL) {
        free(new_value);
        return -1;
      }
      entry->value = new_value;
      // return real_idx;
      return 0;
    }

    if (entry->value == NULL) {
      char *new_value = strdup(value);
      char *new_key = strdup(key);
      if (new_value == NULL || new_key == NULL) {
        free(new_value);
        free(new_key);
        return -1;
      }
      entry->value = new_value;
      entry->key = new_key;
      db->count++;
      // return real_idx;
      return 0;
    }
  }

  return -2;
}

kv_t *kv_init(size_t capacity) {
  if (capacity == 0)
    return NULL;

  kv_t *table = malloc(sizeof(kv_t));

  if (table == NULL) {
    return NULL;
  }

  table->capacity = capacity;
  table->count = 0;

  table->entries = calloc(sizeof(kv_entry_t), capacity);
  if (table->entries == NULL) {
    free(table);
    return NULL;
  }

  return table;
}