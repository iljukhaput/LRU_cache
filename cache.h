#ifndef _CACHE_
#define _CACHE_

#include <stdbool.h>
#include "hash_table.h"
#include "double_linked_list.h"

struct cache_t;

struct cache_t *cache_create(int cache_size);
void cache_free(struct cache_t *c);

typedef struct page_t *(*slow_get_page)(int page_num);
bool cache_lookup_update(struct cache_t *c, int key, slow_get_page slow);

struct page_t *slow(int num);
struct hash_t *get_hash(struct cache_t *c);
struct list_t *get_list(struct cache_t *c);

#endif // _CACHE_
