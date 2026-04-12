#include "kv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hash(const char *value, size_t capacity) {
  unsigned int h = 2166136261u;
  while (*value) {
    h ^= (unsigned char)*value++;
    h *= 16777619u;
  }

  return (int)(h % capacity);
}

char *kv_get(kv_t *db, const char *key) {
  if (!db || !key) {
    return NULL;
  }

  int index = hash(key, db->capacity);

  for (int i = 0; i < db->capacity - 1; i++) {
    int real_idx = (index + i) % db->capacity;

    kv_entry_t *entry = &db->entries[real_idx];

    if (entry->key == NULL)
      return NULL;

    if (entry->key && entry->key != TOMBSTONE && strcmp(entry->key, key) == 0) {
      return entry->value;
    }
  }

  return NULL;
}

int kv_delete(kv_t *db, const char *key) {
  if (!db || !key) {
    return -1;
  }

  int index = hash(key, db->capacity);

  for (int i = 0; i < db->capacity - 1; i++) {
    int real_idx = (index + i) % db->capacity;

    kv_entry_t *entry = &db->entries[real_idx];

    if (entry->key == NULL) {
      return -1;
    }

    if (entry->key && entry->key != TOMBSTONE && strcmp(entry->key, key) == 0) {
      free(entry->key);
      free(entry->value);
      entry->key = TOMBSTONE;
      entry->value = NULL;

      db->count--;
      // return real_idx;
      return 0;
    }
  }

  return -1;
}

int kv_put(kv_t *db, const char *key, const char *value) {
  if (!db || !key || !value) {
    return -1;
  }

  int index = hash(key, db->capacity);

  for (int i = 0; i < db->capacity - 1; i++) {
    int real_idx = (index + i) % db->capacity;

    kv_entry_t *entry = &db->entries[real_idx];

    if (entry->key && entry->key != TOMBSTONE && strcmp(entry->key, key) == 0) {
      char *new_value = strdup(value);
      if (new_value == NULL) {
        return -1;
      }
      free(entry->value);
      entry->value = new_value;
      // return real_idx;
      return 0;
    }

    if (!entry->key || entry->key == TOMBSTONE) {
      char *new_value = strdup(value);
      char *new_key = strdup(key);
      if (!new_value || !new_key) {
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

void kv_free(kv_t *db) {
  // if (!db)
  //   return -1;

  for (int i = 0; i < db->capacity - 1; i++) {
    kv_entry_t *entry = &db->entries[i];

    if (entry->key && entry->key != TOMBSTONE) {
      free(entry->key);
      free(entry->value);
      entry->key = NULL;
      entry->value = NULL;
      db->count = 0;
    }
  }

  free(db->entries);
  free(db);

  // return 0;
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