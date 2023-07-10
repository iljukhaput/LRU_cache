#include <stdlib.h>
#include "double_linked_list.h"


struct page_t {
	int num;
};

struct list_node_t {
	struct page_t *data;
	struct list_node_t *next;
	struct list_node_t *prev;
};

struct list_t {
	struct list_node_t *top;
	struct list_node_t *back;
};


struct list_node_t *node_create(struct page_t *p)
{
	struct list_node_t *p_list = malloc(sizeof(struct list_node_t));
	p_list->data = p;
	p_list->next = NULL;
	p_list->prev = NULL;
	return p_list;
}

void node_free(struct list_node_t *node_t)
{
	free(node_t);
	node_t = NULL;
}

struct list_t *list_create()
{
	struct list_t *p_list_t = malloc(sizeof(struct list_t));
	p_list_t->top = NULL;
	p_list_t->back = NULL;
	return p_list_t;
 
}

int list_size(const struct list_t *lst)
{
	if (lst->top == NULL) {
		return 0;
	}

	int size = 1;
	struct list_node_t *tmp = lst->top;
	while (tmp->next != NULL) {
		tmp = tmp->next;
		size++;
	}
	return size;
}

struct page_t *list_back_(struct list_t *lst)
{
	return lst->back->data;
}

void list_pop_back(struct list_t *lst)
{
	lst->back->prev->next = NULL;
	lst->back = lst->back->prev;
}

void list_push_front_(struct list_t *lst, struct page_t *q)
{
	struct list_node_t *new_node = malloc(sizeof(struct list_node_t));
	new_node->data = q;
	new_node->next = lst->top;
	new_node->prev = NULL;
	lst->top = new_node;
}

void list_move_upfront_(struct list_t *lst, struct list_node_t *p)
{
	p->prev->next = p->next;
	p->next->prev = p->prev;
	lst->top->prev = p;
	p->next = lst->top;
	p->prev = NULL;
	lst->top = p;
}

void list_free(struct list_t *lst)
{
	if (lst->top == NULL) {
		return;
	}
	struct list_node_t *tmp = lst->top;
	while (lst->top != NULL) {
		tmp = lst->top;
		lst->top = lst->top->next;
		node_free(tmp);
	}
}

