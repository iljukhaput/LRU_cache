#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cache.h"
#include "double_linked_list.h"
#include "hash_table.h"

struct cache_t {
	int sz;
	struct hash_t *hash;
	struct list_t *lst;
};

struct cache_t *cache_create(int cache_size)
{
	struct cache_t *c = malloc(sizeof(struct cache_t));
	c->sz = cache_size;
	c->lst = list_create();
	c->hash = htable_create(cache_size);
	return c;
}

void cache_free(struct cache_t *c)
{
	list_free(&c->lst);
	htable_free(c->hash);
	free(c);
}

struct page_t *slow(int num)
{
	struct page_t *ppage = page_create(num);	
	return ppage;
}

bool cache_lookup_update(struct cache_t *c, int key, slow_get_page slow)
{
	struct list_node_t *pnode = htable_find(c->hash, key);
	if (pnode == NULL) {
		if (list_size(c->lst) == c->sz) {
			// assume that the key is the page number
			int backid = get_num(list_back(&(c->lst)));
			htable_erase(c->hash, backid);
			list_pop_back(c->lst);
		}
		struct page_t *page = slow(key);
		list_push_front(c->lst, page);
		htable_insert(c->hash, key, list_begin(&c->lst));
		return false;
	}
	list_move_upfront(c->lst, pnode);
	return true;
}

struct hash_t *get_hash(struct cache_t *c)
{
	return c->hash;
}

struct list_t *get_list(struct cache_t *c)
{
	return c->lst;
}

