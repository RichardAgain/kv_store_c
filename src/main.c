
#include "kv.h"
#include <stdio.h>

int main() {
  kv_t *table = kv_init(16);

  kv_put(table, "hello", "yes i am");
  kv_put(table, "hello", "no, i am not");
  kv_put(table, "good morning", "ooh, ooh, ooh, ooh-ooh-ooh");

  kv_delete(table, "good morning");
  kv_put(table, "good morning", "ooh, ooh, ooh, ooh-ooh-ooh");

  for (int i = 0; i < table->capacity; i++) {
    if (table->entries[i].key) {
      printf("[%d] %s: %s\n", i, table->entries[i].key,
             table->entries[i].value);
    }
  }

  kv_free(table);
}
