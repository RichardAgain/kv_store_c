
#include "kv.h"
#include <stdio.h>

int main() {
  kv_t *table = kv_init(16);

  kv_put(table, "hello", "yes i am");
  kv_put(table, "hello", "no, i am not");
  //   kv_entry_t entry = table->entries[index];
  //   printf("[%d] %s: %s\n", index, entry.key, entry.value);

  // for (int i = 0; i < table->capacity; i++) {
  //   if (table->entries[i].key) {
  //     printf("[%d] %s: %s\n", i, table->entries[i].key,
  //            table->entries[i].value);
  //   }
  // }

  char *value = kv_get(table, "hello");
  printf("%s\n", value);
}
