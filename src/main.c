
#include "kv.h"
#include <stdio.h>

int main() {
  kv_t *table = kv_init(16);

  int index1 = kv_put(table, "hello", "yes i am");
  int index2 = kv_put(table, "hello", "no, i am not");
  int index3 = kv_put(table, "good morning", "ooh, ooh, ooh, ooh-ooh-ooh");
  //   kv_entry_t entry = table->entries[index];
  //   printf("[%d] %s: %s\n", index, entry.key, entry.value);

  // for (int i = 0; i < table->capacity; i++) {
  //   if (table->entries[i].key) {
  //     printf("[%d] %s: %s\n", i, table->entries[i].key,
  //            table->entries[i].value);
  //   }
  // }

  kv_delete(table, "good morning");

  printf("[%d]: %s\n", index1, table->entries[index1].value);
  printf("[%d]: %s\n", index3, table->entries[index3].value);
}
