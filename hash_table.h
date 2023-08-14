#ifndef _HASH_TABLE_
#define _HASH_TABLE_

#include "double_linked_list.h"

struct hashmap_entry_t;
struct hashmap_node_t;
struct hash_t;

struct hash_t *htable_create(int len);
struct list_node_t *htable_find(const struct hash_t *h, int key);
void htable_insert(struct hash_t *h, int key, struct list_node_t *list_node);
void htable_erase(struct hash_t *h, int key);
void htable_free(struct hash_t *h);

int get_hash_value(const struct hash_t *h, int key);
int get_hash_table_len(struct hash_t *h);
void print_htable_info(const struct hash_t *h);
void print_hashmap_node_info(const struct hash_t *h, int key);

#endif // _HASH_TABLE_
