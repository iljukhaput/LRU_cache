#include <stdio.h>
#include <stdlib.h>
#include "double_linked_list.h"
#include "hash_table.h"

struct hashmap_entry_t {
	int key;
	struct list_node_t *node;
};

struct hashmap_node_t {
	struct hashmap_node_t *next;
	struct hashmap_entry_t entry;
};

struct hash_t {
	struct hashmap_node_t **htab;
	int len; // number of items in hash table
};


int get_hash_value(struct hash_t *h, int key)
{
	int hash_value = key % h->len; // TODO: replace the hash function with a normal
	return hash_value;
}


struct hash_t *htable_create(int len)
{
	struct hash_t *h = malloc(sizeof(struct hash_t));
	h->htab = (struct hashmap_node_t **)malloc(sizeof(struct hashmap_node_t) * 
			len);
	h->len = len;
	for (int i = 0; i < len; i++) {
		h->htab[i] = 0;
	}
	return h;
}

struct list_node_t *htable_find(struct hash_t *h, int key)
{
	int hash_value = get_hash_value(h, key);
	struct hashmap_node_t *tmp = h->htab[hash_value];
	while (tmp) {
		if (tmp->entry.key == key) {
			return tmp->entry.node;
		}
		tmp = tmp->next;
	}
	return 0;
}

void htable_insert(struct hash_t *h, int key, struct list_node_t *list_node)
{
	if (!htable_find(h, key)) {
		printf("Non-unique key");
		return;
	}

	struct hashmap_node_t *new_node = malloc(sizeof(struct hashmap_node_t));
	new_node->next = NULL;
	new_node->entry.key = key;
	new_node->entry.node = list_node;

	int hash_value = get_hash_value(h, key);
	struct hashmap_node_t **hashmap_node = &h->htab[hash_value];
	while (*hashmap_node) {
		*hashmap_node = (*hashmap_node)->next;
	}
	*hashmap_node = new_node;
}

