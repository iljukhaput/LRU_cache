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


int get_hash_value(const struct hash_t *h, int key)
{
	int hash_value = key % h->len; // TODO: replace the hash function with a normal
	return hash_value;
}

struct hashmap_entry_t *get_entry(struct hashmap_node_t *pnode)
{
	return &pnode->entry;
}

struct hashmap_node_t *hmap_node_create()
{
	struct hashmap_node_t *pnode = malloc(sizeof(struct hashmap_node_t));
	return pnode;
}

struct hash_t *htable_create(int len)
{
	struct hash_t *h = malloc(sizeof(struct hash_t));
	if (h == NULL) {
		return NULL;
	}

	h->htab = calloc(len, sizeof(struct hashmap_node_t *));
	if (h->htab == NULL) {
		return NULL;
	}

	h->len = len;
	return h;
}

struct hashmap_node_t *hashmap_node_find (const struct hash_t *h, int key)
{
	int hash_value = get_hash_value(h, key);
	struct hashmap_node_t *tmp = h->htab[hash_value];
	while (tmp) {
		if (tmp->entry.key == key) {
			return tmp;
		}
		tmp = tmp->next;
	}
	return 0;
}

struct list_node_t *htable_find(const struct hash_t *h, int key)
{
	struct hashmap_node_t *find_node = hashmap_node_find(h, key);
	if (find_node != NULL) {
		return find_node->entry.node;
	}
	return 0;
}

void htable_insert(struct hash_t *h, int key, struct list_node_t *list_node)
{
	if (htable_find(h, key)) {
		printf("Non-unique key\n");
		return;
	}

	struct hashmap_node_t *new_node = malloc(sizeof(struct hashmap_node_t));
	new_node->next = NULL;
	new_node->entry.key = key;
	new_node->entry.node = list_node;

	int hash_value = get_hash_value(h, key);
	struct hashmap_node_t *tmp = h->htab[hash_value];
	if (tmp == NULL) {
		h->htab[hash_value] = new_node;
	} else {
		while (tmp->next) {
			tmp = tmp->next;
		}
		tmp->next = new_node;
	}
}

void htable_erase(struct hash_t *h, int key)
{
	int hash_value = get_hash_value(h, key);
	struct hashmap_node_t *tmp = h->htab[hash_value];
	if (tmp->entry.key == key) {
		h->htab[hash_value] = h->htab[hash_value]->next;
		free(tmp);
	} else {
		while (tmp->next != NULL) {
			if (tmp->next->entry.key == key) {
				break;
			}
			tmp = tmp->next;
		}
		struct hashmap_node_t *tmp_del = tmp->next;
		tmp->next = tmp_del->next;
		free(tmp_del);
	}
}

void htable_free(struct hash_t *h)
{
	struct hashmap_node_t *tmp;
	for (int i=0; i < h->len; i++) {
		while (h->htab[i] != 0) {
			tmp = h->htab[i];
			h->htab[i] = h->htab[i]->next;
			free(tmp);
		}
	}
	free(h->htab);
	h->htab = NULL;
	free(h);
}

//==============================================================================

int get_htable_len(struct hash_t *h)
{
	return h->len;
}

void print_htable_info(const struct hash_t *h)
{
	printf("\nhtable->len: %d\n", h->len);
	printf("htable->htab: %p\n", h->htab);
	int num;
	for (int i = 0; i < h->len; i++) {
		if (!h->htab[i]) {
			num = 0;
			printf("htable->htab[%d] = %d\n", i, num);
		} else {
			num = get_num_from_node(h->htab[i]->entry.node);
			printf("htable->htab[%d] = %d", i, num);
			struct hashmap_node_t *tmp = h->htab[i];
			while (tmp->next) {
				num = get_num_from_node(tmp->next->entry.node);
				printf(" -> %d", num);
				tmp = tmp->next;
			}
			printf("\n");
		}
	}
}

void print_hashmap_node_info(const struct hash_t *h, int key)
{
	int hash_value = get_hash_value(h, key);
	struct hashmap_node_t *tmp = h->htab[hash_value];
	while (tmp->next) {
		tmp = tmp->next;
	}
	int num = get_num_from_node(tmp->entry.node);
	printf("\nkey: %d\n", key);
	printf("hash value: %d\n", hash_value);
	printf("page_num: %d\n", num);

}

